% Way-1:
gcd(X, 0, G) :- G is X.
gcd(X, Y, G) :- Y > 0, Z is X mod Y, gcd(Y, Z, G).

% Way-2:
gcd(A,B,G) :-
	A=B,
	G=A.

gcd(A,B,G) :-
	A>B,
	C is A-B,
	gcd(C,B,G).

gcd(A,B,G) :-
	B>A,
	C is B-A,
	gcd(C,A,G).

?- gcd(48, 18, Result).
Result = 6.



