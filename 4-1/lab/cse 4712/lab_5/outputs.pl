% =====================================================================
% OUTPUTS FOR ALL 4 TASKS
% =====================================================================

% =====================================================================
% TASK 1 OUTPUT
% =====================================================================
% Query: change(18, Coins, UniqueCoins).
% Expected Output:
% Coins = [2, 5, 1, 10]
% UniqueCoins = 4
%
% Explanation:
% - The sequence [2, 5, 1, 10] sums to 18
% - All consecutive pairs have GCD = 1:
%   - gcd(2, 5) = 1
%   - gcd(5, 1) = 1
%   - gcd(1, 10) = 1
% - It has 4 unique coins: {1, 2, 5, 10}
% - Another valid sequence [1,5,1,5,1,5] only has 2 unique coins
% =====================================================================

% =====================================================================
% TASK 2 OUTPUT
% =====================================================================
% Query: change_limited(14, 4, 5, Coins, Sum).
% Expected Output:
% Coins = [(1,0),(2,2),(5,2),(10,0)]
% Sum = 4
% Coins = [(1,2),(2,1),(5,0),(10,1)]
% Sum = 4
% Coins = [(1,2),(2,1),(5,2),(10,0)]
% Sum = 5
% Coins = [(1,4),(2,0),(5,0),(10,1)]
% Sum = 5
% true
%
% Explanation:
% - All combinations that sum to 14 using available coins
% - Each coin type has stock limits: 1(max 5), 2(max 3), 5(max 2), 10(max 2)
% - Total number of coins must be between 4 and 5
% - The fail operator forces backtracking to find all solutions
% =====================================================================

% =====================================================================
% TASK 3 OUTPUT
% =====================================================================
% Query: rank_students(R).
% Expected Output:
% R = [['B', 240, bob],
%      ['C', 260, alice],
%      ['C', 210, diana],
%      ['F', 250, charlie]]
%
% Explanation:
% Student Details:
% - alice: (100, 70, 90) -> Grades: (A, C, A) -> Lowest: C, Total: 260
% - bob: (80, 80, 80) -> Grades: (B, B, B) -> Lowest: B, Total: 240
% - charlie: (100, 50, 100) -> Grades: (A, F, A) -> Lowest: F, Total: 250
% - diana: (70, 70, 70) -> Grades: (C, C, C) -> Lowest: C, Total: 210
%
% Ranking Rules:
% 1. Higher lowest grade ranks higher: B > C > F
% 2. If lowest grades are equal, higher total ranks higher
%
% Final Ranking:
% 1. bob: Lowest grade B (highest), Total 240
% 2. alice: Lowest grade C, Total 260 (higher than diana)
% 3. diana: Lowest grade C, Total 210
% 4. charlie: Lowest grade F (lowest), Total 250
%
% Note: subject_grade is rewritten using cut operator (!) to prevent
% backtracking once a grade is determined.
% =====================================================================

% =====================================================================
% TASK 4 OUTPUT
% =====================================================================
% Query: happiest_path(a, e, Path, Cost, Points).
% Expected Output:
% Path = [a, b, c, e]
% Cost = 12
% Points = 4
%
% Explanation:
% Path Analysis:
% 1. Path [a,b,d,e]:
%    - Cost: 5 + 2 + 5 = 12
%    - Foods eaten: burger at b (10 points), burger at d (10/2 = 5 points)
%    - Total food value: 10 + 5 = 15
%    - Points: 15 - 12 = 3
%
% 2. Path [a,b,c,e]: *** OPTIMAL ***
%    - Cost: 5 + 4 + 3 = 12
%    - Foods eaten: burger at b (10 points), pizza at c (6 points)
%    - Total food value: 10 + 6 = 16
%    - Points: 16 - 12 = 4
%
% 3. Path [a,b,e]:
%    - Cost: 5 + 5 = 10
%    - Foods eaten: burger at b (10 points)
%    - Total food value: 10
%    - Points: 10 - 10 = 0
%
% The path [a,b,c,e] maximizes happiness with 4 points.
%
% Key Points:
% - Start node (a) and end node (e) don't give food
% - When same food is eaten multiple times, value decreases:
%   First time: full value, nth time: value/n
% - Points = (Total Food Value) - Cost
% =====================================================================

% =====================================================================
% HOW TO TEST
% =====================================================================
% To test each task, load the respective file and run the query:
%
% Task 1:
% ?- [task1].
% ?- change(18, Coins, UniqueCoins).
%
% Task 2:
% ?- [task2].
% ?- change_limited(14, 4, 5, Coins, Sum).
%
% Task 3:
% ?- [task3].
% ?- rank_students(R).
%
% Task 4:
% ?- [task4].
% ?- happiest_path(a, e, Path, Cost, Points).
% =====================================================================
