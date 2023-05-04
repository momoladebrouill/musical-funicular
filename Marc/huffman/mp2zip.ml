let bin_print x =
    let rec aux x p =
        if x > 0 then 
            (print_char (if x land p = 0 then '0' else '1');
            aux (x-p) (p*2))
        else ()
    in aux x 1

let () =
    if Array.length Sys.argv <= 1 then Printf.printf "khoya y a pa mot a encod esh\n" else
    let s = Sys.argv.(1) in
    let a,l = Compression.compresse s in
    Printf.printf "avant : %s\n" s;
    Printf.printf "sans compression : ";
    String.iter (fun c -> bin_print (Char.code c)) s;
    Printf.printf "\npendant : ";
    List.iter (fun x -> print_char (if x then '1' else '0')) l;
    Printf.printf "\napres : %s\n" (Decompression.decompress a l)
