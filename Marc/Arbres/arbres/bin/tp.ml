type 'a arbre_bin = 
    | Nil 
    | Noeud of 'a arbre_bin * 'a * 'a arbre_bin

type deplacement = Gauche | Droite
type chemin = deplacement list

type ('a, 'b) arbre_strict = 
    Feuille of 'a 
    | NoeudI of ('a, 'b) arbre_strict * 'b * ('a, 'b) arbre_strict

type operations = Plus | Mult
type ('a, 'b) etiquette = F of 'a | N of 'b

let rec taille (a : 'a arbre_bin) : int = 
    match a with
    Nil -> 0
    | Noeud (g,x,d) -> max (taille g) (taille d) + 1


let rec hauteur (a : 'a arbre_bin) : int =
    match a with
    Nil -> -1
    | Noeud (g,x,d) -> max (hauteur g) (hauteur d) + 1
    

let feuille (a : 'a arbre_bin) : bool =
    match a with
    Noeud (Nil,a,Nil) -> true
    | _ -> false
   

let rec noeuds (a : 'a arbre_bin) : 'a list =
    let rec aux a acc =
    match a with
    | Nil -> acc
    | Noeud (g,x,d) -> x::(noeuds g)@(noeuds d)
    in aux a []
  

let rec feuilles (a : 'a arbre_bin) : 'a list = 
    let rec aux a acc =
        match a with
        | Nil -> acc
        | Noeud (g,x,d) when feuille a -> x::acc
        | Noeud (g,x,d) -> (aux g acc)@(aux d acc)
    in aux a []

let rec noeuds_internes (a : 'a arbre_bin) : 'a list =
    let rec aux a acc =
        match a with
        | Nil -> acc
        | Noeud (g,x,d) when feuille g && feuille d -> x::acc
        | Noeud (g,x,d) when not (feuille a) -> x::(aux g acc)@(aux d acc)
        | Noeud (g,x,d) -> (aux g acc) @ (aux g acc)

    in aux a []

let rec est_strict (a : 'a arbre_bin) : bool =
    match a with
    Nil -> false
    | Noeud (Nil,x,Nil) -> true
    | Noeud (g,x,d) when Nil = g || Nil = d -> false
    | Noeud (g,x,d) -> (est_strict g) && (est_strict d)

let rec sous_arbres (a : 'a arbre_bin) : 'a arbre_bin list =
    let rec aux a acc =
        match a with
        Nil -> [a]
        | Noeud (g,_,d) -> a::(aux g acc)@(aux d acc)
    in aux a []
    
let rec chemin_noeud (a : 'a arbre_bin) (l : chemin) : 'a option =
    match a with
    Nil -> None
    | Noeud (g,x,d) ->
        match l with
        [] -> Some x
        | Droite::q -> chemin_noeud  d q
        | Gauche::q -> chemin_noeud g q
        
let rec affiche_avant a =
    match a with
    Nil -> ()
    | Noeud (g,x,d) ->
        print_string x;
        affiche_avant g;
        affiche_avant d

let rec evalue a =
    match a with
    Feuille x -> x
    |NoeudI (g,x,d) ->
        match x with
        Plus -> evalue g + evalue d
        | Mult -> evalue g * evalue d
        

let rec arbre_strict_vers_arbre_bin a =
    let asvab = arbre_strict_vers_arbre_bin in
    match a with
    | Feuille x -> Noeud(Nil, F x, Nil)
    | NoeudI (g,x,d) -> Noeud(asvab g,N x,asvab d)
    
let rec arbre_bin_vers_arbre_strict a =
    let abvas = arbre_bin_vers_arbre_strict in
    let get_val a = (match abvas a with Some x ->x | _ -> failwith "noo"  ) in
    match a with
    Nil  -> None
    | Noeud (g,N x,d) when g = Nil || d = Nil -> None
    | Noeud (g,F x,d) -> Some (Feuille x)
    | Noeud (g,N x,d) -> Some (NoeudI (get_val g,x,get_val d))
    

    
let () = print_endline "Hello, World!"
