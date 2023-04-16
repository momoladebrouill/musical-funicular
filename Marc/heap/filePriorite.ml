


let cree taille_max defval defprio =
    Tas.cree taille_max (defprio,defval)

let ajoute heap e p =
    Tas.ajoute (p,e) heap

let retire heap =
    let _,e = Tas.extrait_maximum heap in e

let () =
    let heap = cree 50 0 1 in
    ajoute heap 5 2;
    ajoute heap 10 3;
    ajoute heap 69 497;
    ajoute heap 4 2;
    print_int (retire heap)
