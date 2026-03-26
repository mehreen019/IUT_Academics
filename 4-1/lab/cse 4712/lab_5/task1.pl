% TASK 1: Find coin sequence with GCD=1 constraint and most unique coins

% Available coins
coins([1,2,5,10,50]).

% Compute GCD using Euclidean algorithm
gcd(X, 0, X).
gcd(X, Y, G) :- 
    Y > 0, 
    R is X mod Y, 
    gcd(Y, R, G).

% Main predicate - finds sequence with most unique coins
change(Amount, Coins, UniqueCount) :-
    findall([U, C], find_valid_sequence(Amount, C, U), AllSequences),
    sort(1, @>=, AllSequences, [[UniqueCount, Coins]|_]).

% Find a valid sequence and count unique coins
find_valid_sequence(Amount, Coins, UniqueCount) :-
    coins(CoinList),
    find_sequence(Amount, CoinList, [], Coins),
    sort(Coins, UniqueCoins),
    length(UniqueCoins, UniqueCount).

% Build sequence recursively
find_sequence(0, _, Acc, Acc).
find_sequence(Amount, CoinList, Acc, Result) :-
    Amount > 0,
    member(Coin, CoinList),
    check_gcd_with_previous(Coin, Acc),
    NewAmount is Amount - Coin,
    NewAmount >= 0,
    find_sequence(NewAmount, CoinList, [Coin|Acc], Result).

% Check if GCD constraint is satisfied
check_gcd_with_previous(_, []).
check_gcd_with_previous(Coin, [PrevCoin|_]) :-
    gcd(Coin, PrevCoin, 1).
