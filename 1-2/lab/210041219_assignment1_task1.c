#include <stdio.h>
#include <stdlib.h>

/// @brief The function returns a pointer to the specific element of a 2D integer array at index
/// position `rowIndex` and `colIndex`; the dimension of the array is specified by rowCount and colCount
/// @param arr Flattened (1D) array to look for specific index
/// @param rowCount Number of rows in the array
/// @param colCount Number of columns in the array
/// @param rowIndex Index of the row to access
/// @param colIndex Index of the column to access
/// @return An integer pointer pointing to the required index
int* Access2DArrayElement(
    int* const arr,
    size_t rowCount, size_t colCount,
    size_t rowIndex, size_t colIndex
);

// The following structure is for testing and should not be changed
typedef struct _testParams
{
    int*    Array;
    size_t  RowCount;
    size_t  ColCount;
    size_t  RowIndex;
    size_t  ColIndex;
    int     ExpectedValue;
} TestParams;

// The following function declaration is for testing and should not be changed
void TEST_Access2DArrayElement(const TestParams* const testParameters);

// Main function serves as a driver for testing and should not be changed
int main(void)
{
    int ARR[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; // Array with 12 elements

    TestParams testParamsList[] = {
        {
            .Array = ARR,
            .RowCount = 3, .ColCount = 4,
            .RowIndex = 1, .ColIndex = 2,
            .ExpectedValue = 7
        },
        {
            .Array = ARR,
            .RowCount = 2, .ColCount = 6,
            .RowIndex = 1, .ColIndex = 5,
            .ExpectedValue = 12
        },
        {
            .Array = ARR,
            .RowCount = 2, .ColCount = 6,
            .RowIndex = 1, .ColIndex = 5,
            .ExpectedValue = 0 // Should be zero since it is changed in the previous access
        }
    };

    const size_t testParamsLen = sizeof(testParamsList) / sizeof(TestParams);

    for(size_t i = 0U; i < testParamsLen; i++)
    {
        TEST_Access2DArrayElement(testParamsList + i);
    }

    return 0;
}

int* Access2DArrayElement(
    int* const arr,
    size_t rowCount, size_t colCount,
    size_t rowIndex, size_t colIndex
)
{
    // ---------------------------------------[Write over here]---------------------------------------
    // ToDo: Insert you array processing and accessing logic over here, then return the proper pointer

    return &arr[rowIndex*colCount + colIndex];

    return NULL;
    // -----------------------------------------------------------------------------------------------
}

// The following function definition is for testing and should not be changed
void TEST_Access2DArrayElement(const TestParams* const testParameters)
{
    static size_t counter = 1U;
    int* fetchedPtr = Access2DArrayElement(testParameters->Array,
        testParameters->RowCount, testParameters->ColCount,
        testParameters->RowIndex, testParameters->ColIndex);
    int fetchedValue = *fetchedPtr;
    if(fetchedValue == testParameters->ExpectedValue)
    {
        printf("%.2zu) [OK] Accessed index [%zu][%zu] in the %zu x %zu array.\n", counter++,
            testParameters->RowIndex, testParameters->ColIndex,
            testParameters->RowCount, testParameters->ColCount);
        printf("\tFetched Value <%d> == Expected Value <%d>\n",
            fetchedValue, testParameters->ExpectedValue);

        // Update the accessed value to 0
        *fetchedPtr = 0;
        printf("\tChanged the accessed value %d to 0 (Zero)!\n", fetchedValue);
    }
    else
    {
        printf("%.2zu) [ERROR] Could not access index [%zu][%zu] in the %zu x %zu array.\n",  counter++,
            testParameters->RowIndex, testParameters->ColIndex,
            testParameters->RowCount, testParameters->ColCount);
        printf("\tFetched Value <%d> != Expected Value <%d>\n",
            fetchedValue, testParameters->ExpectedValue);
    }
}
