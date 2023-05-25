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
