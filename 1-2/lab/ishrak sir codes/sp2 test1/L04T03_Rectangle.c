#include <stdio.h>

typedef struct rectangle
{
    float XLow;
    float XHigh;
    float YLow;
    float YHigh;
} Rectangle;


Rectangle GetRectangleFrom4Coordinates(float *X, float *Y);
int IsPointInside(Rectangle *rect, float xPoint, float yPoint);

int main(void)
{
    float X[4], Y[4];
    float Xpoint, Ypoint;
    for(int i = 0; i < 4; i++)
    {
        scanf("%f ,%f", &X[i], &Y[i]);
    }
    scanf("%f ,%f", &Xpoint, &Ypoint);
    Rectangle rect = GetRectangleFrom4Coordinates(X, Y);

    printf( IsPointInside(&rect, Xpoint, Ypoint) ? "Yes\n" : "No\n" );
    return 0;
}

Rectangle GetRectangleFrom4Coordinates(float *X, float *Y)
{
    float minX = X[0];
    float maxX = X[0];
    float minY = Y[0];
    float maxY = Y[0];
    for(int i = 1; i < 4; i++)
    {
        if(X[i] < minX) minX = X[i];
        else if(X[i] > maxX) maxX = X[i];

        if(Y[i] < minY) minY = Y[i];
        else if(Y[i] > maxY) maxY = Y[i];
    }

    return (Rectangle){minX, maxX, minY, maxY};
}

int IsPointInside(Rectangle *rect, float xPoint, float yPoint)
{
    if(
        (rect->XLow <= xPoint && rect->XHigh >= xPoint)
        &&
        (rect->YLow <= yPoint && rect->YHigh >= yPoint)
    ) return 1;
    else return 0;
}