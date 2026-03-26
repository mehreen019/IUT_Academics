parent( alice , bob).
parent( bob , charlie).
parent( alice , diana).
parent( diana , eric).

grandparent(X, Z):- 
	parent(Y, X),
	parent(Z, Y).

%Who are Charlie’s grandparents?
grandparent(charlie, X).

%Is Alice a grandparent of Eric?
grandparent(eric, alice).

%List the grandsons of Alice.
grandparent(X, alice).
	

