type ('a, 'b) t = ('b * 'a) Tas.t

let cree taille_max defval defprio = 
    Tas.cree taille_max (defprio, defval)

let ajoute file x p =
    Tas.ajoute (p, x) file

let retire file =
    let prio, v = Tas.extrait_maximum file in
    prio, v

let taille = Tas.taille

