#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Heuristic 1: Standard Largest-First
int greedyStandard(vector<int> coins, int amount) {
    sort(coins.rbegin(), coins.rend());
    int count = 0;
    
    // TODO: [IMPLEMENTATION REQUIRED]
    // 1. Loop through the sorted 'coins' vector.
    // 2. While the current 'coin' is <= the remaining 'amount':
    //    a. Subtract the coin from 'amount'.
    //    b. Increment the 'count'.
    
    return count;
}

// Heuristic 2: Remainder-Aware Greedy
int greedyRemainderAware(vector<int> coins, int amount) {
    sort(coins.rbegin(), coins.rend());
    int count = 0;
    
    while (amount > 0) {
        int best_coin = coins.back(); 
        
        // TODO: [IMPLEMENTATION REQUIRED]
        // 1. Iterate through the available 'coins'.
        // 2. Find the largest coin that fits (<= amount).
        // 3. LOOK-AHEAD LOGIC: If picking this coin results in a remainder
        //    that is divisible by the next smaller coin, prioritize this one.
        // 4. Subtract the selected 'best_coin' from 'amount' and increment 'count'.
        
        break; // Remove this break once logic is implemented to avoid infinite loops
    }
    return count;
}

void runSanityCheck() {
    vector<int> non_canonical = {20, 15, 5, 4, 1};
    int val = 23;
    
    cout << "--- COIN CHANGE SANITY CHECK ---" << endl;
    cout << "For V=23 (Non-Canonical):" << endl;
    cout << "Standard Greedy   : " << greedyStandard(non_canonical, val) << " coins" << endl;
    cout << "Remainder-Aware   : " << greedyRemainderAware(non_canonical, val) << " coins" << endl;
    cout << "--------------------------------" << endl;
}

int main() {
    runSanityCheck();
    
    // System 1: Canonical (Greedy should work perfectly)
    vector<int> sys1 = {1, 5, 10, 25}; 
    // System 2: Non-Canonical (Greedy fails)
    vector<int> sys2 = {1, 4, 5, 15, 20}; 
    
    ofstream out("data_coins.txt");
    out << "#Value Std_Canonical Remainder_Canonical Std_NonCanonical Remainder_NonCanonical\n";
    
    for(int v = 1; v <= 100; ++v) {
        out << v << " " 
            << greedyStandard(sys1, v) << " " << greedyRemainderAware(sys1, v) << " "
            << greedyStandard(sys2, v) << " " << greedyRemainderAware(sys2, v) << "\n";
    }
    
    out.close();
    cout << "Data saved to data_coins.txt" << endl;
    return 0;
}