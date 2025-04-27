#include <stdio.h>

#include "DynamicArray.h"

int main(void)
{
    IntDArrayController controller = IntDArray_New();
    
    puts("--- Intial Condition ---\n");
    IntDArray_Print(&controller);

    for(int i = 0; i < 10; i++)
    {
        IntDArray_Add(&controller, i);
        printf("--- Inserted %d ---\n", i);
        IntDArray_Print(&controller);
    }

    IntDArray_RemoveLast(&controller);
    printf("--- Removed Last Element ---\n");
    IntDArray_Print(&controller);

    printf("--- Setting Out of Range Elements ---\n");
    IntDArray_Set(&controller, 20U, 1);
    IntDArray_Print(&controller);

    printf("--- Fetching Out of Range Elements ---\n");
    printf("%dth element: %d\n", 20, IntDArray_Get(&controller, 20U));

    return 0;
}
