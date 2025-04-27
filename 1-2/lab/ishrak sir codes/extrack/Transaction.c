#include "Transaction.h"

#include <string.h>
#include <stdio.h>

Transaction Transaction_Init(const char* tag, const char* description, int amount, int month)
{
    Transaction tx = {0};
    strncpy(tx.Tag, tag, MAX_TAG_LENGTH);
    strncpy(tx.Description, description, MAX_DESC_LENGTH);
    tx.Amount = amount;
    tx.Month = (month > 0 && month <= 12) ? month : -1;
    return tx;
}

Transaction Transaction_NewIncome(const char* tag, const char* description, int amount, int month)
{
    Transaction tx = Transaction_Init(tag, description, amount, month);
    tx.Type = INCOME;
    return tx;
}

Transaction Transaction_NewExpense(const char* tag, const char* description, int amount, int month)
{
    Transaction tx = Transaction_Init(tag, description, amount, month);
    tx.Type = EXPENSE;
    return tx;
}

int Transaction_Comp(const Transaction* restrict tx1, const Transaction* restrict tx2)
{
    return tx1->Month == tx2->Month ? tx1->Amount - tx2->Amount : tx1->Month - tx2->Month;
}

void Transaction_Print(const Transaction* restrict tx)
{
    printf(tx->Type == INCOME ? "Income:\n" : "Expense:\n");
    printf("\tAmount: %d\n", tx->Amount);
    printf("\tMonth: %.2d\n", tx->Month);
    printf("\tTag: %s\n", tx->Tag);
    printf("\tDescription: %s\n", tx->Description);
}

void Transaction_FPrint(FILE* fp, const Transaction* restrict tx)
{
    fprintf(fp, "Type: %d\n", tx->Type);
    fprintf(fp, "Amount: %d\n", tx->Amount);
    fprintf(fp, "Month: %d\n", tx->Month);
    fprintf(fp, "Tag: %s\n", tx->Tag);
    fprintf(fp, "Description: %s\n\n", tx->Description);
}

void Transaction_FRead(FILE* fp, Transaction* restrict tx)
{
    fscanf(fp, " Type: %d", &tx->Type);
    fscanf(fp, " Amount: %d", &tx->Amount);
    fscanf(fp, " Month: %d", &tx->Month);
    fscanf(fp, " Tag: %s", tx->Tag);
    fscanf(fp, " Description: ");
    fgets(tx->Description, MAX_DESC_LENGTH, fp);
}