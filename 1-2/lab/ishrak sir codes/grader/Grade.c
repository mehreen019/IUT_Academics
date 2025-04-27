#include "Grade.h"

#include <stdio.h>

Grade MakeGrade(Course course, float gradePoint)
{
    return (Grade){.CourseInfo = course, .GradePoint = gradePoint};
}

void PrintGrade(const Grade *const grade)
{
    printf(">> %4s %4s %.2f\n",
        grade->CourseInfo.Tag,
        grade->CourseInfo.Code,
        grade->GradePoint);
}