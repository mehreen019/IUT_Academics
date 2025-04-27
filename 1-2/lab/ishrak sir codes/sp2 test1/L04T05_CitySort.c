#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXCITYNAMELEN 20
#define MAXCITYARRLEN 100

typedef struct city
{
    char Name[MAXCITYNAMELEN + 1];
    double X, Y;
    double _distanceFromA;
} City;

double GetCityDistance(const City *const cityA, const City *const cityB);
void ScanCity(City *const city, const City *const reference);
void PrintCityNameAndDistance(const City *const city);
void SwapCities(City *const cityA, City *const cityB);
void SortCities(City *const cityArray, size_t length);

int main(void)
{
    size_t len;
    City cityArray[MAXCITYARRLEN];

    scanf("%zu", &len);
    ScanCity(&cityArray[0], NULL);
    for(size_t i = 1; i < len; i++)
    {
        ScanCity(&cityArray[i], &cityArray[0]);
    }

    SortCities(cityArray, len);

    for(size_t i = 0; i < len; i++)
    {
        PrintCityNameAndDistance(&cityArray[i]);
    }
    return 0;
}

double GetCityDistance(const City *const cityA, const City *const cityB)
{
    return sqrt((cityA->X - cityB->X) * (cityA->X - cityB->X) + (cityA->Y - cityB->Y) * (cityA->Y - cityB->Y));
}

void ScanCity(City *const city, const City *const reference)
{
    if(!reference)
    {
        scanf("%s%lf%lf", city->Name, &city->X, &city->Y);
        city->_distanceFromA = 0.0;
    }
    else
    {
        scanf("%s%lf%lf", city->Name, &city->X, &city->Y);
        city->_distanceFromA = GetCityDistance(city, reference);
    }
}

void PrintCityNameAndDistance(const City *const city)
{
    printf("%s %g\n", city->Name, city->_distanceFromA);
}

void SwapCities(City *const cityA, City *const cityB)
{
    City temp = *cityA;
    *cityA = *cityB;
    *cityB = temp;
}

void SortCities(City *const cityArray, size_t length)
{
    for(size_t i = 0; i < length - 1; i++)
    {
        for(size_t j = i + 1; j < length; j++)
        {
            if(cityArray[i]._distanceFromA > cityArray[j]._distanceFromA)
            {
                SwapCities(&cityArray[i], &cityArray[j]);
            }
        }
    }
}