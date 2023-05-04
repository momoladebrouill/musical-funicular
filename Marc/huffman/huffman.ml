type arbre = Char of int | Node of arbre * arbre

let construit_arbre t =
    let f = FilePriorite.cree (Array.length t) (Char 0) 0 in
    Array.iteri (fun i a -> if a > 0 then FilePriorite.ajoute f (Char i) (-a) else ()) t;
    while FilePriorite.taille f >= 2 do
        let fx,x = FilePriorite.retire f in
        let fy,y = FilePriorite.retire f in
        FilePriorite.ajoute f (Node(x,y)) (fx+fy)
    done;
    snd (FilePriorite.retire f)

 let codes a =
     let m = Array.make 256 [] in
     let rec parcour a acc =
         match a with
         Char i -> m.(i)<- List.rev acc
         | Node(x,y) -> (parcour x (false::acc); parcour y (true::acc))
     in parcour a [];
     m

 
