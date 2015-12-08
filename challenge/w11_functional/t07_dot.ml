(* Dot product of two lists
 * Programming Techniques for Scientific Simulations 2, ETH Zürich, 2015
 * Licensed under the Apache License (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * run with
 *   ocaml t07_dot.ml
 *)

let dotprod_int xs ys =
    List.fold_left (+) 0 (List.map2 ( * ) xs ys);;

print_int (dotprod_int [1; 2] [3; 4]);
print_string "\n";;

Random.self_init();;

(* build a list of n random integers in [0,100) *)
let rec rlist n =
  if n == 0 then []
  else (Random.int 100) :: rlist(n-1);;

(* same as above, but tail recursive (much more efficient for huge n) *)
let rec rlist2 n =
  let rec helper n accl =
    if n == 0 then accl
    else helper (n-1) ((Random.int 100) :: accl)
  in helper n [];;


let l1 = rlist2 200;;
let l2 = rlist2 200;;

(* print a list *)
(*
open Printf;;
let () = List.iter (printf "%d ") l1;;
print_string "\n";;
*)

print_int (dotprod_int l1 l2);
