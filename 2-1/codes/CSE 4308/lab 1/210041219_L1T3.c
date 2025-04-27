#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

int main(void){
    FILE* ptr;
    FILE* grd;
    float low_grade= 4.00;
    int ID,check=0,sem;
    ptr=fopen("./studentInfo.txt", "r");
    grd=fopen("./grades.txt", "r");

    if(ptr==NULL || grd==NULL){
        printf("error has occured");
        return 0;
    }

    printf("enter student id:");
    scanf("%d", &ID);

    char buff[20];
    while(fgets(buff, 20, ptr)){
        char* value = strtok(buff, ";");
        if(atoi(value)==ID){
            value = strtok(NULL, ";");
            printf("%s\n", value);
            check=1;
            break;
        }
    }

    if(!check){
        printf("student id couldn't be found");
        return 0;
    }

    while(fgets(buff, 20, grd)){
        char* value = strtok(buff, ";");
        if(atoi(value)==ID){
            value = strtok(NULL, ";");
            if(atof(value)<low_grade){
                low_grade=atof(value);
                value = strtok(NULL, ";");
                sem= atoi(value);
            }
        }
    }
    
    printf("lowest grade is in %d semester", sem);

    fclose(ptr);
}