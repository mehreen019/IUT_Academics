var 1..6: R;
var 1..6: A;
var 1..6: F;
var 1..6: I;
var 1..6: T;
var 1..6: S;

% All must be in different positions
constraint R != A;
constraint R != F;
constraint R != I;
constraint R != T;
constraint R != S;
constraint A != F;
constraint A != I;
constraint A != T;
constraint A != S;
constraint F != I;
constraint F != T;
constraint F != S;
constraint I != T;
constraint I != S;
constraint T != S;

% F is standing in between A and I
constraint (A < F /\ F < I) \/ (I < F /\ F < A);

% S and R are standing next to each other
constraint (S = R + 1) \/ (S = R - 1);

% T is either at the front or at the back
constraint T = 1 \/ T = 6;

% S has exactly one person behind them
constraint S = 5;

solve satisfy;

output [
  "R = ", show(R), "\n",
  "A = ", show(A), "\n",
  "F = ", show(F), "\n",
  "I = ", show(I), "\n",
  "T = ", show(T), "\n",
  "S = ", show(S), "\n"
];
