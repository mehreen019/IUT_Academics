#pragma once
#include "StudentInfo.h"
#include <stddef.h>
#define DEFAULT_INIT_CAPACITY 2

typedef struct _intDArrayController
{
    StudentInfo* Elements;
    size_t Count;
    size_t Capacity;
} IntDArrayController;

//TASK 1

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
int IntDArray_Add(IntDArrayController *restrict controller, StudentInfo element);

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
StudentInfo IntDArray_Get(IntDArrayController *restrict controller, size_t index);

/// @brief A safe function for setting a value in the dynamic array
/// @param controller Pointer to the controller to set value to
/// @param index Index of the value to get
/// @param value New value to set
/// @return 1 if successful, 0 in the case of out of range index
int IntDArray_Set(IntDArrayController *restrict controller, size_t index, StudentInfo value);

//TASK 2

/// @brief removing element from given index
/// @param controller pointer to the controller to remove from
/// @param i index to remove
/// @return 1 if index is valid, -1 if index is out of range or array capacity or count is 0
int IntDArray_Remove(IntDArrayController *restrict controller, size_t i);

/// @brief inserting given array in given position
/// @param controller pointer to the controller in which array is to be inserted
/// @param i index where array is to be inserted
/// @param value array to insert
/// @return 1 if insertion is succesful, -1 otherwise
int IntDArray_Insert(IntDArrayController *restrict controller, size_t i, StudentInfo value);

/// @brief clearing the entire function but maintaining the space
/// @param controller pointer to the controller which is to be cleared
void IntDArray_Clear(IntDArrayController *restrict controller);

/// @brief finding whether a certain element exists in the dymnamic array from given pointer
/// @param controller pointer to the controller where element is to be found
/// @param t pointer to the element which we are to find
/// @return 1 if it's in the array, -1 otherwise
int IntDArray_Find(IntDArrayController *restrict controller, StudentInfo* t);

/// @brief sorting the dynamic array in ascending or descending order
/// @param controller pointer to the controller which we are sorting
/// @param num 1 if the controller is to be sorted in ascending order, 0 if the controller is to be sorted in descending order
void IntDArray_Sort(IntDArrayController *restrict controller, int num);