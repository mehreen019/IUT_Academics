#include "Struct.h"
#include <stddef.h>
#include <stdio.h>
#define DEFAULT_INIT_CAPACITY 2

typedef struct _intDArrayController
{
    Month* Elements;
    size_t Count;
    size_t Capacity;
} IntDArrayController;

IntDArrayController IntDArray_New(void);
void IntDArray_Print(IntDArrayController *restrict controller);
int IntDArray_Add(IntDArrayController *restrict controller, Month element);
void IntDArray_Read(FILE* fp, Month *stdx);
Month IntDArray_FindByMonth(IntDArrayController *restrict controller, int index);
int IntDArray_GetIncomeAmount(IntDArrayController *restrict controller, int index);
int IntDArray_GetExpenseAmount(IntDArrayController *restrict controller, int index);