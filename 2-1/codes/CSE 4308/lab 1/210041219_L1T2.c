#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

struct Info{
    int ID;
    float CGPA;
    int sem;
}info;

int main(void){
    FILE* ptr;
    float ans= 4.00;
    ptr=fopen("./grades.txt", "a+");
    if(ptr==NULL){
        printf("error has occured");
        return 0;
    }
    printf("enter student id: ");
    scanf("%d", &info.ID);
    printf("enter cgpa: ");
    scanf("%f", &info.CGPA);
    printf("enter semester: ");
    scanf("%d", &info.sem);

    if(info.CGPA<2.5 || info.CGPA>4.00 || info.sem>8){
        printf("INVALID INFO");
    }
    else{
        fprintf(ptr, "%d;%f;%d", info.ID, info.CGPA, info.sem);
    }

    fclose(ptr);

}