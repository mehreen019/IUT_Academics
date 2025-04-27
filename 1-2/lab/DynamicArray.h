#pragma once

#define DEFAULT_INIT_CAPACITY 2

typedef struct _intDArrayController
{
    int* Elements;
    size_t Count;
    size_t Capacity;
} IntDArrayController;

/// @brief Create a new empty dynamic array for storing integer with DEFAULT_INIT_CAPACITY
/// @return A new controller structure for the initialized array 
IntDArrayController IntDArray_New(void);

/// @brief Frees and empties an existing controller (call after usage has ended)
/// @param controller Pointer to the controller to free
void IntDArray_Free(IntDArrayController *restrict controller);

/// @brief Adds a new element to the dynamic array
/// @param controller Pointer to the controller to add to
/// @param element The value to add to the dynamic array
/// @return 1 if successful, 0 if failed to grow memory, -1 if the controller is already freed
int IntDArray_Add(IntDArrayController *restrict controller, int element);

/// @brief Removes the last element in the dynamic array
/// @param controller Pointer to the controller to remove the last element from
/// @return 1 if successful, 0 if the array does not have any element in it
int IntDArray_RemoveLast(IntDArrayController *restrict controller);

/// @brief Prints the elements, count and capacity of the dynamic array
/// @param controller Pointer to the controller to print
void IntDArray_Print(IntDArrayController *restrict controller);

/// @brief A safe function for getting a value from the dynamic array
/// @param controller Pointer to the controller to fetch value from
/// @param index Index of the value to get
/// @return Value of the element if it exists, INT_MIN in the case of out of range index
int IntDArray_Get(IntDArrayController *restrict controller, size_t index);

/// @brief A safe function for setting a value in the dynamic array
/// @param controller Pointer to the controller to set value to
/// @param index Index of the value to get
/// @param value New value to set
/// @return 1 if successful, 0 in the case of out of range index
int IntDArray_Set(IntDArrayController *restrict controller, size_t index, int value);