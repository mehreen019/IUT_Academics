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

int main(void)
{
    size_t len;
    ChessPiece pieceArray[52];
    Coordinate refCoord = {'h', '8'};
    scanf("%zu", &len);
    for(size_t i = 0; i < len; i++)
    {
        ScanChessPiece(&pieceArray[i]);
        //PrintChessPiece(&pieceArray[i]);
        pieceArray[i]._MDistance = CalculateManhattanDistance(&pieceArray[i].Coord, &refCoord);
    }

    SortChessPieceArray(pieceArray, len);
    printf("[OUTPUT]\n");
    for(size_t i = 0; i < len; i++)
    {
        PrintChessPiece(&pieceArray[i]);
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