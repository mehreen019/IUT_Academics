#include <stdlib.h>
#include <stdio.h>
#include "task.h"

SLL_Controller SLL_NewController(void)
{
    return (SLL_Controller){.HEAD = NULL, .TAIL = NULL, .Count = 0U};
}
SLL_Element* SLL_MakeElement(int value)
{
    SLL_Element* element = ( SLL_Element* ) malloc(sizeof(SLL_Element));
    if(!element) return NULL;

    element->Value = value;
    element->NEXT = element->PREV = NULL;

    return element;
}

void SLL_InsertBeg(SLL_Controller* controller, int value){
     SLL_Element* element = SLL_MakeElement(value);
    //if(!element) return
    if(controller->Count == 0U)
    {
        controller->HEAD = element;
        controller->TAIL = element;
    }
    element->NEXT = controller->HEAD;
    controller->HEAD->PREV = element;
    controller->HEAD = element;
    controller->Count++;
}
void SLL_InsertEnd(SLL_Controller* controller, int value){
    SLL_Element* element = SLL_MakeElement(value);
    //if(!element)
    if(controller->Count == 0U)
    {
        controller->HEAD = element;
        controller->TAIL = element;
    }
    element->PREV = controller->TAIL;
    controller->TAIL->NEXT = element;
    controller->TAIL = element;
    controller->Count++;
}
void SLL_Print(const SLL_Controller* controller)
{
    SLL_Element* iterator = controller->HEAD;
    printf("Elements: ");
    while (iterator)
    {
        printf("%d ", iterator->Value);
        iterator = iterator->NEXT;
    }
    putchar('\n');
    printf("Count: %zu\n", controller->Count);
}
SLL_Element* SLL_Insert(SLL_Controller* controller, int value)
{
    SLL_Element* element = SLL_MakeElement(value);
    if(!element) return NULL;

    // Case 1: List is empty
    if(controller->Count == 0U)
    {
        controller->HEAD = element;
        controller->TAIL = element;
    }
    else // Case 2 ... 4: List is not empty 
    {
        SLL_Element* iterator = controller->HEAD;
        while(iterator)
        {
            if(iterator->Value > value)
                break;
            iterator = iterator->NEXT;
        }
        
        // Case 2: Insertion at Head
        if(iterator == controller->HEAD)
        {
            element->NEXT = controller->HEAD;
            controller->HEAD->PREV = element;
            controller->HEAD = element;
        }
        // Case 3: Insertion at Tail
        else if(iterator == NULL)
        {
            element->PREV = controller->TAIL;
            controller->TAIL->NEXT = element;
            controller->TAIL = element;
        }
        // Case 4: Insertion in the middle
        else
        {
            element->NEXT = iterator;
            element->PREV = iterator->PREV;
            iterator->PREV->NEXT = element;
            iterator->PREV = element;
        }
    }

    controller->Count++;
    return element;
}

SLL_Element* SLL_Find(const SLL_Controller* controller, int value)
{
    SLL_Element* iterator = controller->HEAD;
    while (iterator)
    {
        if(iterator->Value == value)
            break;
        iterator = iterator->NEXT;
    }
    return iterator;
}
void SLL_ReversePrint(const SLL_Controller* controller)
{
    SLL_Element* iterator = controller->TAIL;
    printf("Elements Reversed: ");
    while (iterator)
    {
        printf("%d ", iterator->Value);
        iterator = iterator->PREV;
    }
    putchar('\n');
    printf("Count: %zu\n", controller->Count);
}
