#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "exp.h"
#include "Struct.h"

int main(int argc, char *argv[])
{
    IntDArrayController controller = IntDArray_New();

    IntDArray_Print(&controller);
    Month m;
    FILE *fp=fopen("MAIN_FILE.txt", "r");
    if(fp==NULL){
        printf("[ERROR] Couldn't open <%s>\n", "MAIN_FILE.txt");
    }
    else{
        IntDArray_Read(fp, &m);
        IntDArray_Add(&controller, m);
        fclose(fp);
    }
    IntDArray_Print(&controller);
    if(strcmp(argv[1],"list")==0){
        IntDArray_Print(&controller);
    }
    if(argv[1]=="find_by_month")
        //IntDArray_FindByMonth(&controller, (atoi)argv[2]);
    if(argv[1]=="summary"){
        //int income=IntDArray_GetIncomeAmount(&controller, (atoi)argv[2]);
        //int expense=IntDArray_GetExpenseAmount(&controller, (atoi)argv[2]);
        //printf("%d", income);
        //printf("%d", expense);
    }

}
    