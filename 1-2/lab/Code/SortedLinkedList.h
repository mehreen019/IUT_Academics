#pragma once

#include <stddef.h>

typedef struct _sll_Element
{
    int Value;
    struct _sll_Element* NEXT;
    struct _sll_Element* PREV;
} SLL_Element;

typedef struct _sll_Controller
{
    SLL_Element* HEAD;
    SLL_Element* TAIL;
    size_t Count;
} SLL_Controller;

SLL_Controller SLL_NewController(void);
void SLL_Free(SLL_Controller* controller);

SLL_Element* SLL_MakeElement(int value);
SLL_Element* SLL_Insert(SLL_Controller* controller, int value);
SLL_Element* SLL_Find(const SLL_Controller* controller, int value);
int SLL_Remove(SLL_Controller* controller, int value);

void SLL_Print(const SLL_Controller* controller);
void SLL_ReversePrint(const SLL_Controller* controller);