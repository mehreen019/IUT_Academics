flatten_list([],[]).

flatten_list([H|T], Flat):-
    flatten_list(T, Flat1),
    append(H, Flat1, Flat).

%flatten_list([[a,b],[c],[b,d,e]], X).