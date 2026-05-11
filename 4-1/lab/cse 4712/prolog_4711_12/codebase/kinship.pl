-----------------
% kinship example
-----------------

male(albert). % a fact stating albert is a male
male(edward).
male(tom).
male(paul).

female(mat).
female(alice). % a fact stating alice is a female
female(victoria). 

parent(albert,edward). % a fact: albert is parent of edward
parent(victoria,mat).
parent(tom,albert).
parent(mat,albert).
parent(paul,victoria).


father(X,Y) :- 
	parent(X,Y), 
	male(X). 

mother(X,Y) :- 
	parent(X,Y), 
	female(X). 

grandfather(X,Y) :- 
	father(X,Z),
	parent(Z,Y).

brother(X, Y) :-
  parent(Z, X),
  parent(Z, Y),
  male(X),
  X \= Y.
  
  
/** <examples>
?- male(X).
?- father(F,C).
?- grandmother !!
?- cousin !!
*/    

