
type trie = {
    mot : bool;
    enfants : (char * trie) list
}

let c = {mot=false;
        enfants=[
        ('a',{mot=true;enfants=[]});
        ('b',{mot=false;enfants=[
            ('c',{mot=true;enfants=[]});
            ('d',{mot = true;enfants= [
                ('e',{mot = true;enfants=[]})]})]})
        ]}

let rec taille a =
    List.fold_left (+) 1 (List.map (fun (_, x)-> taille x) a.enfants)

let rec nb_mots a =
    List.fold_left (+) (if a.mot then 1 else 0) (List.map (fun (_, x)-> nb_mots x) a.enfants)

let trie_apres_char l c =
  List.find_opt (fun (d,_) -> d = c) l

let contient a s =
    let rec aux a s i =
      if i+1 = String.length s then true else
      match  trie_apres_char a.enfants s.[i] with
      None -> false
      | Some (_,a) -> aux a s (i+1)
    in aux a s 0 

let enumere a =
  let rec aux mot current chr =
      let new_word = mot ^ chr in
      let kids_words = List.concat (List.map (fun (chr,x) -> aux new_word x (String.make 1 chr)) current.enfants)
      in if current.mot then new_word :: kids_words else kids_words
  in aux "" a ""

let suffixe i s =
    let len = String.length s - 1 in
    let rec aux i =
      if i = len then (s.[i],{mot = true; enfants = []})
      else (s.[i],{mot = false; enfants = [aux (i+1)]})
    in {mot = false; enfants = [aux i]}

let avec_trie_pour_char l c t =
    let rec aux l  =
        match l with 
        [] -> [(c,t)]
        |(a,t')::q -> if a = c then (c,t)::q else (a,t')::(aux q)
    in aux l

let ajoute t s =
    let rec aux t i =
        if i = String.length s then t else
            { 
                mot  = t.mot; enfants = avec_trie_pour_char t.enfants s.[i]  
            begin 
              match trie_apres_char t.enfants s.[i] with 
              None -> suffixe i s 
              | Some (c,t) ->  aux t (i+1)
            end 
    }
    in aux t 0

let () = 
    print_int (nb_mots c);
    print_int (taille c);
    assert (trie_apres_char c.enfants 'a' = Some ('a',{mot=true;enfants=[]}));
    assert ((trie_apres_char c.enfants 'f') = None);
    assert (contient c "bc");
    assert (contient (suffixe 2 "abcde") "cde");
    print_endline "les mots de cet arbre :";
    List.iter print_endline (enumere (ajoute c "bde des etudiants"));
    print_endline "Hello, World!"





