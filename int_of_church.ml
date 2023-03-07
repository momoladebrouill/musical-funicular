let somme_premiers_entiers n =
  let s=ref 0 in
  for i=0 to n do
    s:= !s + i
  done;
  !s;;

let rec somme_premiers_entiers_rec n=
  if n=0 then 0
  else somme_premiers_entiers_rec (n-1) + n;;

let mediane3 x y z =
  if (x<y) && (y<z) then y (* x,y,z *)
  else if (z<y) && (y<x) then y (* z,y,x *)
  else if (y<x) && (x<z) then x
  else if (z<x) && (x<y) then x
  else if (y<z) && (z<x) then z
  else if (x<z) && (z<y) then z
  else 
    failwith "MMH NON"
  ;;

let mediane3 x y z =
  (* On veut x < y < z*)
  let x,z = if x<z then
    x,z
  else
    z,x
  in 
  let x,y = if x<y then 
    x,y
  else
    y,x
  in 
  let y,z = if y<z then
    y,z
  else
    z,y
  in y
;;

(*print_int (mediane3 1 2 3);;
print_int (mediane3 2 3 1);;
print_int (mediane3 3 2 1);;
print_int (mediane3 1 3 2);;
print_int (mediane3 2 1 3);;
print_int (mediane3 3 2 1);;
print_int (mediane3 1 3 2);;*)

let min a b = if a < b then a else b;;

let fiboC n =
  let rec aux n = 
      if n = 0 then (0,1) 
      else let x,y = fiboC (n-1) in (y, x+y)
  in let v,_ = aux n in v

;;

(*for i =0 to 20 do 
  Printf.printf "fibo(%i) = %i\n" i (fibo_rapide i) 
done;;*)

let signe z =
  match z with
  | 0 -> 0
  | z when z < 0 -> -1
  | _ -> 1
;;

let c0 = fun f -> fun x -> x;;
let c1 = fun f -> fun x -> f x;;
let c2 = fun f -> fun x -> f (f x);;
let c3 = fun f -> fun x -> f (f (f x));;
let c4 = fun f -> fun x -> f (f (f (f x)));;
let c5 = fun f -> fun x -> f (f (f (f (f x))));;
let c6 = fun f -> fun x -> f (f (f (f (f (f x)))));;

let int_of_church f = f (fun x ->  x+1) 0;;

let rec church_of_int f n = 
  if n = 0 then c0
  else church_of_int (f c0) (n-1)
;;


let successeur a = a c0;;

print_int (int_of_church (successeur c5));;
print_newline ();;





