#!/usr/bin/env ocaml
(* Very basic ocaml, un peu de recurtion, un peu de typage, rien de fort interssant*)
print_string "La réponse à la question est = ";;
print_int (40+2);;
print_char '\n';;
print_char 'a';;

let print_boole (x:bool) = 
        if x 
        then print_string ("tru")
        else print_string("fols");;

print_boole (true||false);;

(* print_endline > type unit ??? *)

let annee = 2022;;
let annee_de_naissance = 1969;;

let f1 x y = x * x * ( y - x + 18 ) ;;

let f2 a b c = (exp a) *. (cos b) *. (sin c);;

(*
let f_of_i x = float_of_int x;;
let igrec = 2. in 
for i = 0 to 100 do
        Printf.printf "\n %g %g" 
                (f2 (float_of_int i) igrec 1.)
                (f2 (-1. *. (float_of_int i)) igrec 5.)
        ;
done;;
;;
*)

let p_e (x:int) (y:int) = 
        int_of_float ((float_of_int x) ** (float_of_int y))
;;

let p_e (x:int) (y:int) =
        let p = ref 1 in
        for i = 1 to y do p:= !p * x;
        done;
        !p;;

let rec factorielle n =
        if n <= 0 then 1
        else n * factorielle (n - 1);;

let rec p_e x n =
        if n <= 0 then 1
        else x * (p_e x (n-1));;

Printf.printf "%i\n%i" (p_e 2 3) (factorielle 5);;

let rec bin_print nb =
    if nb = 0 then ()
    else 
        begin 
            if nb mod 2 = 1 then print_char '1' else print_char '0';
        bin_print (nb/2)
        end
;;

print_newline ();;
bin_print 128;;
        

print_newline ();;
