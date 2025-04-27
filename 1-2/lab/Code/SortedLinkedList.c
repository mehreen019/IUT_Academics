#include "SortedLinkedList.h"

#include <stdlib.h>
#include <stdio.h>

SLL_Controller SLL_NewController(void)
{
    return (SLL_Controller){.HEAD = NULL, .TAIL = NULL, .Count = 0U};
}

void SLL_Free(SLL_Controller* controller)
{
    SLL_Element* iterator = controller->HEAD;
    while (iterator)
    {
        free(iterator->PREV);
        iterator = iterator->NEXT;
    }
    free(controller->TAIL);

    controller->HEAD = controller->TAIL = NULL;
    controller->Count = 0U;
}

SLL_Element* SLL_MakeElement(int value)
{
    SLL_Element* element = ( SLL_Element* ) malloc(sizeof(SLL_Element));
    if(!element) return NULL;

    element->Value = value;
    element->NEXT = element->PREV = NULL;

    return element;
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

int SLL_Remove(SLL_Controller* controller, int value)
{
    SLL_Element* iterator = SLL_Find(controller, value);

    // Case 1: Element does not exist
    if(!iterator) return 0;

    // Case 2: Removing the only element
    if(controller->Count == 1U)
    {
        controller->HEAD = controller->TAIL = NULL;
    }
    // Case 3: Removing HEAD
    else if(iterator == controller->HEAD)
    {
        controller->HEAD = iterator->NEXT;
        controller->HEAD->PREV = NULL;
    }
    // Case 4: Removing TAIL
    else if(iterator == controller->TAIL)
    {
        controller->TAIL = iterator->PREV;
        controller->TAIL->NEXT = NULL;
    }
    // Case 5: Removing from the middle
    else
    {
        iterator->PREV->NEXT = iterator->NEXT;
        iterator->NEXT->PREV = iterator->PREV;
    }

    free(iterator);
    controller->Count--;
    return 1;
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