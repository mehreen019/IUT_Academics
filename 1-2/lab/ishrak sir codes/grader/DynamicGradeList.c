#include "DynamicGradeList.h"

#include <stdlib.h>
#include <stdio.h>

DynamicGradeList DynamicGradeList_Make(void)
{
    DynamicGradeList dArray = {NULL, false, 0, 0};
    dArray.Elements = (Grade *)malloc((sizeof(Grade)) * 4);
    dArray._IsAllocated = true;
    dArray.Capacity = 4;
    return dArray;
}
void DynamicGradeList_Destroy(DynamicGradeList *const dArray)
{
    if (!dArray->_IsAllocated)
        return;
    free(dArray->Elements);
    dArray->Elements = NULL;
    dArray->_IsAllocated = false;
}
bool DynamicGradeList_AddElement(DynamicGradeList *const dArray, Grade element)
{
    if (!dArray->_IsAllocated)
        return false;
    if (dArray->Count == dArray->Capacity)
    {
        size_t target = dArray->Capacity * 2;
        dArray->Elements = (Grade *)realloc(dArray->Elements, target * sizeof(Grade));
        if (!dArray->Elements)
            return false;
        dArray->Capacity = target;
    }
    // dArray->Elements[dArray->Count] = element;
    size_t position;
    for(position = 0; position < dArray->Count; position++)
    {
        if(CompareCourse(&element.CourseInfo, &dArray->Elements[position].CourseInfo) < 0)
            break;
    }
    for(size_t i = dArray->Count; i > position; i--)
    {
        dArray->Elements[i] = dArray->Elements[i - 1];
    }
    dArray->Elements[position] = element;
    dArray->Count++;
    return true;
}
bool DynamicGradeList_RemoveElement(DynamicGradeList *const dArray, size_t position)
{
    if (!dArray->_IsAllocated)
        return false;
    if (position >= dArray->Count)
        return false;
    for (size_t i = position; i < dArray->Count - 1; i++)
    {
        dArray->Elements[i] = dArray->Elements[i + 1];
    }
    dArray->Count--;
    return true;
}
long long DynamicGradeList_Find(const DynamicGradeList *const dArray, Course value)
{
    for (size_t i = 0; i < dArray->Count; i++)
    {
        if(!CompareCourse(&dArray->Elements[i].CourseInfo, &value))
        {
            return i;
        }
    }
    return -1;
}

void DynamicGradeList_Serialize(const DynamicGradeList *const dArray, const char *const filePath)
{
    FILE *fp = fopen(filePath, "wb");
    if(fp)
    {
        fwrite(&dArray->Count, sizeof(size_t), 1, fp);
        fwrite(dArray->Elements, sizeof(Grade), dArray->Count, fp);
        fclose(fp);
    }
    else
    {
        printf("[ERROR!] Cannot write to file (%s)\n", filePath);
        exit(EXIT_FAILURE);
    }
}

void DynamicGradeList_Deserialize(DynamicGradeList *const dArray, const char *const filePath)
{
    FILE *fp = fopen(filePath, "rb");
    if(fp)
    {
        fread(&dArray->Count, sizeof(size_t), 1, fp);
        dArray->Elements = (Grade *)realloc(dArray->Elements, dArray->Count * sizeof(Grade));
        dArray->Capacity = dArray->Count;
        fread(dArray->Elements, sizeof(Grade), dArray->Count, fp);
        fclose(fp);
    }
    else
    {
        printf("[WARNING!] No save file found (%s)\n", filePath);
    }
}

void DynamicGradeList_Print(const DynamicGradeList *const dArray)
{
    for(size_t i = 0; i < dArray->Count; i++)
    {
        PrintGrade(&dArray->Elements[i]);
    }
}