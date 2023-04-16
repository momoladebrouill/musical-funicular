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
        match a with
    E -> ()
    | N(g,x,d) -> 
            for _=0 to p do print_string "- " done;
            print_int x;
            print_char '\n';
            aux (p+1) g;
            aux (p+1) d
     in aux 0

let supprime_minimum a =
    match a with
    | E -> E
    | N(E,x,d) -> d
    | N(g,x,E) -> g
    | N(N(a,x,b),_,N(c,y,d)) -> 
            if x < y then N(fusion a b,x,N(c,y,d))
            else N(N(a,x,b),y,fusion c d)

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

