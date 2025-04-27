#include<stdio.h>
#pragma once

#define MAX_CITY_LEN    10
#define MAX_COUNTRY_LEN 10
#define MAX_NAME_LEN    20

typedef struct _address
{
    int     HouseNumber;
    int     RoadNumber;
    char    City[MAX_CITY_LEN + 1];
    char    Country[MAX_COUNTRY_LEN + 1];
    int     ZipCode;
} Address;


typedef struct _studentInfo
{
    char    Name[MAX_NAME_LEN + 1];
    int     ID;
    float   CGPA;
    Address PresentAddress;
    Address PermanentAddress;
} StudentInfo;

void takeinput(const StudentInfo const *st){
    scanf("%s", st->Name);
    scanf("%d", &st->ID);
    scanf("%f", &st->CGPA);
    scanf("%d", &st->PresentAddress.HouseNumber);
    scanf("%d", &st->PresentAddress.RoadNumber);
    scanf("%d", &st->PresentAddress.ZipCode);
    scanf("%s", st->PresentAddress.City);
    scanf("%s", st->PresentAddress.Country);
    scanf("%d", &st->PermanentAddress.HouseNumber);
    scanf("%d", &st->PermanentAddress.RoadNumber);
    scanf("%d", &st->PermanentAddress.ZipCode);
    scanf("%s", st->PermanentAddress.City);
    scanf("%s", st->PermanentAddress.Country);
}

void print(const StudentInfo const *st){
    printf("%s\n", st->Name);
    printf("%d\n", st->ID);
    printf("%f\n", st->CGPA);
    printf("%d\n", st->PresentAddress.HouseNumber);
    printf("%d\n", st->PresentAddress.RoadNumber);
    printf("%d\n", st->PresentAddress.ZipCode);
    printf("%s\n", st->PresentAddress.City);
    printf("%s\n", st->PresentAddress.Country);
    printf("%d\n", st->PermanentAddress.HouseNumber);
    printf("%d\n", st->PermanentAddress.RoadNumber);
    printf("%d\n", st->PermanentAddress.ZipCode);
    printf("%s\n", st->PermanentAddress.City);
    printf("%s\n", st->PermanentAddress.Country);
}

void SerializeStudent(FILE* fp, const StudentInfo* const st){
    fprintf(fp, "%s\n", st->Name);
    fprintf(fp, "%d\n", st->ID);
    fprintf(fp, "%f\n", st->CGPA);
    fprintf(fp, "%d\n", st->PresentAddress.HouseNumber);
    fprintf(fp, "%d\n", st->PresentAddress.RoadNumber);
    fprintf(fp, "%d\n", st->PresentAddress.ZipCode);
    fprintf(fp, "%s\n", st->PresentAddress.City);
    fprintf(fp,"%s\n", st->PresentAddress.Country);
    fprintf(fp, "%d\n", st->PermanentAddress.HouseNumber);
    fprintf(fp,"%d\n", st->PermanentAddress.RoadNumber);
    fprintf(fp,"%d\n", st->PermanentAddress.ZipCode);
    fprintf(fp,"%s\n", st->PermanentAddress.City);
    fprintf(fp, "%s\n", st->PermanentAddress.Country);
}

void DeserializeStudent(FILE* fp, const StudentInfo const *stdx){
    fscanf(fp,"%s", stdx->Name);
    fscanf(fp,"%d", &stdx->ID);
    fscanf(fp,"%f", &stdx->CGPA);
    fscanf(fp,"%d", &stdx->PresentAddress.HouseNumber);
    fscanf(fp,"%d", &stdx->PresentAddress.RoadNumber);
    fscanf(fp,"%d", &stdx->PresentAddress.ZipCode);
    fscanf(fp,"%s", stdx->PresentAddress.City);
    fscanf(fp,"%s", stdx->PresentAddress.Country);
    fscanf(fp,"%d", &stdx->PermanentAddress.HouseNumber);
    fscanf(fp,"%d", &stdx->PermanentAddress.RoadNumber);
    fscanf(fp,"%d", &stdx->PermanentAddress.ZipCode);
    fscanf(fp,"%s", stdx->PermanentAddress.City);
    fscanf(fp,"%s", stdx->PermanentAddress.Country);
}


int main(void){
    StudentInfo st, stdx;
    //takeinput(&st); //for serialization
    FILE *fp=fopen("MAIN_FILE.txt", "r"); //w+ mode for serialization
    if(fp==NULL){
        printf("[ERROR] Couldn't open <%s>\n", "MAIN_FILE.txt");
    }
    else{
        //SerializeStudent(fp, &st);
        DeserializeStudent(fp, &stdx);
        fclose(fp);
    }
    print(&stdx); //will comment this out for serialization
}
