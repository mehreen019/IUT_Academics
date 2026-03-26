color( red ).
color( green ).
color( blue ).

diff_color(X, Y):-
    color(X),
    color(Y),
    X \= Y.

%all combinations of different colors
diff_color(X, Y).