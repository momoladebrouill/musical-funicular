type 'a t = {
    elements : 'a array;
    mutable taille : int
}

let cree taille_max defaut =
    {
        elements = Array.make taille_max defaut;
        taille =  0;
}

let est_vide t =  t.taille = 0

let pere i = (i-1)/2

let gauche i = 2*i + 1

let droite i = 2*i + 2

let maximum t = assert (not (est_vide t)); t.elements.(0)

let feuille i t = gauche i >= t.taille

let notfeuille i t = droite i < t.taille

let assert_tas t =
    let cond =  ref true in
    for i = 0 to t.taille do
        cond := !cond && (if notfeuille i t then  t.elements.(gauche i) <= t.elements.(i) && t.elements.(droite i) <= t.elements.(i) else true)
    done;
    !cond

let print_heap t =
    let rec aux i p =
      for _ = 0 to p do print_string "- "done;
      print_int t.elements.(i);
      print_char '\n';
      if notfeuille i t then
        let _,_ = (aux (gauche i) (p+1),aux (droite i) (p+1))
      in ()
    in aux 0 0

let print_array = Array.iter print_int

let print_heap_inline t = 
    for i = 0 to t.taille do 
        print_int t.elements.(i) 
    done

let swap t i j =
    let vi = t.(i) in
    t.(i) <- t.(j);
    t.(j) <- vi

let ajoute x t = 
    t.elements.(t.taille) <- x;
    let i = ref t.taille in
    while !i > 0 && t.elements.(!i) > t.elements.(pere !i) do
        swap t.elements !i (pere !i);
        i := pere !i
    done;
    t.taille <- t.taille + 1

let max_pere_fils t i =
    let _,ind = max (max 
      (t.(gauche i),gauche i )
      (t.(droite i),droite i) 
      ) (t.(i),i) in ind

let extrait_maximum t =
    let m = t.elements.(0) in
    t.elements.(0) <- t.elements.(t.taille-1);
    let i = ref 0 in
    while notfeuille !i t && ((max_pere_fils t.elements !i) <> !i) do
        let j = max_pere_fils t.elements !i in
        swap t.elements !i j;
        i:=j
    done;
    t.taille <- t.taille - 1;
    m

let tri_par_tas l =
    let t = cree (List.length l) (List.hd l) in List.iter (fun x -> ajoute x t) l;
    let t' = cree (List.length l) (List.hd l) in List.iter (fun _ -> ajoute (extrait_maximum t) t') l;
    List.of_seq (Array.to_seq t'.elements) |> List.rev

let vers_tas a =
    let b = Array.copy a in
    let t = {elements = a; taille = 0} in
    for i = 0 to Array.length b - 1 do
        ajoute b.(i) t
    done

let depuis_tas a =
    let t = {elements = a; taille = Array.length a} in
    while t.taille > 0 do
        a.(t.taille) <- extrait_maximum t
    done


let tas () =
    let t = cree 20 0 in
    let a = [|1;2;3;4;5|] in
    print_array a;
    print_char '\n';
    vers_tas a;
    print_array a;
    print_char '\n';
    depuis_tas a;
    for i = 0 to 10 do
      ajoute i t;
    done
