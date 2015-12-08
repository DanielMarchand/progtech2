; Approximatively calculate the square root of a number (verbose version)
; Programming Techniques for Scientific Simulations 2, ETH Zürich, 2015
; Licensed under the Apache License (http://www.apache.org/licenses/LICENSE-2.0)
;
; run with
;   clojure t10_sqrt.clj

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; helpers

; convenience helper for definition of default parameter names
(defmacro defndef [name args & body]
  "(defn ) with default parameters.
  Define values of default arguments in a hash at the end of the parameter list.
  Invoke with (fname :<optional_argument_name> <value>)."
  (if (map? (last args))
    `(defn
       ~name
       ~(let [mandatory-args (drop-last args)
              options (last args)
              option-names (vec (keys options))]
          (vec (concat mandatory-args
                       [(symbol "&") {:keys option-names 
                                      :or options}])))
       ~@body)
    `(defn ~name ~args ~@body)))

; we could install and  (use '[clojure.math.numeric-tower]')  for these
(defn square [x]
  (* x x))
(defn mean [x y]
  (/ (+ x y) 2))
(defn abs [x]
  (if (< x 0)
    (- x)
    x))

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; the iteration

; note: the question mark is allowed as part of a symbol name
;       it is conventionally used for functions that return boolean values
(defn good_enough? [guess x tolerance]
  (< (abs (- (square guess) x))
     tolerance))

; guess is sqrt(x) if guess == x/guess, so we take the mean of guess and x/guess
(defn next_guess [guess x] (mean guess (/ x guess)))

; the iteration
(defn sqrt_iter [x tolerance guess]
  (if (good_enough? guess x tolerance)
    guess
    (recur x tolerance (next_guess guess x)) ))

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; convenience wrappers

; definition with param defaults overload
(defn sqrt
  ([x tolerance initial_guess]
    (sqrt_iter x tolerance initial_guess))
  ([x tolerance] ; overload
    (sqrt_iter x tolerance 1.0))
  ([x] ; overload
    (sqrt_iter x 0.001 1.0) ))

; definition with default parameters map (via defndef macro above)
(defndef sqrt2 [ x {tolerance 0.001 initial_guess 1.0}]
  (sqrt_iter x tolerance initial_guess) )

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; main action, with different results

(println (sqrt_iter 2.0 0.001 1.0))
(println (sqrt 2.0))
(println (sqrt 2.0 1e-9 1.4142))
(println (sqrt2 2.0 :initial_guess 1.5))
