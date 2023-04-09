type 'a abr =
    Noeud of 'a abr * 'a * 'a abr
    | Nil

type 'a a23 =
    | Bin23 of 'a a23 * 'a * 'a a23
    | Ter23 of 'a a23 * 'a * 'a a23 * 'a * 'a a23
    | Nil23

type 'a a234 =
    | Bin23 of 'a a234 * 'a * 'a a234
    | Ter23 of 'a a234 * 'a * 'a a234 * 'a * 'a a234
    | Quat23 of 'a a234 * 'a * 'a a234 * 'a * 'a a234 * 'a * 'a a234
    | Nil234
 

let etendue a =
    let rec g_min a =
        match a with
        | Nil -> failwith "trop bas"
        | Noeud(Nil,x,Nil) -> x
        | Noeud(g,_,_) -> g_min g
    in
    let rec d_max a =
        match a with
        | Nil -> failwith "trop bas"
        | Noeud(Nil,x,Nil) -> x
        | Noeud(_,_,d) -> d_max d
    in (g_min a, d_max a)


let rec est_abr1 a =
    match a with
    | Nil -> true
    | Noeud(Nil,x,Nil) -> true
    | Noeud(g,x,d) -> est_abr1 g && est_abr1 d && 
      (let gmin,gmax = etendue g in
      let dmin,dmax = etendue d in
      gmax < x && x < dmin)

let est_abr a =
  let rec aux a = 
      match a with 
      | Noeud(Nil,x,Nil) -> (true,x,x)
      | Noeud(g,x,d)->  
        let b,ming,maxg = aux g in
        let d,mind,maxd = aux d in
        if b && d && maxg < x && x < mind then (true,maxg, mind) else (false,x,x)  
  in let (b,_,_) = aux a in b


let rec contient a t =
    match a with 
    | Nil -> false
    | Noeud(g,x,d) -> (t = x) || (if t < x then contient g t else contient d t)


let rec insere a t =
    match a with 
    | Nil -> Noeud(Nil,t,Nil)
    | Noeud(g,x,d) -> if x = t then a else
        if x > t then Noeud(insere g t,x,d) 
         else Noeud(g,x,insere d t)

let rec supprime a t =
    let rec plus_a_droite a =
        match a with 
        | Nil -> failwith "peuplus"
        | Noeud(_,x,Nil) -> x 
        | Noeud(_,x,d) -> plus_a_droite d
    in 
      match a with 
      | Nil -> Nil
      | Noeud(g,x,d) ->
              if x = t then
                  if g = Nil then d else
                  let pad = plus_a_droite g in Noeud(supprime g pad,pad,d)
              else if x > t then Noeud(supprime g t,x,d) 
              else Noeud(g,x,supprime d t)
 
let b = Noeud(
    Noeud(Nil,1,Nil),
    3,
    Noeud(
        Noeud(Nil,4,Nil),
        6,
        Noeud(Nil,10,Nil)
     )
)

let a = Noeud(
      Noeud(Noeud(Nil,-1,Nil),1,Noeud(Nil,4,Nil)),
      5,
      Noeud(Nil,6,Nil)
)
