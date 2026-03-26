var 1..3: G;   % Gorontalo
var 1..3: WS;  % West Sulawesi
var 1..3: SS;  % South Sulawesi
var 1..3: CS;  % Central Sulawesi
var 1..3: SES; % Southeast Sulawesi
var 1..3: NS;  % North Sulawesi

constraint G != CS;
constraint G != NS;
constraint WS != SS;
constraint WS != CS;
constraint SS != CS;
constraint SS != SES;
constraint CS != SES;
constraint CS != NS;
constraint NS != CS;

solve satisfy;

output [
  "Gorontalo (G) = ", show(G), "\n",
  "West Sulawesi (WS) = ", show(WS), "\n",
  "South Sulawesi (SS) = ", show(SS), "\n",
  "Central Sulawesi (CS) = ", show(CS), "\n",
  "Southeast Sulawesi (SES) = ", show(SES), "\n",
  "North Sulawesi (NS) = ", show(NS), "\n",
  "Where 1=Red, 2=Yellow, 3=Blue\n"
];
