let stats s =
    let t = Array.make 256 0 in
    String.iter (fun c -> let lieux = Char.code c in t.(lieux) <- t.(lieux) + 1) s;
    t

let compresse s =
    let a = Huffman.construit_arbre (stats s) in
    let cs = Huffman.codes a in
    a, (String.fold_left (fun t c -> t@(cs.(Char.code c))) [] s)
