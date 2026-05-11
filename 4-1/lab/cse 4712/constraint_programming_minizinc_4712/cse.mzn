include "alldifferent.mzn";

int: n=9;
var 1..n: C;
var 1..n: S;
var 1..n: E;


constraint C*100 + S*10 + E = 9*C*S*E;

solve minimize C*100 + S*10 + E;
% solve satisfy;

output [show(C),show(S),show(E),"\n"];
