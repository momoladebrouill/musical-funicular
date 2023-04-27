type arbre = E | N of arbre * int * arbre

let minimum t = let N(_,x,_) = t in x

let est_un_arbre_croissant t =
    t = E || begin
        let rec aux t = 
            match t with
            N(E,x,E) -> (true,x)
            | N(g,x,d) -> 
                    let gd,mind = aux d in
                    let gg,ming = aux g in
                   if gd && gd then 
                (ming >= x && mind >= x,x) else (false,x)
            | _ -> false,0
     in fst (aux t) end


let rec fusion t1 t2 =
    match t1,t2 with
    E,t2 -> t2
    | t1,E -> t1
    | N(g,x,d),N(g',x',d') when x<=x' -> N(fusion d t2,x,g)
    | N(g,x,d),N(g',x',d') -> N(fusion d' t1,x',g')

let ajoute t x =
    fusion t (N(E,x,E))

let rec a i = if i = 0 then E else ajoute (a (i-1)) i

let print_arbre a =
    let rec aux p a =
        let indent_and_print s = 
            for _ = 0 to p do print_string "- " done; print_string (s^"\n") in
        match a with
        E -> indent_and_print "E"
        | N(g,x,d) -> 
            indent_and_print (string_of_int x);
            aux (p+1) g;
            aux (p+1) d
    in aux 0 a

let supprime_minimum a =
    match a with
    | E -> E
    | N(E,_,t) 
    | N(t,_,E) -> t
    | N((N(a,x,b) as t1),_,(N(c,y,d) as t2)) -> 
            if x < y then N(fusion a b,x,t2)
            else N(t1,y,fusion c d)

let ajouts_successifs v =
    let rec aux i =
        if i = 0 then E else ajoute (aux (i-1)) v.(i)
    in aux (Array.length v - 1)

let rec potentiel t =
    let rec aux t = 
    match t with
    | E -> (0,1)
    | N(g,x,d) -> 
            let pg,tg = aux g in
            let pd,td = aux d in
            ((if tg < td then 1 else 0) + pg + pd, td+tg+1)
    in fst (aux t)

let tri a =
    let b = ref (ajouts_successifs a) in
    Array.init (Array.length a - 1) (fun i -> let mini = minimum !b in b:=supprime_minimum !b; mini)
    ;
(* FOR UTOP : *)
#install_printer print_arbre;;
let q = a 5;;
