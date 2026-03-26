edge(a , b ).
edge(b , c ).
edge(c , d ).
edge(d , b ).
edge(c , e ).

connected(X, Y) :- edge(X, Y).
connected(X, Y) :- edge(Y, X).

find_path(End, End, _, [End]).

find_path(Start, End, Visited, [Start|Path]):-
    connected(Start, Next),
    \+ member(Next, Visited),
	find_path(Next, End, [Next | Visited], Path).

path(Start, End, Path):-
    find_path(Start, End, [Start], Path).

%path(a,e,X).
%path(a,d,X).