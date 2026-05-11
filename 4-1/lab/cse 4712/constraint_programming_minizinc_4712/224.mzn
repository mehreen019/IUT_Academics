% Cryptarithmetic puzzle: TWO + TWO = FOUR

include "alldifferent.mzn";

% Variables: letters representing digits
var 0..9: T;
var 0..9: W;
var 0..9: O;
var 0..9: F;
var 0..9: U;
var 0..9: R;

% Carry variables
var 0..1: C1;  % Carry from ones place
var 0..1: C10; % Carry from tens place

% Constraints
constraint alldifferent([T, W, O, F, U, R]);

% Leading digits can't be zero
constraint T != 0;
constraint F != 0;

% Addition constraints
constraint (O + O) == R + 10 * C1;
constraint (W + W + C1) == U + 10 * C10;
constraint (T + T + C10) == O + 10 * F;

solve satisfy;
% solve maximize F*1000 + O*100 + U*10 + R;


output ["   \(T)\(W)\(O)\n",
        " + \(T)\(W)\(O)\n",
        "-------\n",
        " = \(F)\(O)\(U)\(R)\n",
        "\nSolution: T=\(T), W=\(W), O=\(O), F=\(F), U=\(U), R=\(R)"];
