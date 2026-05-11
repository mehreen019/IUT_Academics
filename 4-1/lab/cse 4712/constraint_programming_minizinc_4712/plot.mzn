% Grain types
enum GRAINS = {BARLEY, CORN, MILLET, OATS, RYE, SPELT, WHEAT};

% Number of plots and grains
int: n_plots = 7;
int: n_grains = 7;
set of int: PLOTS = 1..n_plots;

% Decision variable: which grains are planted in each plot
array[PLOTS] of var set of GRAINS: plots;

% Constraints:

% 1. Each plot grows exactly 3 grains
constraint forall(p in PLOTS)(card(plots[p]) == 3);

% 2. Each grain is grown in exactly 3 plots
constraint forall(g in GRAINS)(
    sum([bool2int(g in plots[p]) | p in PLOTS]) == 3
);

% 3. Every pair of grains appears together in exactly 1 plot
constraint forall(g1, g2 in GRAINS where g1 != g2)(
    sum([bool2int({g1,g2} subset plots[p]) | p in PLOTS]) == 1
);

% Solve (no objective needed, just find feasible solution)
solve satisfy;

% Output the solution
output [
    "Plot " ++ show(p) ++ ": " ++ show(plots[p]) ++ "\n"
    | p in PLOTS
];
