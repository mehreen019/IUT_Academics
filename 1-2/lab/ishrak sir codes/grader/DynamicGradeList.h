#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "Grade.h"

typedef struct GradeDynamicArrayControlBlock
{
    Grade *Elements;
    bool _IsAllocated;
    size_t Capacity;
    size_t Count;
} DynamicGradeList;

DynamicGradeList DynamicGradeList_Make(void);
void DynamicGradeList_Destroy(DynamicGradeList *const dArray);
bool DynamicGradeList_AddElement(DynamicGradeList *const dArray, Grade element);
long long DynamicGradeList_Find(const DynamicGradeList *const dArray, Course value);
bool DynamicGradeList_RemoveElement(DynamicGradeList *const dArray, size_t position);

void DynamicGradeList_Serialize(const DynamicGradeList *const dArray, const char *const filePath);
void DynamicGradeList_Deserialize(DynamicGradeList *const dArray, const char *const filePath);
void DynamicGradeList_Print(const DynamicGradeList *const dArray);