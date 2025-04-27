#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "DynamicGradeList.h"

#define SAVE_PATH "./SaveData.bin"

#define CMDSTR_LIST     "list"
#define CMDSTR_ADD      "add"
#define CMDSTR_REMOVE   "remove"
#define CMDSTR_FIND     "find"
#define CMDSTR_GPA      "gpa"
#define CMDSTR_HELP     "help"

DynamicGradeList gradeList;

void ListGrades(void);
void AddGrade(const char *const course, const char *const code, float gp);
void RemoveGrade(const char *const course, const char *const code);
void FindGrade(const char *const course, const char *const code);
void GetGPA(void);
void PrintCommandList(void);

int main(int argc, char **argv)
{
    gradeList = DynamicGradeList_Make();   
    DynamicGradeList_Deserialize(&gradeList, SAVE_PATH);

    if(argc < 2)
    {
        PrintCommandList();
        exit(EXIT_FAILURE);
    }
    
    if(!strcmp(argv[1], CMDSTR_LIST))
    {
        ListGrades();
    }
    else if(!strcmp(argv[1], CMDSTR_ADD))
    {
        assert(argc == 5);
        AddGrade(argv[2], argv[3], atof(argv[4]));
    }
    else if(!strcmp(argv[1], CMDSTR_REMOVE))
    {
        assert(argc == 4);
        RemoveGrade(argv[2], argv[3]);
    }
    else if(!strcmp(argv[1], CMDSTR_FIND))
    {
        assert(argc == 4);
        FindGrade(argv[2], argv[3]);
    }
    else if(!strcmp(argv[1], CMDSTR_GPA))
    {
        GetGPA();
    }
    else if(!strcmp(argv[1], CMDSTR_HELP))
    {
        PrintCommandList();
    }
    else
    {
        PrintCommandList();
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

void ListGrades(void)
{
    printf("[Listing Grades]\n");
    DynamicGradeList_Print(&gradeList);
}

void AddGrade(const char *const course, const char *const code, float gp)
{
    Course courseInfo = MakeCourseFromStrings(course, code);
    DynamicGradeList_AddElement
    (
        &gradeList, MakeGrade(courseInfo, gp)
    );
    DynamicGradeList_Serialize(&gradeList, SAVE_PATH);
    printf("[Added Grade For]\n");
    PrintCourse(&courseInfo);
    printf("|- GP: %.2f\n", gp);
}

void RemoveGrade(const char *const course, const char *const code)
{
    Course courseInfo = MakeCourseFromStrings(course, code);
    if(DynamicGradeList_RemoveElement
    (
        &gradeList, DynamicGradeList_Find(&gradeList, courseInfo)
    ))
    {
        DynamicGradeList_Serialize(&gradeList, SAVE_PATH);
        printf("[Removed Grade For]\n");
        PrintCourse(&courseInfo);
    }
    else
    {
        printf("[!FAILED to Remove Grade For]\n");
        PrintCourse(&courseInfo);
    }
}

void FindGrade(const char *const course, const char *const code)
{
    Course courseInfo = MakeCourseFromStrings(course, code);
    long long index = DynamicGradeList_Find(&gradeList, courseInfo);
    if(index >= 0)
    {
        printf("[Found Grade]\n");
        PrintGrade(&gradeList.Elements[index]);
    }
    else
    {
        printf("[!FAILED to Find Grade For]\n");
        PrintCourse(&courseInfo);
    }
}

void GetGPA(void)
{
    float GPA = 0.0;
    for(size_t i = 0; i < gradeList.Count; i++)
    {
        GPA += gradeList.Elements[i].GradePoint;
    }
    GPA /= gradeList.Count;
    printf("[GPA]: %.2f\n", GPA);
}

void PrintCommandList(void)
{
    printf("Use one of the following commands:\n");
    printf("<%s> for listing new course\n", CMDSTR_LIST);
    printf("<%s> <COURSE> <CODE> <GPA> for adding new course\n", CMDSTR_ADD);
    printf("<%s> <COURSE> <CODE> for removing an existing course\n", CMDSTR_REMOVE);
    printf("<%s> <COURSE> <CODE> for finding an existing course\n", CMDSTR_FIND);
    printf("<%s> for calculating GPA\n", CMDSTR_GPA);
    printf("<%s> for getting this help document\n", CMDSTR_HELP);
}