edge(a,b).
edge(a,e).
edge(b,d).
edge(b,c).
edge(c,m).
edge(e,b).

path(Node1,Node2) :-
	edge(Node1,Node2).
path(Node1,Node2) :-
	edge(Node1,SomeNode),
	path(SomeNode,Node2).


/*
uedge(Node1,Node2) :-
	edge(Node1,Node2);
    edge(Node2,Node1).
*/



