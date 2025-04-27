#include <stdio.h>

int SwapInts(int *const a, int *const b);
int SortArray(int *const array, size_t length);
int CalculatePairCountFromSortedArray(const int *const array, size_t length);

int main(void)
{
    int array[1000];
    size_t len;
    scanf("%zu", &len);
    
    for(int i = 0; i < len; i++)
    {
        scanf("%d", &array[i]);
    }

    SortArray(array, len);
    int pairCount = CalculatePairCountFromSortedArray(array, len);
    printf("%d\n", pairCount);
    return 0;
}

int SwapInts(int *const a, int *const b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int SortArray(int *const array, size_t length)
{
    for(size_t i = 0; i < length - 1; i++)
    {
        for(size_t j = i + 1; j < length; j++)
        {
            if(array[i] > array[j])
            {
                SwapInts(&array[i], &array[j]);
            }
        }
    }
}

int CalculatePairCountFromSortedArray(const int *const array, size_t length)
{
    int count = 0;
    for(size_t i = 0; i < length - 1; i++)
    {
        if( !(array[i] ^ array[i+1]) )
        {
            count++;
            i++;
        }
    }
    return count;
}