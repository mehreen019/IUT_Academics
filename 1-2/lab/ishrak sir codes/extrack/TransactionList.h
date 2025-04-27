#pragma once

#include "Transaction.h"

#include <stdlib.h>

typedef struct _TXL_Element
{
    Transaction tx;
    struct _TXL_Element* Next;
    struct _TXL_Element* Prev;
} TXL_Element;

typedef struct _ssl_Controller
{
    TXL_Element* Head;
    TXL_Element* Tail;
    size_t Count;
} TXL_Controller;

TXL_Controller TXL_New(void);
void TXL_Free(TXL_Controller* restrict controller);
TXL_Element* TXL_InsertElement(TXL_Controller* restrict controller, Transaction tx);
TXL_Element* TXL_FindElement(TXL_Controller* restrict controller, Transaction tx);
int TXL_RemoveElement(TXL_Controller* restrict controller, Transaction tx);
void TXL_WriteToFile(FILE* fp, const TXL_Controller* restrict controller);
void TXL_ReadFromFile(FILE* fp, TXL_Controller* restrict controller);
void TXL_Print(TXL_Controller* restrict controller);
void TXL_ReversePrint(TXL_Controller* restrict controller);