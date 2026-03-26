% TASK 4: Find happiest path maximizing (food value - cost)

% Graph edges: (From, To, Weight)
edges([(a,b,5),(b,c,4),(b,d,2),(c,e,3),(d,e,5),(b,e,5)]).

% Food at each node
foods([(a,pizza),(b,burger),(c,pizza),(d,burger),(e,pizza)]).

% Food happiness values
food_values([(pizza,6),(burger,10)]).

% Main predicate - find path with maximum happiness
happiest_path(Start, End, Path, Cost, Points) :-
    findall([Pts, P, C], find_path_with_happiness(Start, End, P, C, Pts), AllPaths),
    AllPaths \= [],
    sort(1, @>=, AllPaths, [[Points, Path, Cost]|_]),
    Points > 0.

% Find a path and calculate its happiness
find_path_with_happiness(Start, End, Path, Cost, Points) :-
    find_path(Start, End, [Start], ReversePath, Cost),
    reverse(ReversePath, Path),
    calculate_happiness(Path, Cost, Points).

% Find path using depth-first search
find_path(End, End, Acc, Acc, 0).
find_path(Current, End, Visited, Path, Cost) :-
    edges(EdgeList),
    member((Current, Next, Weight), EdgeList),
    \+ member(Next, Visited),
    find_path(Next, End, [Next|Visited], Path, RestCost),
    Cost is RestCost + Weight.

% Calculate happiness = total food value - cost
calculate_happiness(Path, Cost, Points) :-
    calculate_food_value(Path, [], TotalFood),
    Points is TotalFood - Cost.

% Calculate total food value (skip first and last nodes)
calculate_food_value([], _, 0).
calculate_food_value([_], _, 0).  % Single node (start=end)
calculate_food_value([_,Node|Rest], EatenFoods, TotalValue) :-
    Rest \= [],  % Not the last node
    foods(FoodList),
    member((Node, Food), FoodList),
    count_food(Food, EatenFoods, Count),
    food_values(ValueList),
    member((Food, BaseValue), ValueList),
    FoodValue is BaseValue / (Count + 1),
    calculate_food_value([Node|Rest], [Food|EatenFoods], RestValue),
    TotalValue is FoodValue + RestValue.
calculate_food_value([_,Last], _, 0) :-  % Last node gives no food
    !.

% Count occurrences of a food in the list
count_food(_, [], 0).
count_food(Food, [Food|Rest], Count) :-
    count_food(Food, Rest, RestCount),
    Count is RestCount + 1.
count_food(Food, [Other|Rest], Count) :-
    Food \= Other,
    count_food(Food, Rest, Count).
