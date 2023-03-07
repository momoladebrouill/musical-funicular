type entier_unaire =
  | Zero
  | Successeur of entier_unaire
;;

let zero = Zero;;
let un = Successeur zero;;
let deux = Successeur un;;
let trois = Successeur deux;;

let rec int_of_entier_unaire eu=
  match eu with
  | Zero -> 0
  | Successeur t -> (int_of_entier_unaire t) + 1
;;

let rec entier_unaire_of_int i=
  if i = 0 then Zero
  else Successeur (entier_unaire_of_int (i-1))
;;

let rec somme_unaire m n =
  match m,n with
  | (m,Zero) -> m
  | (Zero,n) -> n
  | (m,Successeur p) -> somme_unaire (Successeur m) p;;

let rec produit_unaire m n =
  match m,n with 
  | (m,Zero) -> Zero
  | (Zero,n) -> Zero
  | (m, Successeur p) -> somme_unaire (produit_unaire m p) m
;; 
