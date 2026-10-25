
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;
using Clock = chrono::high_resolution_clock;

// -----------------------------------------------------------------------------
// TODO 1: knapsack_2D
// Full (n+1) x (W+1) table. O(n*W) time AND O(n*W) space.
// -----------------------------------------------------------------------------
int knapsack_2D(int n, int W, const vector<int>& weights, const vector<int>& values) {
    // TODO: 
    return -1; // placeholder, replace me
}

// -----------------------------------------------------------------------------
// TODO 2: knapsack_1D
// Single W+1 array. O(n*W) time, O(W) space.
// IMPORTANT: the capacity loop MUST run descending (see Live Challenge).
// -----------------------------------------------------------------------------
int knapsack_1D(int n, int W, const vector<int>& weights, const vector<int>& values,
                 bool ascending_bug = false /* set true only for the live challenge demo */) {
    // TODO: 
    return -1; // placeholder, replace me
}

int main() {
    // ---------------- Sanity Check ----------------
    cout << "--- KNAPSACK SANITY CHECK ---" << endl;
    vector<int> w_sanity = {1, 3, 4, 5};
    vector<int> v_sanity = {1, 4, 5, 7};
    int W_sanity = 7;
    cout << "2D : " << knapsack_2D(4, W_sanity, w_sanity, v_sanity) << " (Expected 9)" << endl;
    cout << "1D : " << knapsack_1D(4, W_sanity, w_sanity, v_sanity) << " (Expected 9)" << endl;
    cout << "-----------------------------" << endl;

    // ---------------- Stress Test: n = 5000, W = 50000 ----------------
    int n = 5000, W = 50000;
    vector<int> weights(n), values(n);
    for (int i = 0; i < n; i++) {
        weights[i] = (i % 50) + 1;
        values[i] = (i % 97) + 1;
    }

    // ---------------- Memory Profiling ----------------
    long long bytes_2D = (long long)sizeof(int) * (n + 1) * (long long)(W + 1);
    long long bytes_1D = (long long)sizeof(int) * (W + 1);
    cout << "Estimated 2D table memory: " << bytes_2D << " bytes (~"
         << bytes_2D / (1024.0 * 1024.0) << " MB)" << endl;
    cout << "Estimated 1D array memory: " << bytes_1D << " bytes (~"
         << bytes_1D / 1024.0 << " KB)" << endl;

    // NOTE: allocating the full 2D table at n=5000, W=50000 needs roughly
    // 5000 * 50000 * 4 bytes ~ 1 GB. Only actually run knapsack_2D here if
    // your machine has enough RAM -- otherwise comment it out and rely on
    // the printed estimate to make your OOM argument.
    //
    double t2D = 0.0;
    // {
    //     auto start = Clock::now();
    //     int result = knapsack_2D(n, W, weights, values);
    //     auto end = Clock::now();
    //     t2D = chrono::duration<double, milli>(end - start).count();
    //     cout << "2D result: " << result << "  time: " << t2D << " ms" << endl;
    // }

    double t1D;
    {
        auto start = Clock::now();
        int result = knapsack_1D(n, W, weights, values);
        auto end = Clock::now();
        t1D = chrono::duration<double, milli>(end - start).count();
        cout << "1D result: " << result << "  time: " << t1D << " ms" << endl;
    }

    ofstream fout("data_knapsack.txt");
    fout << "n W bytes_2D bytes_1D time_1D_ms time_2D_ms\n";
    fout << n << " " << W << " " << bytes_2D << " " << bytes_1D << " " << t1D << " "<<t2D<<"\n";
    fout.close();

    // ---------------- Live Challenge: The Loop Direction Drill ----------------
    // Run once with ascending_bug = true on a SMALL instance and show the
    // wrong (inflated) answer, since items get reused within the same pass.
    {
        vector<int> w_small = {2, 3, 4};
        vector<int> v_small = {3, 4, 5};
        int W_small = 6;
        int correct = knapsack_1D(3, W_small, w_small, v_small, false);
        int buggy   = knapsack_1D(3, W_small, w_small, v_small, true);
        cout << "Loop Direction Drill -> correct (descending): " << correct
             << "  buggy (ascending): " << buggy << endl;
    }

    cout << "Data written to data_knapsack.txt" << endl;
    return 0;
}