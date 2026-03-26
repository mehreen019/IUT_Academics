% TASK 2: Find all valid coin combinations using fail operator

% Available coins and their stock limits
coins([1,2,5,10]).
stock([(1,5),(2,3),(5,2),(10,2)]).

% Main predicate - uses fail to explore all possibilities
change_limited(Amount, LowLimit, HighLimit, Coins, Sum) :-
    stock(Stock),
    generate_combination(Stock, Amount, Coins, Sum),
    Sum >= LowLimit,
    Sum =< HighLimit,
    write('Coins = '), writeln(Coins),
    write('Sum = '), writeln(Sum),
    fail.
change_limited(_, _, _, _, _).

% Generate a combination of coins that sums to Amount
generate_combination([], 0, [], 0).
generate_combination([(Coin, MaxQty)|Rest], Amount, [(Coin, Qty)|RestCoins], Sum) :-
    between(0, MaxQty, Qty),
    CoinValue is Coin * Qty,
    CoinValue =< Amount,
    RemainingAmount is Amount - CoinValue,
    generate_combination(Rest, RemainingAmount, RestCoins, RestSum),
    Sum is Qty + RestSum.
