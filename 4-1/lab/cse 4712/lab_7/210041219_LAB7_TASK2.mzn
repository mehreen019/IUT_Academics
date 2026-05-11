include "globals.mzn";

set of int: T = 1..4;

enum PERSON = {X, Y};
enum TASK = {G, Q, C, D, L};

array[TASK] of var T: start;
array[TASK] of var PERSON: who;

constraint start[Q] <= 3;
constraint start[L] <= 3;

constraint who[G] = X;

constraint start[C] < start[L];
constraint start[G] < start[D];

constraint start[D] <= 2;

constraint who[D] != who[L];
constraint who[L] = who[C];

constraint forall(p in PERSON, t in T)(
  bool2int(who[G]=p /\ start[G]=t) +
  bool2int(who[C]=p /\ start[C]=t) +
  bool2int(who[D]=p /\ start[D]=t) +
  bool2int(who[Q]=p /\ (start[Q]=t \/ start[Q]=t-1)) +
  bool2int(who[L]=p /\ (start[L]=t \/ start[L]=t-1))
  <= 1
);

constraint forall(t in T)(
  (t = start[D]) ->
  (
    bool2int(who[G]=X /\ start[G]=t) +
    bool2int(who[C]=X /\ start[C]=t) +
    bool2int(who[D]=X /\ start[D]=t) +
    bool2int(who[Q]=X /\ (start[Q]=t \/ start[Q]=t-1)) +
    bool2int(who[L]=X /\ (start[L]=t \/ start[L]=t-1)) +
    bool2int(who[G]=Y /\ start[G]=t) +
    bool2int(who[C]=Y /\ start[C]=t) +
    bool2int(who[D]=Y /\ start[D]=t) +
    bool2int(who[Q]=Y /\ (start[Q]=t \/ start[Q]=t-1)) +
    bool2int(who[L]=Y /\ (start[L]=t \/ start[L]=t-1))
    = 1
  )
);

solve satisfy;

output [
"G: start=" ++ show(start[G]) ++ " who=" ++ show(who[G]) ++ "\n",
"Q: start=" ++ show(start[Q]) ++ " who=" ++ show(who[Q]) ++ "\n",
"C: start=" ++ show(start[C]) ++ " who=" ++ show(who[C]) ++ "\n",
"D: start=" ++ show(start[D]) ++ " who=" ++ show(who[D]) ++ "\n",
"L: start=" ++ show(start[L]) ++ " who=" ++ show(who[L]) ++ "\n"
];