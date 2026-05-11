% Use this editor as a MiniZinc scratch book
include "globals.mzn";

set of int: HOUSE = 1..5;

enum Color = {red, green, ivory, yellow, blue};
enum Nation = {englishman, spaniard, norwegian, ukrainian, japanese};
enum Candy = {hershey, kitkat, smarties, snickers, milkyways};
enum Drink = {coffee, tea, milk, orangejuice, water};
enum Pet = {dog, fox, horse, snails, zebra};

% houseOfX[value] = which house that value belongs to
array[Color]  of var HOUSE: houseOfColor;
array[Nation] of var HOUSE: houseOfNation;
array[Candy]  of var HOUSE: houseOfCandy;
array[Drink]  of var HOUSE: houseOfDrink;
array[Pet]    of var HOUSE: houseOfPet;

% All categories must occupy different houses
constraint all_different([houseOfColor[c]  | c in Color]);
constraint all_different([houseOfNation[n] | n in Nation]);
constraint all_different([houseOfCandy[c]  | c in Candy]);
constraint all_different([houseOfDrink[d]  | d in Drink]);
constraint all_different([houseOfPet[p]    | p in Pet]);

% Basic clues
constraint houseOfNation[englishman] = houseOfColor[red];
constraint houseOfNation[spaniard]   = houseOfPet[dog];
constraint houseOfNation[norwegian]  = 1;

% Green is immediately right of ivory
constraint houseOfColor[green] = houseOfColor[ivory] + 1;

% Hershey next to fox
constraint abs(houseOfCandy[hershey] - houseOfPet[fox]) = 1;

% KitKat in yellow house
constraint houseOfCandy[kitkat] = houseOfColor[yellow];

% Norwegian next to blue house
constraint abs(houseOfNation[norwegian] - houseOfColor[blue]) = 1;

% Smarties with snails
constraint houseOfCandy[smarties] = houseOfPet[snails];

% Snickers with orange juice
constraint houseOfCandy[snickers] = houseOfDrink[orangejuice];

% Ukrainian drinks tea
constraint houseOfNation[ukrainian] = houseOfDrink[tea];

% Japanese eats Milky Ways
constraint houseOfNation[japanese] = houseOfCandy[milkyways];

% KitKat next to horse
constraint abs(houseOfCandy[kitkat] - houseOfPet[horse]) = 1;

% Coffee in green house
constraint houseOfDrink[coffee] = houseOfColor[green];

% Milk in middle house
constraint houseOfDrink[milk] = 3;

solve satisfy;

output [
"--- Colors ---\n",
"red=" ++ show(houseOfColor[red]) ++
", green=" ++ show(houseOfColor[green]) ++
", ivory=" ++ show(houseOfColor[ivory]) ++
", yellow=" ++ show(houseOfColor[yellow]) ++
", blue=" ++ show(houseOfColor[blue]) ++ "\n\n",

"--- Nationalities ---\n",
"englishman=" ++ show(houseOfNation[englishman]) ++
", spaniard=" ++ show(houseOfNation[spaniard]) ++
", norwegian=" ++ show(houseOfNation[norwegian]) ++
", ukrainian=" ++ show(houseOfNation[ukrainian]) ++
", japanese=" ++ show(houseOfNation[japanese]) ++ "\n\n",

"--- Candy ---\n",
"hershey=" ++ show(houseOfCandy[hershey]) ++
", kitkat=" ++ show(houseOfCandy[kitkat]) ++
", smarties=" ++ show(houseOfCandy[smarties]) ++
", snickers=" ++ show(houseOfCandy[snickers]) ++
", milkyways=" ++ show(houseOfCandy[milkyways]) ++ "\n\n",

"--- Drinks ---\n",
"coffee=" ++ show(houseOfDrink[coffee]) ++
", tea=" ++ show(houseOfDrink[tea]) ++
", milk=" ++ show(houseOfDrink[milk]) ++
", orangejuice=" ++ show(houseOfDrink[orangejuice]) ++
", water=" ++ show(houseOfDrink[water]) ++ "\n\n",

"--- Pets ---\n",
"dog=" ++ show(houseOfPet[dog]) ++
", fox=" ++ show(houseOfPet[fox]) ++
", horse=" ++ show(houseOfPet[horse]) ++
", snails=" ++ show(houseOfPet[snails]) ++
", zebra=" ++ show(houseOfPet[zebra]) ++ "\n"
];