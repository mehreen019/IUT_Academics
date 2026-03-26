var 1..4: Z;
var 1..4: I;
var 1..4: F;
var 1..4: N;

% Z does not like Paratha
constraint Z != 4;

% I and F want different dishes
constraint I != F;

% F likes Rice items
constraint F = 1 \/ F = 2;

% Z copies I but different from the rest
constraint Z = I;
constraint Z != F;
constraint Z != N;

% N will not order Kashmiri Naan
constraint N != 3;

solve satisfy;

output [
  "Z = ", show(Z), "\n",
  "I = ", show(I), "\n",
  "F = ", show(F), "\n",
  "N = ", show(N), "\n",
  "Where 1=Special Rice, 2=Biriyani Rice, 3=Kashmiri Naan, 4=Paratha \n"
];