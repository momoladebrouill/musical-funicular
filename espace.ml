type point2D = (float*float);;

type sous_ensemble_2D =
  | Zero (*Singelton {0}*)
  | Droite of point2D 
  | Plan
;;

let zero,plan = Zero, Plan;;
let axe_x = Droite (1., 0.);;
let axe_y = Droite (0., 1.);;
let axe_moins_x = Droite (-1., 0.);;

let inter2D alpha beta =
  match alpha,beta with 
  | Plan,y | y,Plan -> y
  | Zero,y | y,Zero -> Zero
  | Droite d1, Droite d2 -> Zero
  | Droite (x1,y1), Droite (x2,y2) 
    when x1 *. y2 -. x2 *. y1 = 0.
    -> Droite (x1,y1)
  | _ -> failwith "Incalculable"
;;

let appartient ensemble point=
  match ensemble with
  | Plan -> true
  | Droite d -> (inter2D d (Droite point)) = d
  | Zero -> point=Zero
;;

assert (inter2D axe_x axe_moins_x  = axe_x);;
