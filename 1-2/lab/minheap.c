#include<bits/stdc++.h>
using namespace std;

// A class for Min Heap
class MinHeap{
    int *heap_array; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap

public:
    // Constructor: Initialise a capacity and heap_array;
    MinHeap(int capacity){
        this->heap_size = 0;
        this->capacity = capacity;
        this->heap_array = new int[capacity];
    }

    // method to heapify a subtree with the root at given index i
    void MinHeapify(int i){
        /* A recursive method to heapify 'heap_array' */
        int l = left(i);
        int r = right(i);

        int smallest = i;
        if (l < heap_size && heap_array[l] < heap_array[i])
            smallest = l;
        if (r < heap_size && heap_array[r] < heap_array[smallest])
            smallest = r;

        if (smallest != i){
            swap(heap_array[i], heap_array[smallest]);
            MinHeapify(smallest);
        }
    }

    // method to get index of parent of node at index i
    int parent(int i){ return (i-1)/2; }

    // method to get index of left child of node at index i
    int left(int i){ return (2*i + 1); }

    // method to get index of right child of node at index i
    int right(int i){ return (2*i + 2); }

    // method to remove minimum element (or root) from min heap
    int extractMin(){
        if (heap_size <= 0)
            return INT_MAX;
        if (heap_size == 1){
            heap_size--;
            return heap_array[0];
        }

        // remove the minimum value from the heap.
        int root = heap_array[0];
        heap_array[0] = heap_array[heap_size-1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    // method to decrease key value of key at index i to new_val
    void decreaseKey(int i, int new_val){
        heap_array[i] = new_val;
        while (i != 0 && heap_array[parent(i)] > heap_array[i]){
            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
        }
    }

    // Returns the minimum key (key at root) from min heap
    int getMin(){ return heap_array[0]; }

    // method deletes key at index i
    // (It first reduced value to minus infinite, then calls extractMin() )
    void deleteKey(int i){
        decreaseKey(i, INT_MIN);
        extractMin();
    }

    // method to inserts a new key 'k'
    void insertKey(int k){
        if (heap_size == capacity){
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        // Inserting the new key at the end
        int i = heap_size;
        heap_array[heap_size++] = k;

        while (i != 0 && heap_array[parent(i)] > heap_array[i]){
            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
        }
    }
};

// Driver program to test above functions
int main(){
    MinHeap h(11);
    h.insertKey(15);
    h.insertKey(2);
    h.insertKey(3);
    h.insertKey(1);
    h.insertKey(45);
    h.insertKey(5);
    h.insertKey(4);
    cout << "minimum element: " << h.extractMin() << endl;
    cout << "second minimum element: " << h.getMin() << endl;
    return 0;
}
