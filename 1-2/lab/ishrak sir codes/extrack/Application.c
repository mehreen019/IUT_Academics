#include "TransactionManager.h"

#include <stdio.h>

#define CMD_INCOME "add_income"
#define CMD_EXPENSE "add_expense"
#define CMD_LISTALL "list"
#define CMD_FILT_MONTH "by_month"
#define CMD_FILT_TAG "by_tag"
#define CMD_FILT_EXPENSE "expenses"
#define CMD_FILT_INCOME "incomes"
#define CMD_SUM_ALL "summary"
#define CMD_SUM_MONTH "summary_month"

void PrintHelp(void);
void PanicExit(void);
int main(int argc, char** argv)
{
    if(argc < 2)
    {
        PrintHelp();
        return 0;
    }

    TransactionManager txm = TXM_New();

    if(!strcmp(argv[1], CMD_INCOME))
    {
        if(argc < 6) PanicExit();
        TXM_AddIncome(&txm, argv[4], argv[5], atoi(argv[2]), atoi(argv[3]));
        printf("Income added successfully!\n");
    }
    else if(!strcmp(argv[1], CMD_EXPENSE))
    {
        if(argc < 6) PanicExit();
        TXM_AddExpense(&txm, argv[4], argv[5], atoi(argv[2]), atoi(argv[3]));
        printf("Expense added successfully!\n");
    }
    else if(!strcmp(argv[1], CMD_LISTALL))
    {
        TXM_ListAll(&txm);
    }
    else if(!strcmp(argv[1], CMD_FILT_MONTH))
    {
        if(argc < 3) PanicExit();
        TXM_FilterByMonth(&txm, atoi(argv[2]));
    }
    else if(!strcmp(argv[1], CMD_FILT_TAG))
    {
        if(argc < 3) PanicExit();
        TXM_FilterByCategory(&txm, argv[2]);
    }
    else if(!strcmp(argv[1], CMD_FILT_EXPENSE))
    {
        TXM_FilterExpense(&txm);
    }
    else if(!strcmp(argv[1], CMD_FILT_INCOME))
    {
        TXM_FilterIncome(&txm);
    }
    else if(!strcmp(argv[1], CMD_SUM_ALL))
    {
        TXM_SummaryOverall(&txm);
    }
    else if(!strcmp(argv[1], CMD_SUM_MONTH))
    {
        if(argc < 3) PanicExit();
        TXM_SummaryByMonth(&txm, atoi(argv[2]));
    }
    else
    {
        PrintHelp();
    }
    
    TXM_Close(&txm);
    return 0;
}

void PrintHelp(void)
{
    puts("EXTRACK : Track your expenses and income");
    puts("Use one of the following commands:");
    
    puts("\n[[ADDITION]]");
    // Add income
    printf("Add Income: extrack %s <AMOUNT> <MONTH[1, 12]> <TAG[%d]> <DESCRIPTION[%d]>\n",
        CMD_INCOME, MAX_TAG_LENGTH, MAX_DESC_LENGTH);
    // Add expense
    printf("Add Expense: extrack %s <AMOUNT> <MONTH[1, 12]> <TAG[%d]> <DESCRIPTION[%d]>\n",
        CMD_EXPENSE, MAX_TAG_LENGTH, MAX_DESC_LENGTH);

    puts("\n[[LISTING]]");
    // List all transactions
    printf("List all: extrack %s\n", CMD_LISTALL);
    // Filter by month
    printf("List by month: extrack %s <MONTH[1, 12]>\n", CMD_FILT_MONTH);
    // Filter by tag
    printf("List by category: extrack %s <TAG>\n", CMD_FILT_TAG);
    // Filter only expenses
    printf("List only expenses: extrack %s\n", CMD_FILT_EXPENSE);
    // Filter only income
    printf("List only incomes: extrack %s\n", CMD_FILT_INCOME);

    puts("\n[[SUMMARIES]]");
    // Summary overall
    printf("Overall summary: extrack %s\n", CMD_SUM_ALL);
    // Summary by month
    printf("Summary by month: extrack %s <MONTH[1, 12]>\n", CMD_SUM_MONTH);
}

void PanicExit(void)
{
    puts("### Error in command input! ###");
    PrintHelp();
    exit(0);
}