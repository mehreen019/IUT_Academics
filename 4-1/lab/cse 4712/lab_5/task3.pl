student(alice, 100, 70, 90).
student(bob, 80, 80, 80).
student(charlie, 100, 50, 100).
student(diana, 70, 70, 70).

subject_grade(Marks, 'A') :- Marks >= 90, !.
subject_grade(Marks, 'B') :- Marks >= 80, !.
subject_grade(Marks, 'C') :- Marks >= 70, !.
subject_grade(Marks, 'D') :- Marks >= 60, !.
subject_grade(_, 'F').

rank_students(RankedList) :-
    findall([LowestGrade, NegTotal, Name], 
            (student_stats(Name, LowestGrade, Total), NegTotal is -Total), 
            StudentList),
    sort(0, @=<, StudentList, Sorted),
    fix_totals(Sorted, RankedList).

student_stats(Name, LowestGrade, Total) :-
    student(Name, Mark1, Mark2, Mark3),
    Total is Mark1 + Mark2 + Mark3,
    subject_grade(Mark1, Grade1),
    subject_grade(Mark2, Grade2),
    subject_grade(Mark3, Grade3),
    find_lowest_grade([Grade1, Grade2, Grade3], LowestGrade).

% Convert negative totals back to positive
fix_totals([], []).
fix_totals([[Grade, NegTotal, Name]|Rest], [[Grade, Total, Name]|Fixed]) :-
    Total is -NegTotal,
    fix_totals(Rest, Fixed).

find_lowest_grade([G1, G2, G3], Lowest) :-
    sort([G1, G2, G3], Sorted),
    reverse(Sorted, [Lowest|_]).

%rank_students(R).