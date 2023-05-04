

let () =
    let s = Sys.argv.(1) in
    let a,l = Compression.compresse s in
    Printf.printf "avant : %s\npendant : " s;
    List.iter (fun x -> print_char (if x then '1' else '0')) l;
    Printf.printf "\napres : %s\n" (Decompression.decompress a l)
