type 'a arbre = { 
    etiquette : 'a; 
    enfants : 'a arbre list 
}

type 'a arbre_bin = 
    Nil
    | Noeud of 'a arbre_bin * 'a * 'a arbre_bin

let t = { etiquette = 1;
    enfants = [
        { etiquette = 2; enfants = [
            { etiquette = 5; enfants = [] }
            ] };
        { etiquette = 3; enfants = [
            { etiquette = 6; enfants = [
                { etiquette = 10 ; enfants = []}
                ]};
            { etiquette = 7; enfants = []}
            ] };
        { etiquette = 4; enfants = [
            { etiquette = 8; enfants = []};
                { etiquette = 9; enfants = []}
                ] }
        ] }

let rec taille_arbre a =
    1 + taille_foret a.enfants
and taille_foret l = match l with
        | [] -> 0
        | t::q -> taille_arbre t + taille_foret q

let rec hauteur_arbre a =
    1 + (List.fold_left max (-1) (List.map (fun x -> hauteur_arbre x) a.enfants))

let rec affiche_etiquettes a =
    print_int a.etiquette;
    print_char ' ';
    List.iter  affiche_etiquettes a.enfants

let rec peigne l =
     match l with
     [] -> Nil
     | [t] -> t
     | t::q -> Noeud(t, None, peigne q)

let rec convert a =
    match a.enfants with
    [] -> Noeud(Nil,Some a.etiquette,Nil)
     | t::q -> Noeud(convert t, Some a.etiquette, peigne (List.map convert q))

let rec print_arbre_bin pref t =
    match t with
    | Nil -> Printf.printf "%snil\n%!" pref
    | Noeud(g,x,d) -> 
            Printf.printf "%s%s\n%!" pref 
        (match x with None -> "*" | Some n -> string_of_int n);
     print_arbre_bin (String.make (String.length pref) ' ' ^ "|" ^ String.make 5 '-') g;
     print_arbre_bin (String.make (String.length pref) ' ' ^ "|" ^ String.make 5 '-') d

let () =
    Printf.printf "%d\n" (taille_arbre t);
    Printf.printf "%d\n" (hauteur_arbre t);
    affiche_etiquettes t;
    print_char '\n';
    print_arbre_bin "" (convert t);
    print_endline "Hello, World!"
