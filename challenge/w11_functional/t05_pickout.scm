; Remove n-th element from list
; Programming Techniques for Scientific Simulations 2, ETH Zürich, 2015
; Licensed under the Apache License (http://www.apache.org/licenses/LICENSE-2.0)
;
; run with
;   scheme t05_pickout.scm

(define (pickout l n)
  (if (= n 0)                                               ; if we're at n-th recursion
      (cdr l)                                               ; add rest of list without current elem
      (append (list (car l)) (pickout (cdr l) (- n 1))) ))  ; else add first remaining element and --n

(define l '(1, 2, 3, 4, 5))
(write l)(newline)
(define l2 (pickout l 2))
(write l2)(newline)

; (define longlist '( <hardcoded long list> ))
; (write (pickout longlist <X> ))(newline)
