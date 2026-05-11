% Define edges in the graph
edge(a, b).
edge(b, c).
edge(c, d).
edge(d, e).
edge(e, f).
edge(f, a).
edge(b, f).

% Define a rule for a direct connection between two nodes
connected(X, Y) :- edge(X, Y).
connected(X, Y) :- edge(Y, X).

% Define a recursive rule for a path between two nodes
path(X, Y, Visited) :- 
    connected(X, Y),
    \+ member(Y, Visited).

path(X, Y, Visited) :- 
    connected(X, Z),
    \+ member(Z, Visited),
    path(Z, Y, [X | Visited]).

% Predicate to check if there is a path between two nodes
has_path(X, Y) :- path(X, Y, []).

% Example usage:
% ?- has_path(a, e).
% true.
% ?- has_path(a, d).
% false.

# =====================================================================
# Dynamic database (assert/retract)
% Declare dynamic predicate to track visited nodes
:- dynamic visited/1.

% Graph edges
edge(a, b).
edge(b, c).
edge(c, d).
edge(d, e).
edge(e, f).
edge(f, a).
edge(b, f).

% Undirected connection
connected(X, Y) :- edge(X, Y).
connected(X, Y) :- edge(Y, X).

% Path predicate using dynamic visited/1
path(X, Y) :-
    retractall(visited(_)),   % Clear any previous state
    assert(visited(X)),       % Mark the start node as visited
    traverse(X, Y).

% Recursive traversal without list
traverse(X, Y) :-
    connected(X, Y),
    \+ visited(Y),            % If Y not visited, we found a path
    assert(visited(Y)).       % Mark Y as visited

traverse(X, Y) :-
    connected(X, Z),
    \+ visited(Z),            % If Z not visited
    assert(visited(Z)),       % Mark Z as visited
    traverse(Z, Y).           % Continue traversing toward Y

#======================================================================
% Depth-Limited Search
% Define edges (same as before)
edge(a, b). edge(b, c). edge(c, d). edge(d, e). edge(e, f). edge(f, a). edge(b, f).

% Bidirectional connections
connected(X, Y) :- edge(X, Y).
connected(X, Y) :- edge(Y, X).

% Path with depth limit (prevents infinite loops)
path(X, Y, Depth) :- 
    Depth > 0,
    connected(X, Y).

path(X, Y, Depth) :- 
    Depth > 0,
    connected(X, Z),
    X \= Z,  % Don't go back to same node immediately
    NewDepth is Depth - 1,
    path(Z, Y, NewDepth).

% Check path with reasonable depth limit
has_path(X, Y) :- path(X, Y, 6).  % Max 6 hops

#======================================================================
% Iterative Deepening
% Try increasing depths until path found
has_path(X, Y) :- 
    between(1, 10, Depth),  % Try depths 1 to 10
    path(X, Y, Depth),
    !.  % Cut to stop after first solution

path(X, Y, Depth) :- 
    Depth > 0,
    connected(X, Y).

path(X, Y, Depth) :- 
    Depth > 1,
    connected(X, Z),
    NewDepth is Depth - 1,
    path(Z, Y, NewDepth).
    
#======================================================================
% Iterative Deepening
% Using Cut and Fail (Advanced)
has_path(X, Y) :- 
    path_generate(X, Y, 6).  % Generate paths up to length 6

path_generate(X, Y, Depth) :- 
    Depth > 0,
    connected(X, Y).

path_generate(X, Y, Depth) :- 
    Depth > 1,
    connected(X, Z),
    X \== Y,  % Avoid immediate cycles
    NewDepth is Depth - 1,
    path_generate(Z, Y, NewDepth).    
