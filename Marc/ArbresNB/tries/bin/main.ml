
type trie = {
    mot : bool;
    enfants : (char * trie) list
}

let c = {
    mot = false;
    enfants = [
        ('a',
          {mot = true; enfants = []});
        ('b',{mot = false; enfants = [
            ('c',{mot = true; enfants = []})]})
        ]}

let rec taille a =
    List.fold_left (+) 1 (List.map (fun (_, x)-> taille x) a.enfants)

let rec nb_mots a =
    List.fold_left (+) (if a.mot then 1 else 0) (List.map (fun (_, x)-> nb_mots x) a.enfants)

let trie_apres_char l c =
  List.find_opt (fun (d,_) -> d = c) l

let rec contient a s i =
    if i+1 = String.length s then true else
    match  trie_apres_char a.enfants s.[i] with
    None -> false
    | Some (_,a) -> contient a s (i+1)

let () = 
    print_int (nb_mots c);
    print_int (taille c);
    assert (trie_apres_char c.enfants 'a' = Some ('a',{mot=true;enfants=[]}));
    assert ((trie_apres_char c.enfants 'f') = None);
    assert (contient c "bc" 0);
    print_endline "Hello, World!"
