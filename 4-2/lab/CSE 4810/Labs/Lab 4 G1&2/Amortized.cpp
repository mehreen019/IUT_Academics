#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class DynamicTable {
private:
    int* table;
    int capacity;
    int size;

public:
    DynamicTable() : capacity(1), size(0) {
        table = new int[capacity];
    }

    ~DynamicTable() { delete[] table; }

    // This function returns the ACTUAL cost of the operation.
    // Cost = 1 (for insertion) + (number of elements copied during resize).
    int insert(int val) {
        int actual_cost = 1; 
        
        // TODO: Check if the table is full (size == capacity)
        // If full:
        // 1. Create a new_table with double the capacity (capacity * 2)
        // 2. Copy all elements from the old table to the new one
        // 3. For every element copied, increment 'actual_cost'
        // 4. Delete the old table, update the pointer, and update capacity
        
        // TODO: Insert the new value and increment the size
        
        return actual_cost;
    }
};

void runSanityCheck() {
    DynamicTable dt;
    // For capacity 1:
    // Insert 1: size 1, cap 1 (No copy) -> Cost 1
    // Insert 2: size 1->2, cap 1->2 (Copy 1 elem) -> Cost 2
    // Insert 3: size 2->3, cap 2->4 (Copy 2 elems) -> Cost 3
    
    cout << "--- SANITY CHECK ---" << endl;
    cout << "Insert 1: Cost " << dt.insert(10) << " (Expected 1)" << endl;
    cout << "Insert 2: Cost " << dt.insert(20) << " (Expected 2)" << endl;
    cout << "Insert 3: Cost " << dt.insert(30) << " (Expected 3)" << endl;
    cout << "--------------------" << endl;
}

int main() {
    runSanityCheck(); // Validate logic before massive run
    
    DynamicTable dt;
    int N = 10000;
    long long total_cost = 0;
    
    ofstream out("data_dyntable.txt");
    out << "#Op_Index Actual_Cost Running_Average\n";

    for (int i = 1; i <= N; ++i) {
        int cost = dt.insert(i);
        total_cost += cost;
        double running_avg = (double)total_cost / i;
        
        out << i << " " << cost << " " << fixed << setprecision(2) << running_avg << "\n";
    }
    
    out.close();
    cout << "Data collection complete. File 'data_dyntable.txt' generated." << endl;
    return 0;
}