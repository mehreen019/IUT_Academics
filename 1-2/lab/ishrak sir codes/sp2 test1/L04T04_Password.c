#include <stdio.h>

char DecimalToHexChar(unsigned int dec);

int main(void)
{
    const unsigned char mask = 15U;
    unsigned char c;
    scanf("%c", &c);

    unsigned int lDigit = c & mask;
    unsigned int rDigit = (c >> 4);

    printf("%c%c\n", DecimalToHexChar(lDigit), DecimalToHexChar(rDigit));

    return 0;
}

char DecimalToHexChar(unsigned int dec)
{
    static const char HexArr[] =   {'0', '1', '2', '3',
                                    '4', '5', '6', '7',
                                    '8', '9', 'A', 'B',
                                    'C', 'D', 'E', 'F'};

    return HexArr[dec];
}