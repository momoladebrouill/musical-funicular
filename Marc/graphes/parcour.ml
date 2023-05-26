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

 let taille_composante g x =
     let visites = Array.make (Array.length g) false in
     parcours g visites x;
     Array.fold_left (fun a x-> if x then a+1 else a) 0 visites

let connexe graphe = 
    (Array.length graphe = 0) ||( (taille_composante graphe 0) = (Array.length graphe))
let _ = hypercube 20 
