#include <stdio.h>
#include <stdlib.h>

#define MAXNAMELEN 15

typedef struct coordinate
{
    char X;
    char Y;
} Coordinate;


typedef struct chessPiece
{
    char Name[MAXNAMELEN + 1];
    Coordinate Coord;
    int _MDistance;
} ChessPiece;

int CalculateManhattanDistance(const Coordinate* const c1, const Coordinate* const c2);
void ScanCoordinate(Coordinate *const coord);
void ScanChessPiece(ChessPiece *const piece);
void PrintChessPiece(const ChessPiece *const piece);
void SwapChessPieces(ChessPiece *const piece1, ChessPiece *const piece2);
void SortChessPieceArray(ChessPiece *const pieceArray, size_t length);
int GetLowerBound(ChessPiece *const pieceArray, size_t length, int targetDistance);

int main(void)
{
    size_t len;
    ChessPiece pieceArray[52];
    Coordinate searchCoord;
    Coordinate refCoord = {'h', '8'};
    scanf("%zu", &len);
    for(size_t i = 0; i < len; i++)
    {
        ScanChessPiece(&pieceArray[i]);
        //PrintChessPiece(&pieceArray[i]);
        pieceArray[i]._MDistance = CalculateManhattanDistance(&pieceArray[i].Coord, &refCoord);
    }
    ScanCoordinate(&searchCoord);
    int searchDistance = CalculateManhattanDistance(&searchCoord, &refCoord);

    SortChessPieceArray(pieceArray, len);

    int targetIndex = GetLowerBound(pieceArray, len, searchDistance);

    printf("[OUTPUT]\n");
    if(targetIndex == 0) PrintChessPiece(&pieceArray[targetIndex]);
    else if(targetIndex == len) PrintChessPiece(&pieceArray[targetIndex - 1]);
    else
    {
        abs(pieceArray[targetIndex]._MDistance < - searchDistance) <
        abs(pieceArray[targetIndex - 1]._MDistance - searchDistance) ?
        PrintChessPiece(&pieceArray[targetIndex]) : PrintChessPiece(&pieceArray[targetIndex - 1]);
    }

    return 0;
}

void ScanCoordinate(Coordinate *const coord)
{
    scanf(" %c %c", &coord->X, &coord->Y); 
}

void ScanChessPiece(ChessPiece *const piece)
{
    scanf(" %s", piece->Name);
    ScanCoordinate(&piece->Coord);
}

void PrintChessPiece(const ChessPiece *const piece)
{
    printf("%s %c%c\n", piece->Name, piece->Coord.X, piece->Coord.Y);
}

int CalculateManhattanDistance(const Coordinate* const c1, const Coordinate* const c2)
{
    return abs(c1->X - c2->X) + abs(c1->Y - c2->Y);
}

void SwapChessPieces(ChessPiece *const piece1, ChessPiece *const piece2)
{
    ChessPiece temp = *piece1;
    *piece1 = *piece2;
    *piece2 = temp;
}

void SortChessPieceArray(ChessPiece *const pieceArray, size_t length)
{
    for(size_t i = 0; i < length - 1; i++)
    {
        for(size_t j = i + 1; j < length; j++)
        {
            if(pieceArray[i]._MDistance > pieceArray[j]._MDistance)
            {
                SwapChessPieces(&pieceArray[i], &pieceArray[j]);
            }
        }
    }
}

int GetLowerBound(ChessPiece *const pieceArray, size_t length, int targetDistance)
{
    int low = 0, high = length - 1;
    while(low <= high)
    {
        int mid = (low + high) / 2;

        if(pieceArray[mid]._MDistance == targetDistance)
        {
            return mid;
        }
        else if(pieceArray[mid]._MDistance > targetDistance)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return low;
}