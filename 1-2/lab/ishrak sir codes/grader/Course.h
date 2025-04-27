#pragma once

#define MAX_TAG_LEN 5
#define MAX_CODE_LEN 4

typedef struct course
{
    char Tag[MAX_TAG_LEN + 1];
    char Code[MAX_CODE_LEN + 1];
    int Degree;
    int Semester;
    int Number;
} Course;

Course MakeCourseFromStrings(const char *const tag, const char *const code);
int CompareCourse(const Course *const course1, const Course *const course2);
void PrintCourse(const Course *const course);