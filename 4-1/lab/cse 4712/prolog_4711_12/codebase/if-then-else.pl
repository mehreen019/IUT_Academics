/*
max(X,Y,Z) :- 
	X =< Y , 
	Z = Y.
	
max(X,Y,Z) :- 
	\+(X =< Y) , 
	Z = X.
*/	
	


max(X,Y,Z) :-
  X =< Y -> Z = Y ;
  Z=X.

