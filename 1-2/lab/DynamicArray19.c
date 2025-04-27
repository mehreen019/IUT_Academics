#include "DynamicArray19.h"
#include "StudentInfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stddef.h>

/// @brief An internal function to grow the allocated memory when required, should not be called explicitly
/// @param controller Pointer to the controller to grow
/// @return 1 if successful, 0 if failed
int IntDArray_Grow(IntDArrayController *restrict controller);

//TASK 1

IntDArrayController IntDArray_New(void)
{
    IntDArrayController controller = (IntDArrayController)
    {
        .Elements = NULL,
        .Count = 0U,
        .Capacity = DEFAULT_INIT_CAPACITY
    };

    controller.Elements = ( StudentInfo * )malloc(controller.Capacity * sizeof(StudentInfo));

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
    StudentInfo* requested = ( StudentInfo * )realloc
    (
        controller->Elements,
        controller->Capacity * 2 * sizeof(StudentInfo)
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

int IntDArray_Add(IntDArrayController *restrict controller, StudentInfo element)
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
         printf("Name : %s\n", controller->Elements[i].Name);
        printf("ID : %d\n", controller->Elements[i].ID);
        printf("CGPA : %.2f\n", controller->Elements[i].CGPA);

        printf("--- Present Address ---\n");
        printf("HouseNumber : %d\n", controller->Elements[i].PresentAddress.HouseNumber);
        printf("RoadNumber : %d\n",controller->Elements[i].PresentAddress.RoadNumber);
        printf("City : %s\n", controller->Elements[i].PresentAddress.City);
        printf("Country : %s\n", controller->Elements[i].PresentAddress.Country);
        printf("ZipCode : %d\n", controller->Elements[i].PresentAddress.ZipCode);

        printf("--- Permanent Address ---\n");
        printf("HouseNumber : %d\n", controller->Elements[i].PermanentAddress.HouseNumber);
        printf("RoadNumber : %d\n", controller->Elements[i].PermanentAddress.RoadNumber);
        printf("City : %s\n", controller->Elements[i].PermanentAddress.City);
        printf("Country : %s\n", controller->Elements[i].PermanentAddress.Country);
        printf("ZipCode : %d\n\n", controller->Elements[i].PermanentAddress.ZipCode);
    }
    printf(
        "}\n"
        "Count: %zu\n"
        "Capacity: %zu\n",
        controller->Count, controller->Capacity
    );
}

StudentInfo IntDArray_Get(IntDArrayController *restrict controller, size_t index)
{
    if(index < controller->Count)
        return controller->Elements[index];
    else printf("index not in range\n");
}

int IntDArray_Set(IntDArrayController *restrict controller, size_t index, StudentInfo value)
{
    if(!(index < controller->Count)) printf("can't set due to out of range\n");

    controller->Elements[index] = value;
    return 1;
}

//TASK 2

int IntDArray_Remove(IntDArrayController *restrict controller, size_t i){
    if(!(i<controller->Count) || (controller->Capacity==0U) || (controller->Count==0U)) return -1;
    else{
        for(int j=i;j<(controller->Count)-1U;j++){
            controller->Elements[j]=controller->Elements[j+1];
        }
        controller->Count--;
        return 1;
    }
}

int IntDArray_Insert(IntDArrayController *restrict controller, size_t i, StudentInfo value){
    if((i>controller->Count+1) || (controller->Capacity==0U)) return -1;
    else if(controller->Count<controller->Capacity){
        for(size_t j=controller->Count;j>i;j--){
            controller->Elements[i]=controller->Elements[i-1];
        }
        controller->Elements[i]=value;
        controller->Count++;
        return 1;
    }
    else{
        if(!(IntDArray_Grow(controller))) return -1;
        for(size_t j=controller->Count;j>i;j--){
            controller->Elements[i]=controller->Elements[i-1];
        }
        controller->Elements[i]=value;
        controller->Count++;
        return 1;
    }
}

void IntDArray_Clear(IntDArrayController *restrict controller){
    for(size_t i=0U;i<controller->Count;i++){
        StudentInfo t={"",0,0,{0,0,"","",0},{0,0,"","",0}};
        controller->Elements[i]=t;
    }
}

int IntDArray_Find(IntDArrayController *restrict controller, StudentInfo* t){
    for(size_t i=0U;i<controller->Count;i++){
        if(controller->Elements[i].ID==t->ID) return i;
    }
    return -1;
}

void IntDArray_Sort(IntDArrayController *restrict controller, int num){
    if(num==1){
        for(size_t i=0U;i<controller->Count;i++){
            for(size_t j=i+1;j<controller->Count;j++){
                if(controller->Elements[i].CGPA>controller->Elements[j].CGPA){
                    StudentInfo t=controller->Elements[i];
                    controller->Elements[i]=controller->Elements[j];
                    controller->Elements[j]=t;
                }
                else if(controller->Elements[i].CGPA==controller->Elements[j].CGPA){
                    if(controller->Elements[i].ID>controller->Elements[j].ID){
                        StudentInfo t=controller->Elements[i];
                        controller->Elements[i]=controller->Elements[j];
                        controller->Elements[j]=t;
                    }
                }
            }
        }
    }
    else if(num==0){
        for(size_t i=0U;i<controller->Count;i++){
            for(size_t j=i+1;j<controller->Count;j++){
                if(controller->Elements[i].CGPA<controller->Elements[j].CGPA){
                    StudentInfo t=controller->Elements[i];
                    controller->Elements[i]=controller->Elements[j];
                    controller->Elements[j]=t;
                }
                else if(controller->Elements[i].CGPA==controller->Elements[j].CGPA){
                    if(controller->Elements[i].ID<controller->Elements[j].ID){
                        StudentInfo t=controller->Elements[i];
                        controller->Elements[i]=controller->Elements[j];
                        controller->Elements[j]=t;
                    }
                }
            }
        }
    }
    else printf("invalid input\n");
}



