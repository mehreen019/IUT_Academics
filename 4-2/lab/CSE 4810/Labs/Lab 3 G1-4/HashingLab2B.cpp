#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cmath>

using namespace std;
using namespace std::chrono;

enum Mode { LINEAR_PROBING, DOUBLE_HASHING };
enum SlotState { EMPTY, OCCUPIED, DELETED };

struct HashEntry {
    int key;
    SlotState state = EMPTY;
};

class HashTable {
private:
    int capacity;
    Mode mode;
    vector<HashEntry> table;
    const double KNUTH_A = 0.6180339887; // Constant A for multiplication method

    int hash1(int key) {
        // TODO: Implement primary hash function using the Multiplication Method
        // Formula: floor(m * ((key * A) mod 1))
        return 0; 
    }

    int hash2(int key) {
        // TODO: Implement secondary hash function for Double Hashing
        // Must return an odd number to be relatively prime to power-of-2 table size
        return 1; 
    }

public:
    HashTable(int size, Mode m) : capacity(size), mode(m) {
        table.resize(capacity);
    }

    // Inserts a key into the table. 
    void insert(int key) {
        // TODO: Implement insertion logic.
        // Remember to reuse DELETED slots appropriately depending on your search rules.
    }

    // Searches for a key. Returns a pair: <found (bool), probes_counted (int)>
    pair<bool, int> search(int key) {
        int probes = 0;
        bool found = false;
        
        // TODO: Implement search logic.
        // CRITICAL: Increment 'probes' every single time you check a slot.
        // Note: You must scan past DELETED slots during a search!
        
        return {found, probes};
    }

    // Deletes a key by replacing its state with DELETED
    void remove(int key) {
        // TODO: Implement lazy deletion logic
    }
};

// Generates uniform random or sequential data keys
vector<int> generateKeys(int count) {
    vector<int> data;
    for (int i = 1; i <= count; i++) {
        data.push_back(i * 7 + 3); // Basic distinct keys
    }
    return data;
}

int main() {
    int m = 1024; // Assigned power-of-2 table size
    
    ofstream outFile("data.txt");
    outFile << "#Alpha\tTime_LP\tTime_DH\tProbes_LP\tProbes_DH\n";

    cout << "Starting empirical profiling for Flavor 2 (Lazy Deletion Overhead)..." << endl;

    // Loop through target active load factors (0.1 to 0.45)
    // We stop early because we insert 2x elements and delete half to create the sentinels
    for (double alpha = 0.1; alpha <= 0.45; alpha += 0.05) {
        int activeElements = static_cast<int>(m * alpha);
        int totalToInsert = activeElements * 2; // Insert double the elements
        
        vector<int> keys = generateKeys(totalToInsert);

        // ==========================================
        // PROFILE LINEAR PROBING
        // ==========================================
        HashTable lpTable(m, LINEAR_PROBING);
        for (int key : keys) {
            lpTable.insert(key);
        }
        // Delete half the keys to pollute the paths with DELETED sentinels
        for (int i = 0; i < totalToInsert; i += 2) {
            lpTable.remove(keys[i]);
        }
        
        // Run Successful Searches on the remaining keys
        long long lpTotalProbes = 0;
        auto startLP = high_resolution_clock::now();
        for (int i = 1; i < totalToInsert; i += 2) {
            auto result = lpTable.search(keys[i]);
            lpTotalProbes += result.second;
        }
        auto stopLP = high_resolution_clock::now();
        auto durationLP = duration_cast<microseconds>(stopLP - startLP).count();
        double avgProbesLP = (double)lpTotalProbes / activeElements;

        // ==========================================
        // PROFILE DOUBLE HASHING
        // ==========================================
        HashTable dhTable(m, DOUBLE_HASHING);
        for (int key : keys) {
            dhTable.insert(key);
        }
        for (int i = 0; i < totalToInsert; i += 2) {
            dhTable.remove(keys[i]);
        }
        
        long long dhTotalProbes = 0;
        auto startDH = high_resolution_clock::now();
        for (int i = 1; i < totalToInsert; i += 2) {
            auto result = dhTable.search(keys[i]);
            dhTotalProbes += result.second;
        }
        auto stopDH = high_resolution_clock::now();
        auto durationDH = duration_cast<microseconds>(stopDH - startDH).count();
        double avgProbesDH = (double)dhTotalProbes / activeElements;

        // Export data row
        outFile << alpha << "\t\t" << durationLP << "\t\t" << durationDH << "\t\t" 
                << avgProbesLP << "\t\t\t" << avgProbesDH << "\n";
                
        cout << "Finished processing Active Load Factor (\u03B1): " << alpha << endl;
    }

    outFile.close();
    cout << "Profiling completed successfully. Results recorded in data.txt" << endl;
    return 0;
}