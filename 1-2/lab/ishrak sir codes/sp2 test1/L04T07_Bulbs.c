#include <stdio.h>

// Considering LSB as the 0-th bit
void SetBit(unsigned char* DATA, int bitNumber);

int main(void)
{
    unsigned char data = 0U;
    char c;
    for(int i = 7; i >= 0; i--)
    {
        scanf("%c", &c);
        if(c == '1') SetBit(&data, i);
    }
    printf("%c\n", data);
    return 0;
}

void SetBit(unsigned char* DATA, int bitNumber)
{
    *DATA |= (1 << bitNumber);
}