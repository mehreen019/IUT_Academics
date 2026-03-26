var 1..3: A;
var 1..3: S;
var 1..3: M;
var 1..3: R;

% A and S must not live on the same floor
constraint A != S;

% If A and M live on the same floor, they must both be on floor 2
constraint (A = M) -> (A = 2 /\ M = 2);

% If A and M live on different floors, one must be on floor 3
constraint (A != M) -> (A = 3 \/ M = 3);

% R must not live on the same floor as anyone else
constraint R != A;
constraint R != S;
constraint R != M;

% R must live on a higher floor than M
constraint R > M;

solve satisfy;

output [
  "A = ", show(A), "\n",
  "S = ", show(S), "\n",
  "M = ", show(M), "\n",
  "R = ", show(R), "\n"
];