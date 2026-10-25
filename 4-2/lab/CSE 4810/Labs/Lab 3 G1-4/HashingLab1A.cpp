#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

enum Mode { LINEAR_PROBING, DOUBLE_HASHING };

class HashTable {
private:
    int capacity;
    Mode mode;
    vector<int> table;
    
    int hash1(int key) {
        // TODO: Implement primary hash function using the Division Method
        return 0; 
    }

    int hash2(int key) {
        // TODO: Implement secondary hash function for Double Hashing
        return 1; 
    }

public:
    HashTable(int size, Mode m) : capacity(size), mode(m) {
        table.resize(capacity, -1); // Initialize empty slots with -1
    }

    // Inserts a key into the table. Returns true if successful.
    bool insert(int key) {
        // TODO: Implement insertion logic with proper collision resolution.
        return true;
    }

    // Searches for a key. Returns a pair: <found (bool), probes_counted (int)>
    pair<bool, int> search(int key) {
        int probes = 0;
        bool found = false;
        // TODO: Implement search and prob count logic.
        
        
        return {found, probes};
    }
};

// Generates the crowded structured data (Arithmetic Progressions)
vector<int> generateInsertionKeys(int count) {
    vector<int> data;
    for (int i = 1; i <= count; i++) {
        data.push_back(i * 10); // 10, 20, 30, 40...
    }
    return data;
}

// Generates "Ghost" keys that are guaranteed NOT to be in the table
vector<int> generateUnsuccessfulKeys(int count) {
    vector<int> data;
    for (int i = 1; i <= count; i++) {
        data.push_back(i * 10 + 5); // 15, 25, 35, 45... (Guaranteed mismatch)
    }
    return data;
}

int main() {
    int m = 1009; // Assigned prime table size
    int numTestKeys = 200; // Number of lookup operations to average out timing
    
    ofstream outFile("data.txt");
    outFile << "#Alpha\tTime_LP\tTime_DH\tProbes_LP\tProbes_DH\n";

    cout << "Starting empirical profiling for Flavor 1 (Unsuccessful Searches)..." << endl;

    for (double alpha = 0.1; alpha <= 0.95; alpha += 0.1) {
        int numElements = static_cast<int>(m * alpha);
        
        vector<int> insertionKeys = generateInsertionKeys(numElements);
        vector<int> ghostKeys = generateUnsuccessfulKeys(numTestKeys);

        // ==========================================
        // PROFILE LINEAR PROBING
        // ==========================================
        HashTable lpTable(m, LINEAR_PROBING);
        for (int key : insertionKeys) {
            lpTable.insert(key); // Fill table statically to target alpha
        }

        long long lpTotalProbes = 0;
        auto startLP = high_resolution_clock::now();
        for (int ghostKey : ghostKeys) {
            auto result = lpTable.search(ghostKey);
            lpTotalProbes += result.second; // Accumulate unsuccessful probe steps
        }
        auto stopLP = high_resolution_clock::now();
        auto durationLP = duration_cast<microseconds>(stopLP - startLP).count();
        double avgProbesLP = (double)lpTotalProbes / numTestKeys;

        // ==========================================
        // PROFILE DOUBLE HASHING
        // ==========================================
        HashTable dhTable(m, DOUBLE_HASHING);
        for (int key : insertionKeys) {
            dhTable.insert(key); // Fill table statically to target alpha
        }

        long long dhTotalProbes = 0;
        auto startDH = high_resolution_clock::now();
        for (int ghostKey : ghostKeys) {
            auto result = dhTable.search(ghostKey);
            dhTotalProbes += result.second;
        }
        auto stopDH = high_resolution_clock::now();
        auto durationDH = duration_cast<microseconds>(stopDH - startDH).count();
        double avgProbesDH = (double)dhTotalProbes / numTestKeys;

        // Export data row
        outFile << alpha << "\t\t" << durationLP << "\t\t" << durationDH << "\t\t" 
                << avgProbesLP << "\t\t\t" << avgProbesDH << "\n";
                
        cout << "Finished processing Load Factor (\u03B1): " << alpha << endl;
    }

    outFile.close();
    cout << "Profiling completed successfully. Results recorded in data.txt" << endl;
    return 0;
}