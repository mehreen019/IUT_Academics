#include <stdio.h>

#define FILE_PATH "./Sample.txt"

int ReadLineAndPrint(FILE* fp);

int main(void)
{
    FILE* fp = fopen(FILE_PATH, "r+");

    if(fp == NULL)
    {
        printf("[Error!] failed to open the file <%s>\n", FILE_PATH);
    }
    else
    {
        ReadLineAndPrint(fp);
        ReadLineAndPrint(fp);
        fseek(fp, -9L, SEEK_END);
        fprintf(fp, "Bye Bye Bye!");
        fseek(fp, 0L, SEEK_SET);
        ReadLineAndPrint(fp);
        ReadLineAndPrint(fp);
        ReadLineAndPrint(fp);
        fclose(fp);
    }

    return 0;
}

int ReadLineAndPrint(FILE* fp)
{
    char ch;
    while (1)
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            putchar('\n');
            return 1;
        }
        else if(ch == EOF)
        {
            printf("\n-- Reached End of File ---\n");
            return 0;
        }
        else
        {
            putchar(ch);
        }
    }
}