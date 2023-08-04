type case = Vide | Pion | Invalide
type plateau = case array array
let n = 7
(* Un plateau est une matrice 7x7 avec des cases invalides aux coins *)
type mouvement = (int*int)*(int*int)
let print_tableau t =
    for i=0 to n-1 do
        for j=0 to n-1 do
            Printf.printf " %s " (match t.(i).(j) with
              Vide -> "◦" | Pion -> "•" | Invalide -> " ")
        done;
        print_char '\n'
    done


let plateau_initial () =
    let t = Array.make_matrix n n Invalide in
    for i=n/3 to (2*n)/3 do
        for j=0 to n-1 do
            t.(i).(j) <- Pion;
            t.(j).(i) <- Pion
        done
    done;
    t.(n/2).(n/2) <- Vide;
    t
let milieu (x1,y1) (x2,y2) = (x1+x2)/2,(y1+y2)/2
let mouvements p =
  let valide (x1,y1) (x2,y2) = 
      (0<=x2 && x2<n && 0<=y2 && y2<n)
      && (let mx,my = milieu (x1,y1) (x2,y2) in p.(x1).(y1), p.(mx).(my), p.(x2).(y2)) = (Vide,Pion,Pion) 
  in 
  let l = ref [] in
  for x=0 to n-1 do
      for y=0 to n-1 do
          l := List.append !l 
            (List.map (fun d -> ((x,y),d)) (List.filter (valide (x,y)) [(x+2,y);(x,y+2);(x,y-2);(x-2,y)]))
      done
  done;
  !l

let compte_pions p =
  let r = ref 0 in
  Array.iter (fun l -> Array.iter (fun e -> if e = Pion then incr r) l) p ; !r

let valide p = compte_pions p = 1

let faire ((x1,y1),(x2,y2)) p = 
    let mx,my = milieu (x1,y1) (x2,y2) in   
    p.(x1).(y1) <- Pion;
    p.(mx).(my) <- Vide;
    p.(x2).(y2) <- Vide

let defaire ((x1,y1),(x2,y2)) p = 
    let mx,my = milieu (x1,y1) (x2,y2) in   
    p.(x1).(y1) <- Vide;
    p.(mx).(my) <- Pion;
    p.(x2).(y2) <- Pion

exception Solution of mouvement list 

let rec enumere pos chemin =
    if valide pos then raise (Solution chemin) 
    else List.iter (fun mvmnt -> faire mvmnt pos; enumere pos (mvmnt::chemin); defaire mvmnt pos )
    (mouvements pos)

let resout () = 
    let p = plateau_initial () in
    try enumere p [] ; failwith "pas de solution" with Solution l -> List.rev l 

let () = 
    let p = plateau_initial () in
    print_tableau p;
    Printf.printf "qqty pions : %d\n" (compte_pions p);
    let mouvements = resout () in
    List.iter (fun m -> print_tableau p; faire m p; let _ = read_line () in ()) mouvements

