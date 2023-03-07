type couleur =
  |Pique
  |Carreau
  |Coeur
  |Trefle
;;

type carte = (int * couleur);;

let ace,valet,dame,roi=1,11,12,13;;

let cesar:carte = (roi,Carreau);;
let judith:carte = (dame,Coeur);;
let lancelot:carte = (valet,Trefle);;

let as_de_pique:carte = (ace,Pique);;
let sept_qui_prend:carte = (7,Carreau);;

let string_of_coul (c:couleur) =
  match c with
  |Pique -> "Pique"
  |Carreau -> "Carreau"
  |Coeur -> "Coeur"
  |Trefle -> "Trefle"

let style_of_num num =
  match num with
  | 1 -> "As"
  | x when x>10 -> List.nth ["Valet";"Dame";"Roi"] (x-11)
  | x -> string_of_int x
;;

let points_of_carte c = 
  match c with
  | (ace,Trefle) -> 50
  | x,typ when x>10 -> List.nth [15;20;25] (x-11)
  | x,typ -> x
;;

let affiche_carte (c:carte) =
  let num,coul = c in
  Printf.printf "%s de %s" 
    (style_of_num num) 
    (string_of_coul coul)
;;

