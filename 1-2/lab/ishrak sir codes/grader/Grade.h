#pragma once

#include "Course.h"

typedef struct grade
{
    Course CourseInfo;
    float GradePoint;
} Grade;

Grade MakeGrade(Course course, float gradePoint);
void PrintGrade(const Grade *const grade);
