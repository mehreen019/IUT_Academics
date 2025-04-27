#include <stdio.h>

#define CARDCOUNT 52

typedef enum suit
{
    CLUBS, HEARTS, SPADES, DIAMONDS, INVSUIT
} Suit;

typedef enum face
{
    ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, INVFACE
} Face;

typedef struct card
{
    Suit SuitVal;
    Face FaceVal;
} Card;

Suit CharToSuit(char c);
Face CharToFace(char c);
void ScanCardFromTwoChar(Card *const card);
void PrintCardsToTwoChar(const Card *const card);
void SwapCards(Card *const cardA, Card *const cardB);
int CmpCards(const Card *const cardA, const Card *const cardB);
void SortCards(Card *const cardArray, size_t length);


int main(void)
{
    size_t len;
    Card cardArray[CARDCOUNT];

    scanf("%zu", &len);
    for(size_t i = 0; i < len; i++)
    {
        ScanCardFromTwoChar(&cardArray[i]);
    }

    SortCards(cardArray, len);
    for(size_t i = 0; i < len; i++)
    {
        PrintCardsToTwoChar(&cardArray[i]);
        printf(" ");
    }
    printf("\n");
    return 0;
}

Suit CharToSuit(char c)
{
    switch (c)
    {
        case 'C': return CLUBS;
        case 'H': return HEARTS;
        case 'S': return SPADES;
        case 'D': return DIAMONDS;
        default:  return INVSUIT;
    }
}

Face CharToFace(char c)
{
    switch (c)
    {
        case 'A': return ACE;
        case '2': return TWO;
        case '3': return THREE;
        case '4': return FOUR;
        case '5': return FIVE;
        case '6': return SIX;
        case '7': return SEVEN;
        case '8': return EIGHT;
        case '9': return NINE;
        case 'T': return TEN;
        case 'J': return JACK;
        case 'Q': return QUEEN;
        case 'K': return KING;
        default:  return INVFACE;
    }
}

void ScanCardFromTwoChar(Card *const card)
{
    char schar, fchar;
    scanf(" %c%c", &schar, &fchar);
    card->SuitVal = CharToSuit(schar);
    card->FaceVal = CharToFace(fchar);
}

void PrintCardsToTwoChar(const Card *const card)
{
    static const char SuitCharList[] = {'C', 'H', 'S', 'D', 'X'};
    static const char FaceCharList[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'X'};
    printf("%c%c", SuitCharList[card->SuitVal], FaceCharList[card->FaceVal]);
}

void SwapCards(Card *const cardA, Card *const cardB)
{
    Card temp = *cardA;
    *cardA = *cardB;
    *cardB = temp;
}

int CmpCards(const Card *const cardA, const Card *const cardB)
{
    if(cardA->SuitVal - cardB->SuitVal)
    {
        return cardA->SuitVal - cardB->SuitVal;
    }
    else return cardA->FaceVal - cardB->FaceVal;
}

void SortCards(Card *const cardArray, size_t length)
{
    for(size_t i = 0; i < length - 1; i++)
    {
        for(size_t j = i + 1; j < length; j++)
        {
            if( CmpCards(&cardArray[i], &cardArray[j]) > 0 )
            {
                SwapCards(&cardArray[i], &cardArray[j]);
            }
        }
    }
}