type entier_entendu=
  |Moins_Infini
  |Entier of int
  |Plus_Infini

let age = Entier 12;;
let anne = Entier 2022;;
let dans_le_futur = ajout_entendu entier age;;

let pos_inf = Plus_Infini;;
let neg_inf = Moins_Infini;;

let ajout_entendu x y =
  match x,y with
  | Entier a, Entier b -> Entier (a+b)
  | Entier a, y -> y
  | a, Entier y-> x
  | x,y when x=y -> x
  |_ -> failwith "Indeterine"
;; 

let opp_inf (x:entier_entendu)  =
  match x with
  | Plus_Infini -> Moins_Infini
  | Moins_Infini -> Plus_Infini
  | Entier z -> Entier (-z)
;;

let prod_entendu x y =
  match x,y with
  | Entier a, Entier b -> Entier (a*b)
  | Entier a, y when a > 0 -> y
  | x, Entier a when a > 0 -> x
  | Entier a, y when a < 0 -> opp_inf y
  | x, Entier a when a < 0 -> opp_inf x
  | Entier a, y when a = 0 -> Entier 0
  | x, Entier a when a = 0 -> Entier 0 
  | x,y when x=y -> Plus_Infini
  | _ -> Moins_Infini
;; 

Printf.printf 
  "%b\n%b\n"
  ((ajout_entendu age anne)=Entier 2034)
  ((prod_entendu age anne)=Entier 24264);;



