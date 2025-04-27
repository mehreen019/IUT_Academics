#include "exp.h"
#include "Struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int IntDArray_Grow(IntDArrayController *restrict controller)
{
    Month* requested = ( Month * )realloc
    (
        controller->Elements,
        controller->Capacity * 2 * sizeof(Month)
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

IntDArrayController IntDArray_New(void)
{
    IntDArrayController controller = (IntDArrayController)
    {
        .Elements = NULL,
        .Count = 0U,
        .Capacity = DEFAULT_INIT_CAPACITY
    };

    controller.Elements = ( Month * )malloc(controller.Capacity * sizeof(Month));

    if(controller.Elements == NULL)
        exit(1);
    
    return controller; 
}

void IntDArray_Print(IntDArrayController *restrict controller)
{
    printf("Elements: { ");
    for(size_t i = 0U; i < controller->Count; i++)
    {
        printf("Month num : %d\t", controller->Elements[i].monthnum);
        printf("Type : INCOME\t");
        printf("Amount : %d\t", controller->Elements[i].Income.Amount);
        printf("Tag : %s\t", controller->Elements[i].Income.Tag);
        printf("Description : %s\t", controller->Elements[i].Income.Desc);
        printf("\n\t");
        printf("\t\t\tType : EXPENSE\t");
        printf("Amount : %d\t", controller->Elements[i].Expense.Amount);
        printf("Tag : %s\t", controller->Elements[i].Expense.Tag);
        printf("Description : %s\t", controller->Elements[i].Expense.Desc);
    }
    printf(
        "}\n"
        "Count: %zu\n"
        "Capacity: %zu\n",
        controller->Count, controller->Capacity
    );
}

int IntDArray_Add(IntDArrayController *restrict controller, Month element)
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

void IntDArray_Read(FILE* fp, Month *stdx){
    fscanf(fp,"%d", &stdx->monthnum);
    fscanf(fp,"%d", &stdx->Income.Amount);
    fscanf(fp,"%s", stdx->Income.Tag);
    fscanf(fp,"%s", stdx->Income.Desc);
    fscanf(fp,"%d", &stdx->Expense.Amount);
    fscanf(fp,"%s", stdx->Expense.Tag);
    fscanf(fp,"%s", stdx->Expense.Desc);
}

Month IntDArray_FindByMonth(IntDArrayController *restrict controller, int index)
{
    if(index < controller->Count)
        return controller->Elements[index];
    else printf("index not in range\n");
}

int IntDArray_GetIncomeAmount(IntDArrayController *restrict controller, int index)
{
    if(index < controller->Count)
        return controller->Elements[index].Income.Amount;
    else printf("index not in range\n");
}

int IntDArray_GetExpenseAmount(IntDArrayController *restrict controller, int index)
{
    if(index < controller->Count)
        return controller->Elements[index].Expense.Amount;
    else printf("index not in range\n");
}
