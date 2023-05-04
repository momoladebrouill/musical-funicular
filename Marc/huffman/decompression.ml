let decompress a l =
    let add s i = s ^ (Char.chr i |> String.make 1) in
    let rec aux l s b =
        match l with
        [] -> ( 
            match b with 
            | Huffman.Char i -> (add s i)
            | _ -> failwith "non ended code")
        | t::q ->
                match b with 
                | Huffman.Char i -> aux l (add s i) a
                | Huffman.Node(x,y) -> aux q s (if t then y else x)
    in  aux l "" a
