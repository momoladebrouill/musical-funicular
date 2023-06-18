let tdim = 32
let tdimf = float_of_int tdim
let world_width = 21
let world_height = 21

type tile = Sol | Obstacle | Mur of int * int

type game_state = {
    position : int * int;
    direction : int;
    ennemy : int * int;
    tileset : Raylib.Texture.t;
    link_sheet : Raylib.Texture.t;
    ennemy_sheet : Raylib.Texture.t;
    fleche_sheet : Raylib.Texture.t;
    world : tile array array;
    frame : int;
    path : (int * int) list;
    distances : int array array;
    ennemy_move : bool
}

(* Question 1 : la fonction suivante demande, étant donné un monde rempli
   d'Obstacles et de Mur, de réaliser un labyrinthe en plaçant des cases Sol
   à l'aide d'un parcours en profondeur issu de (1,1) où on indique comme Sol
   toutes les cases traitées. On ignore les cases ayant au moins deux voisines
   Sol (car on créerait un raccourci).

   Le graphe implicite ici sera de dire que (x,y) --> (x',y')
   lorsque (x,y) est une case Sol et (x',y') est une case Obstacle
   possédant une unique case voisine Sol (on ne va pas créer de cycle). 

   Si vous le faites de manière déterministe, votre labyrinthe va être peu
   intéressant. Faites un mélange des voisins pour rajouter de l'aléatoire.
   *)
let laby world =
    let w = Array.length world - 2 in
    let h = Array.length world.(0) - 2 in
    let out_border x y = x<1 || x>w || y<1 || y>h in
    let iter_border x y = List.init 8 (fun i -> if i=4 then (1,1) else (x - 1 + (i mod 3) ,y - 1 + i/3)) in
    let qqty_sol_vois x y = (List.fold_left (fun s (x,y) -> s + if (out_border x y) || world.(x).(y) <> Sol then 0 else 1) 0 (iter_border x y)) in
    let rec aux x y n =
        if  (out_border x y) || n < 1 || world.(x).(y) = Sol then () 
        else
            begin
            world.(x).(y) <- Sol;
            let x',y'=ref (x+Random.int 3 - 1),ref (y+Random.int 3 - 1) in
            while qqty_sol_vois !x' !y' <> 1 do
                    x' := x+(Random.int 3) - 1;
                    y' := y+(Random.int 3) - 1
            done;
             aux !x' !y' (n-1)
            end
    in aux 5 5 100


(* Question 2 : supprimer n Obstacles aléatoires dans le monde *)
let dig_holes world n =
    ()

(* On demande ici de renvoyer un couple (d, path) où d est la matrice
   de distances dans un Dijkstra issu de g.position et path est soit
   [] soit la liste des coordonnées dans un chemin de g.position vers
   g.ennemi *)
let compute_path g =
    let inf = max_int in
    let d = Array.make_matrix world_width world_height inf in
    d, []


