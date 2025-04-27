#include "TransactionList.h"

TXL_Controller TXL_New(void)
{
    return (TXL_Controller){.Count = 0U, .Head = NULL, .Tail = NULL};
}

void TXL_Free(TXL_Controller* restrict controller)
{
    TXL_Element* iterator = controller->Head;
    while (iterator)
    {
        free(iterator->Prev);
        iterator = iterator->Next;
    }
    free(controller->Tail);
    controller->Head = controller->Tail = NULL;
    controller->Count = 0U;
}

TXL_Element* TXL_MakeElement(Transaction tx)
{
    TXL_Element* element = ( TXL_Element* )malloc(sizeof(TXL_Element));
    
    if(!element) return NULL;

    element->tx = tx;
    element->Prev = NULL;
    element->Next = NULL;

    return element;
}

TXL_Element* TXL_InsertElement(TXL_Controller* restrict controller, Transaction tx)
{
    // Make Element
    TXL_Element* element = TXL_MakeElement(tx);
    if(!element) return NULL;

    // Case 1: List is Empty
    if(controller->Count == 0U)
    {
        controller->Head = controller->Tail = element;
    }
    else // Case 2...4: List is not Empty
    {
        TXL_Element* iterator = controller->Head;
        while( Transaction_Comp(&element->tx, &iterator->tx) > 0)
        {
            iterator = iterator->Next;
            if(!iterator) break;
        }
        // Case 2: Insert at Head
        if(iterator == controller->Head)
        {
            controller->Head = element;
            element->Next = iterator;
            iterator->Prev = element;
        }
        // Case 3: Insert at Tail
        else if(iterator == NULL)
        {
            controller->Tail->Next = element;
            element->Prev = controller->Tail;
            controller->Tail = element;             
        }
        // Case 4: Somewhere in the middle
        else
        {
            element->Next = iterator;
            element->Prev = iterator->Prev;
            iterator->Prev->Next = element;
            iterator->Prev = element;
        }
    }
    controller->Count++;
    return element;
}

TXL_Element* TXL_FindElement(TXL_Controller* restrict controller, Transaction tx)
{
    TXL_Element* iterator = controller->Head;
    while (iterator)
    {
        if(!Transaction_Comp(&iterator->tx, &tx)) break;
        iterator = iterator->Next;
    }
    return iterator;
}

int TXL_RemoveElement(TXL_Controller* restrict controller, Transaction tx)
{
    TXL_Element* iterator = TXL_FindElement(controller, tx);
    // Case 0: Element does not exist
    if(!iterator) return 0;

    // Case 1: Element is both Head and Tail (only element)
    if(controller->Count == 1)
    {
        controller->Head = NULL;
        controller->Tail = NULL;
        free(iterator);
    }
    // Case 2: Element is only Head
    else if(iterator == controller->Head)
    {
        controller->Head = iterator->Next;
        iterator->Next->Prev = NULL;
        free(iterator);
    }
    // Case 3: Element is only Tail
    else if(iterator == controller->Tail)
    {
        controller->Tail = iterator->Prev;
        iterator->Prev->Next = NULL;
        free(iterator);
    }
    // Case 4: Element is somewhere in the middle
    else
    {
        iterator->Prev->Next = iterator->Next;
        iterator->Next->Prev = iterator->Prev;
        free(iterator);
    }

    controller->Count--;
    return 1;
}

void TXL_WriteToFile(FILE* fp, const TXL_Controller* restrict controller)
{
    fprintf(fp, "Count: %zu\n", controller->Count);
    TXL_Element* iterator = controller->Head;
    while (iterator)
    {
        Transaction_FPrint(fp, &iterator->tx);
        iterator = iterator->Next;
    }
}

void TXL_ReadFromFile(FILE* fp, TXL_Controller* restrict controller)
{
    size_t count = 0U;
    fscanf(fp, "Count: %zu", &count);
    
    for(size_t i = 0U; i < count; i++)
    {
        Transaction tx;
        Transaction_FRead(fp, &tx);
        TXL_InsertElement(controller, tx);
    }
}

void TXL_Print(TXL_Controller* restrict controller)
{
    TXL_Element* iterator = controller->Head;
    while (iterator)
    {
        Transaction_Print(&iterator->tx);
        iterator = iterator->Next;
    }
    printf("\nCount: %zu\n", controller->Count);
}

void TXL_ReversePrint(TXL_Controller* restrict controller)
{
    TXL_Element* iterator = controller->Tail;
    printf("Reversed Elements: ");
    while (iterator)
    {
        Transaction_Print(&iterator->tx);
        iterator = iterator->Prev;
    }
    printf("\nCount: %zu\n", controller->Count);
}