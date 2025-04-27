#pragma once

#include "TransactionList.h"

#define TXL_FILE_PATH_MAX_LEN 300
#define TXL_FILE_PATH "./Data.txt"

typedef struct _transactionManager
{
    TXL_Controller TXLController;
    char TXFile[TXL_FILE_PATH_MAX_LEN + 1];
} TransactionManager;

TransactionManager TXM_New(void);
void TXM_Close(TransactionManager* txm);
void TXM_AddIncome(TransactionManager* txm, const char* tag, const char* description, int amount, int month);
void TXM_AddExpense(TransactionManager* txm, const char* tag, const char* description, int amount, int month);
void TXM_ListAll(TransactionManager* txm);
void TXM_FilterByMonth(TransactionManager* txm, int month);
void TXM_FilterByCategory(TransactionManager* txm, const char* tag);
void TXM_FilterExpense(TransactionManager* txm);
void TXM_FilterIncome(TransactionManager* txm);
void TXM_SummaryByMonth(TransactionManager* txm, int month);
void TXM_SummaryOverall(TransactionManager* txm);