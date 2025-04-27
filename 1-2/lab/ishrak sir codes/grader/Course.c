#include "Course.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Course MakeCourseFromStrings(const char *const tag, const char *const code)
{
    Course course = {0};
    strncpy(course.Tag, tag, MAX_TAG_LEN);
    strncpy(course.Code, code, MAX_CODE_LEN);
    course.Degree = code[0] - '0';
    course.Semester = code[1] - '0';
    course.Number = atoi(code + 2);
    return course;
}

int CompareCourse(const Course *const course1, const Course *const course2)
{
    int tagCmp = strcmp(course1->Tag, course2->Tag);
    return tagCmp ? tagCmp : strcmp(course1->Code, course2->Code);
}

void PrintCourse(const Course *const course)
{
    printf("COURSE: %s %s\n", course->Tag, course->Code);
    printf("|- Degree: %d\n", course->Degree);
    printf("|- Semester: %d\n", course->Semester);
    printf("|- Number: %d\n", course->Number);
}