int: n=4;
array [1..n] of var 1..n: q; % queen in column i is in row q[i]

include "alldifferent.mzn";

constraint alldifferent(q);                       % distinct rows
% constraint alldifferent([ q[i] + i | i in 1..n]); % distinct upward diagonals
% constraint alldifferent([ q[i] - i | i in 1..n]); % distinct downward diagonals
constraint forall(i,j in 1..n where i<j)(abs(q[i]-q[j]) != abs(i-j));

% search
solve satisfy;
output [ if fix(q[j]) == i then "Q" else "." endif ++
         if j == n then "\n" else "" endif | i,j in 1..n]

