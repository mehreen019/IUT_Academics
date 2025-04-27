#pragma once

#include <stdio.h>

#define MAX_TAG_LENGTH 10
#define MAX_DESC_LENGTH 200

typedef enum _transactionType
{
    INCOME, EXPENSE
} TransactionType;

typedef struct _transaction
{
   TransactionType Type;
   char Tag[MAX_TAG_LENGTH + 1];
   char Description[MAX_DESC_LENGTH + 1];
   int Amount;
   int Month; 
} Transaction;

Transaction Transaction_NewIncome(const char* tag, const char* description, int amount, int month);
Transaction Transaction_NewExpense(const char* tag, const char* description, int amount, int month);
int Transaction_Comp(const Transaction* restrict tx1, const Transaction* restrict tx2);
void Transaction_Print(const Transaction* restrict tx);
void Transaction_FPrint(FILE* fp, const Transaction* restrict tx);
void Transaction_FRead(FILE* fp, Transaction* restrict tx);