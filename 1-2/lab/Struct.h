#pragma once
#define max_tag 10
#define max_desc 200

typedef struct _type
{
    int     Amount;
    char    Tag[max_tag + 1];
    char    Desc[max_desc + 1];
} Type;


typedef struct _month
{
    int     monthnum;
    Type Income;
    Type Expense;
} Month;

