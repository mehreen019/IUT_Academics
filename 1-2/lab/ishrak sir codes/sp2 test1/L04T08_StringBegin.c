#include <stdio.h>
#include <string.h>

#define MAXWORDLEN 30

int main(void)
{
    int len;
    int count = 0;
    char s[4], wordBuffer[MAXWORDLEN + 1];

    scanf("%d%s", &len, s);
    for(int i = 0; i < len; i++)
    {
        scanf("%s", wordBuffer);
        wordBuffer[3] = 0;
        if(!strcmp(s, wordBuffer)) count++;
    }
    printf("%d\n", count);
    return 0;
}