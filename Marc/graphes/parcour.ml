type graphe = int list array

let cycle n =
    Array.init n (fun i -> [(n+i-1) mod n; (i+1) mod n])

let complet n =
    let all = List.init n Fun.id in
    Array.init n (fun i -> List.filter ((<>) i) all)

let rec pow n = if n = 0 then 1 else 2*(pow (n-1))

let vers_bin n p =
    List.init n (fun i -> (pow i) land p <> 0)

let depuis_bin l =
    List.fold_left (fun a (i,x) -> if x then a + pow i else a) 
    0 (List.mapi (fun i x -> (i,x)) l)

let compte_diff l1 l2 =
    List.fold_left2 (fun a x y -> if x<>y then a+1 else a) 0 l1 l2

let hypercube n =
    Array.init (n*n) (fun i -> List.filter 
      (fun j -> compte_diff (vers_bin n i) (vers_bin n j) = 1) (List.init (pow n) Fun.id))

let aleatoire n p =
    let g = Array.make n [] in
    for i = 1 to  p do
        let ind = Random.int n in
        g.(ind) <- (Random.int n)::g.(ind)
    done; g

let rec parcours g visites x =
    visites.(x) <- true;
    List.iter (parcours g visites) (List.filter (fun y -> not visites.(y)) g.(x))
let parcours_fun f g x =
    let visites = Array.make (Array.length g) false in
    let rec aux x =
        visites.(x) <- true;
      f x;
      List.iter aux (List.filter (fun y -> not visites.(y)) g.(x))
    in aux x

let taille_composante g x =
    let visites = Array.make (Array.length g) false in
    parcours g visites x;
     Array.fold_left (fun a x-> if x then a+1 else a) 0 visites

let connexe graphe = 
    (Array.length graphe = 0) ||( (taille_composante graphe 0) = (Array.length graphe))

let proportions n pmax =
    List.init pmax (fun p -> (*pour chaque p*)
        List.fold_left (fun a _ -> (*compter le nombre de graphes connexes*)
            if connexe (aleatoire n p) then a+1 else a) 0
        (List.init 100 Fun.id) (*sur une base de 100 éléments*)
    )

let composante g =
    let assoc = Array.make (Array.length g) 0 in
    let rec aux j = 
        match 
          Array.find_opt 
          (fun (_,v) -> v=0) 
          (Array.mapi (fun i j -> i,j) assoc) 
        with (*rechercher ceux qui sont repertorié dans la composante connexe 0*)
        Some(i,_) -> parcours_fun (fun i -> assoc.(i) <- j) g i ; aux (j+1)
        (* si on en a un,on le repertorie dans la composante connexe j et on continue*)
        | None -> let assoc = List.of_seq (Array.to_seq assoc) in
        List.init j 
          (fun i -> 
              List.filter_map 
              (fun (k,v) -> if v=i then Some(k) else None) 
              (List.mapi (fun i j -> i,j) assoc)
              )
          (*sinon, on transforme le tableau indiquant les répartions en listes cde connexes*)
        in List.tl (aux 1) (*enlever le premier element*)


let chemin peres x y =
    let rec aux y acc =
        match peres.(y) with
        | None -> None
        | Some z -> if z = x then Some (z::acc) else aux z (z::acc)
    in aux y [y]

let parcours_ex g visites peres y =
    let rec aux x =
    visites.(x) <- true;
    List.iter 
      (fun y -> if peres.(y) = None then peres.(y) <-Some x; aux y) 
      (List.filter (fun y -> not visites.(y)) g.(x))
    in aux y
 let cyclique_oriente g =
     let n = Array.length g in
     let visites = Array.make n false in
     let peres = Array.make n None in
     parcours_ex g visites peres 0;
     List.exists (fun x -> match chemin peres x x with
      None -> false
      | Some _ -> true) (List.init n Fun.id)
