#include "DynamicArray.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/// @brief An internal function to grow the allocated memory when required, should not be called explicitly
/// @param controller Pointer to the controller to grow
/// @return 1 if successful, 0 if failed
int IntDArray_Grow(IntDArrayController *restrict controller);

IntDArrayController IntDArray_New(void)
{
    IntDArrayController controller = (IntDArrayController)
    {
        .Elements = NULL,
        .Count = 0U,
        .Capacity = DEFAULT_INIT_CAPACITY
    };

    controller.Elements = ( int * )malloc(controller.Capacity * sizeof(int));

    if(controller.Elements == NULL)
        exit(1);
    
    return controller; 
}

void IntDArray_Free(IntDArrayController *restrict controller)
{
    free(controller->Elements);
    controller->Capacity = 0U;
    controller->Count = 0U;
}

int IntDArray_Grow(IntDArrayController *restrict controller)
{
    int* requested = ( int * )realloc
    (
        controller->Elements,
        controller->Capacity * 2 * sizeof(int)
    );
    if(requested == NULL)
    {
        return 0;
    }
    else
    {
        controller->Elements = requested;
        controller->Capacity *= 2;
        return 1;
    }
}

int IntDArray_Add(IntDArrayController *restrict controller, int element)
{
    if(controller->Capacity == 0U) return -1;
    if(controller->Count < controller->Capacity)
    {
        controller->Elements[controller->Count++] = element;
    }
    else
    {
        if(!IntDArray_Grow(controller)) return 0;
        controller->Elements[controller->Count++] = element;
    }
    return 1;
}

int IntDArray_RemoveLast(IntDArrayController *restrict controller)
{
    if(controller->Capacity == 0U) return -1;
    if(controller->Count == 0U) return 0;

    controller->Count--;
    return 1;
}

void IntDArray_Print(IntDArrayController *restrict controller)
{
    printf("Elements: { ");
    for(size_t i = 0U; i < controller->Count; i++)
    {
        printf("%d ", controller->Elements[i]);
    }
    printf(
        "}\n"
        "Count: %zu\n"
        "Capacity: %zu\n",
        controller->Count, controller->Capacity
    );
}

int IntDArray_Get(IntDArrayController *restrict controller, size_t index)
{
    if(index < controller->Count)
        return controller->Elements[index];
    else return INT_MIN;
}

int IntDArray_Set(IntDArrayController *restrict controller, size_t index, int value)
{
    if(!(index < controller->Count)) return 0;

    controller->Elements[index] = value;
    return 1;
}