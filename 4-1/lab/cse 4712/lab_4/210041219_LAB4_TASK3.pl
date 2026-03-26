factorial(1 , 1) :- !.

factorial(N , Result) :-
 N > 1,
 N1 is N - 1,
 factorial(N1 , R),
 Result is R*N.

%factorial(5 , X).