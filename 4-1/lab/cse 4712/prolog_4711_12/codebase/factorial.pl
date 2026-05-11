% Define the base case: factorial of 0 is 1
factorial(0, 1).

% Define the recursive rule for calculating factorial
factorial(N, Result) :-
    N > 0,
    N1 is N - 1,
    factorial(N1, SubResult),
    Result is N * SubResult.

% Example usage:
% ?- factorial(5, Result).
% Result = 120.

