open Graphics
let _ =
    Random.self_init ();
type arbre =
    Nil
    | Noeud of arbre*string*arbre

type dir = 
    G | D

let rnoeud = 10 (* Le rayon du noeud *)
let marge = 10 (* la marge autour du noeud *)

let rec pixels a = match a with
    | Nil -> 0, 0
    | Noeud(g, _, d) -> 
            let lg, _ = pixels g in
            let ld, _ = pixels d in
            lg + ld + 2*(marge + rnoeud), lg + marge + rnoeud

let rec dessine a x y =
    
    match a with
    | Nil -> ()
    | Noeud(g, e, d) ->
            (* On précalcule les tailles des sous-arbres *)
            let lg, rg = pixels g in
            let _, rd = pixels d in

            (* position de la racine gauche relativement à (x,y) *)
            let v_rg = x - lg - marge - rnoeud + rg in

            (* position de la racine droite relative (x, y) *)
            let v_rd = x + marge + rnoeud + rd in
            
            let dec_y = y - 2 * rnoeud - marge in

            moveto x y; lineto v_rg dec_y;
            moveto x y; lineto v_rd dec_y;
            fill_circle x y rnoeud;

            moveto (x) (y);
            set_color red;
            draw_string e;
            set_color black;

            dessine g v_rg dec_y;
            dessine d v_rd dec_y

let random_char () =
    String.make 1 "azertyuiopqsdfghjklmwxcvbn".[Random.int 26]

let rec  genere_arbre_1 n = 
    if n = 0 then Nil else
        let r = Random.int n in
        Noeud( genere_arbre_1 r, random_char (), genere_arbre_1 (n-r-1))

let rec foreach l f = 
    match l with
    [] -> []
    | t::q -> (f t)::(foreach q f)

let rec chemins_vide a =
    match a with
    Nil -> [[]]
    | Noeud (g,_,d) -> (foreach (chemins_vide g) (fun t-> G::t))@(foreach (chemins_vide d) (fun t->D::t))

let rec remplit a chem =
    match chem,a with
    [],_ -> Noeud(Nil,random_char (),Nil)
    | G::q,Noeud(g,x,d) -> Noeud(remplit g q,x,d)
    | D::q,Noeud(g,x,d) -> Noeud(g,x,remplit d q)
    | _,_ -> failwith "deso le R"

let genere_arbre_2 n =
    let rec aux i a =
        if i = 0 then a 
        else let chems = chemins_vide a in 
        aux (i-1) (remplit a (List.nth chems (Random.int (n-i+1))))
        in aux n Nil


let a = Nil
let _ = genere_arbre_1 10
let b = genere_arbre_2 20

let () = if a<>b then
    let x,y = (pixels b) in 
    Printf.printf "%i %i\n" x y;
    open_graph " ";
    let w,r = pixels b in
    dessine b ((size_x ()) /2) ((size_y ())/2);
    let _ = Scanf.scanf "%c" (fun _ -> ()) in Printf.printf "\n" 
