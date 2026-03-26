age(max, 25).
age(norris, 21).
age(oscar, 22).

name_is(1, max).
name_is(2, norris).
name_is(3, oscar).

likes(max, pizza).
likes(lando, pizza).
likes(oscar, apples).
likes(max, ice_cream).

%rule - works like a function. returns only true/false
% , - AND, ; - OR
happy(X):- likes(X, pizza), likes(X, ice_cream).