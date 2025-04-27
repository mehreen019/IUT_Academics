#include "TransactionManager.h"

#include <string.h>

TransactionManager TXM_New(void)
{
    TransactionManager txm;
    txm.TXLController = TXL_New();
    strncpy(txm.TXFile, TXL_FILE_PATH, TXL_FILE_PATH_MAX_LEN);

    FILE *fp = fopen(txm.TXFile, "r");
    if (fp)
        TXL_ReadFromFile(fp, &txm.TXLController);
    fclose(fp);

    return txm;
}

void TXM_Close(TransactionManager *txm)
{
    FILE *fp = fopen(txm->TXFile, "w");
    if (fp)
    {
        TXL_WriteToFile(fp, &txm->TXLController);
        fclose(fp);
    }
    else
    {
        printf("[ERROR!] Cannot open file to write!\n");
        exit(EXIT_FAILURE);
    }
}

void TXM_AddIncome(TransactionManager *txm, const char *tag, const char *description, int amount, int month)
{
    Transaction itx = Transaction_NewIncome(tag, description, amount, month);
    TXL_InsertElement(&txm->TXLController, itx);
}
void TXM_AddExpense(TransactionManager *txm, const char *tag, const char *description, int amount, int month)
{
    Transaction etx = Transaction_NewExpense(tag, description, amount, month);
    TXL_InsertElement(&txm->TXLController, etx);
}

void TX_FormattedHeaderPrint(void)
{
    puts("Month  Type       Amount         Tag                   Desc");
    puts("----- ------- --------------- ---------- --------------------------------");
}

void TX_FormattedPrint(const Transaction *restrict tx)
{
    if(strlen(tx->Description) <= 33)
    {
        printf("%5.2d %7s %15d %10s %s",
            tx->Month, tx->Type == INCOME ? "Income" : "Expense", tx->Amount, tx->Tag, tx->Description);
    }
    else
    {
        printf("%5.2d %7s %15d %10s %.29s...\n",
            tx->Month, tx->Type == INCOME ? "Income" : "Expense", tx->Amount, tx->Tag, tx->Description);
    }
}
void TXM_ListAll(TransactionManager *txm)
{
    puts("[[Listing all transactions]]");
    TX_FormattedHeaderPrint();
    TXL_Element *iterator = txm->TXLController.Head;
    while (iterator)
    {
        TX_FormattedPrint(&iterator->tx);
        iterator = iterator->Next;
    }
}
void TXM_FilterByMonth(TransactionManager *txm, int month)
{
    printf("[[Filtered by month <%.2d>]]\n", month);
    TX_FormattedHeaderPrint();
    TXL_Element *iterator = txm->TXLController.Head;
    while (iterator)
    {
        if (iterator->tx.Month == month)
            TX_FormattedPrint(&iterator->tx);
        iterator = iterator->Next;
    }
}

void TXM_FilterByCategory(TransactionManager *txm, const char *tag)
{
    printf("[[Filtered by category <%s>]]\n", tag);
    TX_FormattedHeaderPrint();
    TXL_Element *iterator = txm->TXLController.Head;
    while (iterator)
    {
        if (!strcmp(iterator->tx.Tag, tag))
            TX_FormattedPrint(&iterator->tx);
        iterator = iterator->Next;
    }
}

void TXM_FilterExpense(TransactionManager *txm)
{
    puts("[[Filtered by expense]]");
    TX_FormattedHeaderPrint();
    TXL_Element *iterator = txm->TXLController.Head;
    while (iterator)
    {
        if (iterator->tx.Type == EXPENSE)
            TX_FormattedPrint(&iterator->tx);
        iterator = iterator->Next;
    }
}

void TXM_FilterIncome(TransactionManager *txm)
{
    puts("[[Filtered by income]]");
    TX_FormattedHeaderPrint();
    TXL_Element *iterator = txm->TXLController.Head;
    while (iterator)
    {
        if (iterator->tx.Type == INCOME)
            TX_FormattedPrint(&iterator->tx);
        iterator = iterator->Next;
    }
}

void TXM_SummaryByMonth(TransactionManager *txm, int month)
{
    printf("[[Summary by month <%.2d>]]\n", month);
    int totalIncome = 0;
    int totalExpense = 0;
    TXL_Element *iterator = txm->TXLController.Head;
    while (iterator)
    {
        if (iterator->tx.Month == month)
        {
            if (iterator->tx.Type == INCOME)
                totalIncome += iterator->tx.Amount;
            else
                totalExpense += iterator->tx.Amount;
        }
        iterator = iterator->Next;
    }
    printf("Total Income : %d\n", totalIncome);
    printf("Total Expense: %d\n", totalExpense);
    puts("------------------------------");
    if (totalIncome == totalExpense)
        printf("Balanced Expenditure\n");
    else if (totalIncome > totalExpense)
        printf("Cash in hand : %d\n", totalIncome - totalExpense);
    else
        printf("Underflow    : %d\n", totalExpense - totalIncome);
}

void TXM_SummaryOverall(TransactionManager *txm)
{
    puts("[[Overall Summary]]");
    int totalIncome = 0;
    int totalExpense = 0;
    TXL_Element *iterator = txm->TXLController.Head;
    while (iterator)
    {
        if (iterator->tx.Type == INCOME)
            totalIncome += iterator->tx.Amount;
        else
            totalExpense += iterator->tx.Amount;
        iterator = iterator->Next;
    }
    printf("Total Income : %d\n", totalIncome);
    printf("Total Expense: %d\n", totalExpense);
    puts("------------------------------");
    if (totalIncome == totalExpense)
        printf("Balanced Expenditure\n");
    else if (totalIncome > totalExpense)
        printf("Cash in hand : %d\n", totalIncome - totalExpense);
    else
        printf("Underflow    : %d\n", totalExpense - totalIncome);
}