(* ATTENTION à décommenter la partie en dessous sur l'ennemi 
   quand laby fonctionne. Mis-à-part cela, vous pouvez 
   ignorer tout ce qu'il y a en dessous. *)

let create_world () =
    let world = Array.make_matrix world_width world_height Obstacle in
    for i = 1 to world_width - 2 do
        world.(i).(0) <- Mur (0, 1);
        world.(i).(world_height - 1) <- Mur (0, -1)
    done;
    for i = 1 to world_height - 2 do
        world.(0).(i) <- Mur (-1, 0);
        world.(world_width - 1).(i) <- Mur (1, 0)
    done;
    world.(0).(0) <- Mur (-1, 1);
    world.(world_width - 1).(0) <- Mur (1, 1);
    world.(0).(world_height - 1) <- Mur (-1, -1);
    world.(world_width - 1).(world_height - 1) <- Mur (1, -1);
    world
    
let draw_path g =
    let rec aux p (px, py) = 
        match p with
        | [] -> []
        | [(x,y)] -> 
            [   match x-px, y-py with
                | 0, -1 -> 10
                | 0, 1 -> 4
                | 1, 0 -> 3
                | -1, 0 -> 9
                | _ -> 7 ]
        | (x,y)::(nx,ny)::q ->
            (match px-x, py-y, x-nx, y-ny with
              1, _, _, 1-> 12
            | 1, _, _, -1-> 0
            | -1, _, _, 1-> 14
            | -1, _, _, -1-> 2
            | -1, _, _, 0 -> 1
            | 1, _, _, 0 -> 1

            | _, -1, -1, _ -> 12
            | _, -1, 1, _ -> 14
            | _, 1, -1, _ -> 0
            | _, 1, 1, _ -> 2
            | _, 1, 0, _ -> 6
            | _, -1, 0, _ -> 6

            | _ -> 7) :: aux ((nx,ny)::q) (x, y)
    in
    let l = match g.path with
        | [] -> []
        | t::q -> 8 :: aux q t in
    let open Raylib in
    List.iter
        (fun ( (x,y), t ) ->
            let tx = t mod 6 in
            let ty = t / 6 in
            draw_texture_rec 
                g.fleche_sheet
                (Rectangle.create 
                    (32. *. float_of_int tx) 
                    (32. *. float_of_int ty) 
                    32. 32.)
                (Vector2.create 
                (tdimf *. float_of_int x) 
                (tdimf *. float_of_int y))
                Color.white
        )
        (List.combine g.path l)

let world_to_tile world di dj =
    match world.(di).(dj) with
    | Sol -> Some 9
    | Obstacle -> Some 5
    | Mur (1,0) -> Some 10
    | Mur (-1,0) -> Some 8
    | Mur (1,1) -> Some 2
    | Mur (1,-1) -> Some 18
    | Mur (-1,1) -> Some 0
    | Mur (-1,-1) -> Some 16
    | Mur (0,1) -> Some 1
    | Mur (0,-1) -> Some 17
    | _ -> None
 
let draw_tile tileset t x y =
    let open Raylib in
    let texw = Texture.width tileset in
    let nr = texw / tdim in
    let tx = t mod nr in
    let ty = t / nr in
  draw_texture_rec 
    tileset
    (Rectangle.create 
        (tdimf *. float_of_int tx) 
        (tdimf *. float_of_int ty) 
        tdimf tdimf)
    (Vector2.create (tdimf *. float_of_int x) (tdimf *. float_of_int y))
    Color.white

let draw_world g =
    for i = 0 to world_width - 1 do
        for j = 0 to world_height - 1 do
            match world_to_tile g.world i j with
            | None -> ()
            | Some t -> draw_tile g.tileset t i j
        done
    done

let draw_link g =
    let open Raylib in
    let i, j = g.position in
    let f = g.frame in
    let t = (f/30) mod 4 in
    draw_texture_rec 
        g.link_sheet
        (Rectangle.create 
            (48. *. float_of_int t) 
            (64. *. float_of_int g.direction)
            48. 64.)
        (Vector2.create 
        (tdimf *. float_of_int i -. 8.) 
        (tdimf *. float_of_int j -. 32.))
        Color.white

let draw_ennemy g =
    let open Raylib in
    let i, j = g.ennemy in
    let f = g.frame in
    let t = (f/30) mod 6 in
    let t = if t >= 3 then 5 - t else t in
    draw_texture_rec 
        g.ennemy_sheet
        (Rectangle.create 
            (32. *. float_of_int t) 
            0.
            32. 64.)
        (Vector2.create 
        (tdimf *. float_of_int i) 
        (tdimf *. float_of_int j -. 32.))
        Color.white

 let load_texture_from_disk fn =
    let open Raylib in
    let img = load_image fn in
    let texture = load_texture_from_image img in
    unload_image img;
    texture

let setup () =
    Random.self_init ();
    let open Raylib in
    init_window (tdim * world_width) (tdim * world_height) 
        "La légende de Zeta";
    set_target_fps 60;
    let tileset = load_texture_from_disk 
        "resources/zelda-oracle-maison.png" in
    let link = load_texture_from_disk
        "resources/link.png" in
    let ennemy = load_texture_from_disk
        "resources/zelda-ennemi.png" in
    let fleche = load_texture_from_disk
        "resources/fleches.png" in
    let world = create_world () in
    laby world;
    dig_holes world world_width;
    let xe = ref (world_width - 2) in
    (* à décommenter quand votre labyrinthe fonctionne pour placer l'ennemi
       sur la dernière ligne *)
    (*
    while world.(!xe).(world_height - 2) <> Sol do
        decr xe
    done;
    *)
    {
        tileset = tileset;
        link_sheet = link;
        ennemy_sheet = ennemy;
        fleche_sheet = fleche;
        world = world;
        position = (1,1);
        direction = 0;
        ennemy = (!xe,world_height-2);
        frame = 0;
        path = [];
        ennemy_move = true;
        distances = Array.make_matrix world_width world_height max_int
    }

let rec loop g =
  match Raylib.window_should_close () with
  | true -> Raylib.close_window ()
  | false ->
      let open Raylib in

      begin_drawing ();
      clear_background Color.raywhite;

      draw_world g;

      for x = 0 to world_width - 1 do
          for y = 0 to world_height - 1 do
                let d = g.distances.(x).(y) in
                if d < max_int
                then begin
                    let c = Color.create (5*d) (255-5*d) 0 100 in
                    draw_rectangle (x * tdim) (y * tdim) tdim tdim c;
                    draw_text 
                        (string_of_int d)
                        (x * tdim) (y * tdim) (tdim/2) Color.black
                end
          done
      done;

      draw_path g;
      
      draw_link g;
      draw_ennemy g;

      end_drawing ();

      let p = ref g.position in
      let d = ref g.direction in
      let x, y = !p in
      if is_key_pressed Key.Up && g.world.(x).(y-1) = Sol
      then ( p := (x, y-1); d := 3 )
      else if is_key_pressed Key.Down && g.world.(x).(y+1) = Sol
      then ( p := (x, y+1); d := 0 )
      else if is_key_pressed Key.Left && g.world.(x-1).(y) = Sol
      then ( p := (x-1, y); d := 1 )
      else if is_key_pressed Key.Right && g.world.(x+1).(y) = Sol
      then ( p := (x+1, y); d := 2 );

      let ennemy_move = if is_key_pressed Key.P 
        then not g.ennemy_move
        else g.ennemy_move in

      let distances, path = if !p <> g.position || ennemy_move
          then compute_path { g with position = !p }
          else g.distances, g.path in

      let e = if not ennemy_move || g.frame mod 24 <> 0
        then g.ennemy
        else match List.rev path with
            | _::(x,y)::_ -> (x,y)
            | _ -> g.ennemy
      in

      loop { g with 
        ennemy_move = ennemy_move;
        position = !p;
        ennemy = e;
        direction = !d;
        path = path;
        distances = distances;
        frame = g.frame + 1 }

let () = setup () |> loop
