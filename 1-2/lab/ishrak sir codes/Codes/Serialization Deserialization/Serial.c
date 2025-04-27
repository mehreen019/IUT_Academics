#include <stdio.h>

#define NAME_LEN 21

#define STUDENT_FILE "./StudentInfo.txt"

typedef struct _student
{
    char Name[NAME_LEN];
    int ID;
    float CGPA;
} Student;

void SerializeStudent(FILE* fp, const Student * const std);
void DeserializeStudent(FILE* fp, Student * const std);
void PrintStudent(const Student* const std);

int main(void)
{
    // Keep either Serialization or Deserialization logic uncommented, not both
    // In real life application, reading and writing will be controlled by your
    // logic and cases, generally using if ... else statements or switch cases

    // ---------- Uncomment the following code for Serialization (Saving) ----------

    // Student std = { "StdA" , 101, 4.00 };

    // FILE* fp = fopen(STUDENT_FILE, "w");

    // if(fp == NULL)
    // {
    //     printf("Failed to open the file <%s>\n", STUDENT_FILE);
    // }
    // else
    // {
    //     SerializeStudent(fp, &std);
    // }
    // PrintStudent(&std);



    // ---------- Uncomment the following code for Deserialization (Loading) ----------
    Student stdx;

    FILE* fp = fopen(STUDENT_FILE, "r");

    if(fp == NULL)
    {
        printf("Failed to open the file <%s>\n", STUDENT_FILE);
    }
    else
    {
        DeserializeStudent(fp, &stdx);
        fclose(fp);
    }
    PrintStudent(&stdx);

    return 0;
}

void SerializeStudent(FILE* fp, const Student * const std)
{
    fprintf(fp, "Name : %s\n", std->Name);
    fprintf(fp, "ID : %d\n", std->ID);
    fprintf(fp, "CGPA : %f\n", std->CGPA);
}

void DeserializeStudent(FILE* fp, Student * const std)
{
    fscanf(fp, " Name : %s", std->Name);
    fscanf(fp, " ID : %d", &std->ID);
    fscanf(fp, " CGPA : %f", &std->CGPA);
}

void PrintStudent(const Student* const std)
{
    printf("Name : %s\n", std->Name);
    printf("ID : %d\n", std->ID);
    printf("CGPA : %f\n", std->CGPA);
}