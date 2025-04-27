#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

int main(void){
    FILE* ptr;
    float ans= 4.00;
    ptr=fopen("./grades.txt", "r");
    if(ptr==NULL){
        printf("error has occured");
        return 0;
    }
    char buff[20];
    while(fgets(buff, 20, ptr)){
        char* value = strtok(buff, ";");
        value = strtok(NULL, ";");
        float num = atof(value);
        if(num<ans) ans=num;
    }
    printf("%f", ans);

    fclose(ptr);
}