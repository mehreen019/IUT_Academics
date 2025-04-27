#include <stdio.h>
#include <fstream>

#define NAME_LEN 21

#define STUDENT_FILE "./StudentArrayInfo.bin"

typedef struct _student
{
    char Name[NAME_LEN];
    int ID;
    float CGPA;
} Student;

void PrintStudent(const Student* const std);
void WriteStudentArray(FILE* fp, const Student* const stdArr, int length);
void ReadStudentArray(FILE* fp, Student* const stdArr, int length);


int main(void)
{
    // Keep either Writing or Reading logic uncommented, not both

    // ---------- Uncomment the following code for Block Writing ----------

    // Student stdArr[3] = {
    //     {"StdA", 101, 3.97},
    //     {"StdB", 102, 3.55},
    //     {"StdC", 105, 3.88}
    // };

    // FILE* fp = fopen(STUDENT_FILE, "wb");

    // if(fp == NULL)
    // {
    //     printf("Failed to open the file <%s>\n", STUDENT_FILE);
    // }
    // else
    // {
    //     WriteStudentArray(fp, stdArr, 3);
    //     fclose(fp);
    // }

    // ---------- Uncomment the following code for Block Reading ----------

    Student stdArr[3];

    FILE* fp = fopen(STUDENT_FILE, "rb");

    if(fp == NULL)
    {
        printf("Failed to open the file <%s>\n", STUDENT_FILE);
    }
    else
    {
        ReadStudentArray(fp, stdArr, 3);
        fclose(fp);
    }

    // The following code can remain uncommented always, for printing the student values
    for(int i = 0; i < 3; i++)
    {
        PrintStudent(&stdArr[i]);
    }

    return 0;
}

void PrintStudent(const Student* const std)
{
    printf("Name : %s\n", std->Name);
    printf("ID : %d\n", std->ID);
    printf("CGPA : %f\n", std->CGPA);
}

void WriteStudentArray(FILE* fp, const Student* const stdArr, int length)
{
    fwrite(stdArr, sizeof(Student), length, fp);
}

void ReadStudentArray(FILE* fp, Student* const stdArr, int length)
{
    fread(stdArr, sizeof(Student), length, fp);
}