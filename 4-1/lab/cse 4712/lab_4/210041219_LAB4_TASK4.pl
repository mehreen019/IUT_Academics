edge(a , b ).
edge(b , c ).
edge(c , d ).
edge(d , e ).
edge(c , e ).

find_path(End, End, _, [End]).

find_path(Start, End, Visited, [Start|Path]):-
    edge(Start, Next),
    \+ member(Next, Visited),
	find_path(Next, End, [Next | Visited], Path).

find_path(Start, End, Path):-
    find_path(Start, End, [Start], Path).

%find_path(a, c, X).