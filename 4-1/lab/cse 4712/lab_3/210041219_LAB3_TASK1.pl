parent( alice , bob).
parent( bob , charlie).
parent( alice , diana).
parent( diana , eric).

sibling(alice, lando).
sibling(eric, oscar).
sibling(bob, max).

gender(alice, female).
gender(bob, male).
gender(charlie, male).
gender(diana, female).
gender(eric, male).

age(alice, 70).
age(bob, 30).
age(charlie, 15).
age(diana, 35).
age(eric, 10).

%Who are Alice’s children?
parent(alice, X).

%Who are Bob’s parents?
parent(X, bob).

%List all people with the age of 30.
age(X, 30).

%List all the men.
gender(X, male).