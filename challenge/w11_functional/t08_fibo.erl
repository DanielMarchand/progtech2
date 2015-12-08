% Print the Fibonacci sequence
% Programming Techniques for Scientific Simulations 2, ETH Zürich, 2015
% Licensed under the Apache License (http://www.apache.org/licenses/LICENSE-2.0)
%
% compile with
%   erlc t08_fibo.erl
% run with
%   erl -noshell -run t08_fibo start -s init stop

-module(t08_fibo).
-export([start/0]).

print_fib(X) -> io:fwrite(" "++integer_to_list(X)).

fib(_, B, 1) -> print_fib(B);
fib(A, B, N) -> print_fib(B), fib(B, A+B, N-1).
fibonacci(N) -> io:write(0), fib(0, 1, N-1).

start() -> fibonacci(15).
