% task 1
% ----- Graph -----
edge(a, b, 3).
edge(a, c, 5).
edge(b, c, 2).
edge(b, d, 4).
edge(c, d, 1).

% ----- Path finder (no cycles) -----
path(Start, End, Visited, [Start, End], Cost, MaxEdge) :-
    edge(Start, End, Cost),
    \+ member(End, Visited),
    MaxEdge is Cost.

path(Start, End, Visited, [Start | Rest], Cost, MaxEdge) :-
    edge(Start, Next, W),
    \+ member(Next, Visited),
    path(Next, End, [Next | Visited], Rest, Cost1, Max1),
    Cost is W + Cost1,
    MaxEdge is max(W, Max1).

% ----- Main predicate -----
shortest_path(Start, End, Path, Cost, MaxEdge) :-
    findall(
        (Cost, MaxEdge, Path),
        path(Start, End, [Start], Path, Cost, MaxEdge),
        Paths
    ),
    sort(Paths, [(Cost, MaxEdge, Path) | _]).


% task 2
% ----- Food -----
food(a, sushi).
food(b, pizza).
food(c, sushi).
food(d, burger).

% ----- Path with food constraint -----
path_food(Start, End, Visited, Foods, [Start, End], Cost) :-
    edge(Start, End, Cost),
    \+ member(End, Visited),
    food(End, F),
    \+ member(F, Foods).

path_food(Start, End, Visited, Foods, [Start | Rest], Cost) :-
    edge(Start, Next, W),
    \+ member(Next, Visited),
    food(Next, F),
    \+ member(F, Foods),
    path_food(Next, End,
              [Next | Visited],
              [F | Foods],
              Rest,
              Cost1),
    Cost is W + Cost1.

% ----- Main predicate -----
shortest_path_food(Start, End, Path, Cost) :-
    food(Start, F),
    findall(
        (Cost, Path),
        path_food(Start, End, [Start], [F], Path, Cost),
        Paths
    ),
    sort(Paths, [(Cost, Path) | _]).

shortest_path_food(_, _, _, _) :-
    false.

% task 3
coins([1, 5, 10, 50]).

change(Amount, Coins, NumCoins) :-
    coins(C),
    findall(
        (N, Seq),
        valid_change(Amount, C, none, Seq, N),
        Solutions
    ),
    Solutions \= [],
    sort(Solutions, Sorted),
    reverse(Sorted, [(NumCoins, Coins) | _]).

valid_change(0, _, _, [], 0).

valid_change(Amount, Coins, Prev, [C | Rest], N) :-
    Amount > 0,
    member(C, Coins),
    C =\= Prev,
    NewAmount is Amount - C,
    NewAmount >= 0,
    valid_change(NewAmount, Coins, C, Rest, N1),
    N is N1 + 1.


% cut

coins([1,5,10,50]).

% Entry predicate
change(Amount, Coins, NumCoins) :-
    coins(CoinList),
    valid_change(Amount, CoinList, none, Coins, NumCoins), 

% Base case
valid_change(0, _, _, [], 0).

% Recursive case
valid_change(Amount, Coins, Prev, [C | Rest], N) :-
    Amount > 0,
    member(C, Coins),
    C =\= Prev,
    NewAmount is Amount - C,
    NewAmount >= 0,
    valid_change(NewAmount, Coins, C, Rest, N1),
    N is N1 + 1.

% task 4
subject_grade(M, 'A') :- M >= 90, !.
subject_grade(M, 'B') :- M >= 80, !.
subject_grade(M, 'C') :- M >= 70, !.
subject_grade(M, 'D') :- M >= 60, !.
subject_grade(_, 'F').

rank_students(Ranked) :-
    findall(
        [Lowest, Total, Name],
        (
            student(Name, M1, M2, M3),
            subject_grade(M1, G1),
            subject_grade(M2, G2),
            subject_grade(M3, G3),
            lowest_grade([G1, G2, G3], Lowest),
            Total is M1 + M2 + M3
        ),
        List
    ),
    sort(List, Sorted),
    reverse(Sorted, Ranked).

lowest_grade(Grades, Lowest) :-
    sort(Grades, [Lowest | _]).
