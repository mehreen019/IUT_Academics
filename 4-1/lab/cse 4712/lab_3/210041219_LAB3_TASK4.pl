count([], 0, 0).

count([H|T], N, S):-
    count(T, N1, S1),
    N is N1 + 1,
	S is S1 + H.

%sum and count of array
count([1,2,4,1,3], N, S).