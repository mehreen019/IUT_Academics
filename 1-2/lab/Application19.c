#include <stdio.h>
#include <stddef.h>
#include "DynamicArray19.h"
#include "StudentInfo.h"

int main(void)
{
    IntDArrayController controller = IntDArray_New();
    
    puts("--- Intial Condition ---\n");
    IntDArray_Print(&controller);
    for(int i=0;i<10;i++){
        StudentInfo t={ "anon",2100412+i, 3.50+i , {12+i,1+i,"dhaka","bangladesh",1230} , {11+i,56+i,"dhaka","bangladesh", 234}};
        IntDArray_Add(&controller, t);
        printf("--- Inserted %d---\n",i);
        IntDArray_Print(&controller);
    }

    IntDArray_RemoveLast(&controller);
    printf("--- Removed Last Element ---\n");
    IntDArray_Print(&controller);

    StudentInfo t={ "anon",210041229, 4.00 , {12,1,"dhaka","bangladesh",1230} , {11,56,"dhaka","bangladesh", 234}};
    
    printf("--- Setting Out of Range Elements ---\n");
    IntDArray_Set(&controller, 20U, t);
    IntDArray_Print(&controller);

    printf("--- Fetching Out of Range Elements ---\n");
    printf("%dth element: %d\n", 20, IntDArray_Get(&controller, 20U));

    //TASK 2

    printf("---After Removing Element at %d index---\n", 7); 
    IntDArray_Remove(&controller, 7U);
    IntDArray_Print(&controller);

    printf("Inserting element at %d index\n", 3);
    IntDArray_Insert(&controller, 3U, t);
    IntDArray_Print(&controller);
    
    printf("---Finding an element via pointer---\n");
    printf("Element is at index %d\n", IntDArray_Find(&controller, &t));

    printf("--Sorting array based on CGPA then ID---\n");
    printf("-Ascending:\n");
    IntDArray_Sort(&controller, 1);
    IntDArray_Print(&controller);
    printf("-Descending:\n");
    IntDArray_Sort(&controller,0);
    IntDArray_Print(&controller);

    printf("---After clearing---\n");
    IntDArray_Clear(&controller);
    IntDArray_Print(&controller);
    
    return 0;
}
