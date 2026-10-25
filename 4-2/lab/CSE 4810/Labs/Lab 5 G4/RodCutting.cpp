// =============================================================================
// RodCutting.cpp
// Task 1: The Performance Paradox in Rod Cutting
// Compile: g++ -O2 -o rodcut RodCutting.cpp
// Run:     ./rodcut
// =============================================================================
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <climits>
#include <cstring>

using namespace std;
using Clock = chrono::high_resolution_clock;

// -----------------------------------------------------------------------------
// TODO 1: cut_rod_naive
// Pure recursion, no memoization. Tries every first-cut length.
// -----------------------------------------------------------------------------
int cut_rod_naive(int n, const vector<int>& prices) {
    // TODO: 


    return -1; // placeholder, replace me
}

// -----------------------------------------------------------------------------
// TODO 2: cut_rod_memoized
// Top-down recursion with a memo array. memo[k] == -1 means "not solved yet".
// -----------------------------------------------------------------------------
int cut_rod_memoized(int n, const vector<int>& prices, vector<int>& memo) {
    // TODO: 


    return -1; // placeholder, replace me
}

// -----------------------------------------------------------------------------
// TODO 3: cut_rod_bottom_up
// Iterative tabulation, no recursion / no call stack growth.
// -----------------------------------------------------------------------------
int cut_rod_bottom_up(int n, const vector<int>& prices) {
    // TODO: 


    return -1; // placeholder, replace me
}


vector<int> build_price_table(int n) {
    vector<int> prices(n);
    for (int i = 0; i < n; i++) {
        prices[i] = (i + 1) * 3 - (i % 4); 
    }
    return prices;
}

template <typename Func, typename... Args>
double time_call_ms(Func f, Args&&... args) {
    auto start = Clock::now();
    f(std::forward<Args>(args)...);
    auto end = Clock::now();
    return chrono::duration<double, milli>(end - start).count();
}

int main() {
    // ---------------- Sanity Check ----------------
    cout << "--- RODCUT SANITY CHECK (n=4) ---" << endl;
    vector<int> sanity_prices = {1, 5, 8, 9}; // classic CLRS example
    vector<int> memo(5, -1);
    cout << "Naive     : " << cut_rod_naive(4, sanity_prices) << " (Expected 10)" << endl;
    cout << "Memoized  : " << cut_rod_memoized(4, sanity_prices, memo) << " (Expected 10)" << endl;
    cout << "Bottom-Up : " << cut_rod_bottom_up(4, sanity_prices) << " (Expected 10)" << endl;
    cout << "----------------------------------" << endl;

    // ---------------- Live Experimentation Run: n = 10, 20, 30 ----------------
    ofstream fout("data_rodcut.txt");
    fout << "n naive_ms memo_ms bottomup_ms\n";

    for (int n : {10, 20, 30}) {
        vector<int> prices = build_price_table(n);
        vector<int> memo_arr(n + 1, -1);

        double t_naive = time_call_ms([&]() { cut_rod_naive(n, prices); });
        fill(memo_arr.begin(), memo_arr.end(), -1);
        double t_memo = time_call_ms([&]() { cut_rod_memoized(n, prices, memo_arr); });
        double t_bottom = time_call_ms([&]() { cut_rod_bottom_up(n, prices); });

        cout << "n=" << n << "  naive=" << t_naive << "ms  memo=" << t_memo
             << "ms  bottomup=" << t_bottom << "ms" << endl;
        fout << n << " " << t_naive << " " << t_memo << " " << t_bottom << "\n";
    }

    // ---------------- Stress Test: n = 40, memoized + bottom-up ONLY ----------------
    // NOTE: Do NOT call cut_rod_naive(40, ...) here -- it will effectively hang.
    {
        int n = 40;
        vector<int> prices = build_price_table(n);
        vector<int> memo_arr(n + 1, -1);

        double t_memo = time_call_ms([&]() { cut_rod_memoized(n, prices, memo_arr); });
        double t_bottom = time_call_ms([&]() { cut_rod_bottom_up(n, prices); });

        cout << "STRESS n=40  memo=" << t_memo << "ms  bottomup=" << t_bottom << "ms" << endl;
        fout << n << " NA " << t_memo << " " << t_bottom << "\n";
    }

    fout.close();

    // ---------------- Live Challenge: Stack Overflow Demonstration ----------------
    // To force a stack overflow, uncomment the block below and increase n until
    // your program crashes. Report the exact n at which it crashes -- this number
    // depends on your OS's default stack size and is NOT a fixed language constant.
    //
    // int crash_n = 50000;
    // vector<int> crash_prices = build_price_table(crash_n);
    // vector<int> crash_memo(crash_n + 1, -1);
    // cout << cut_rod_memoized(crash_n, crash_prices, crash_memo) << endl;
    //
    // Compare against the bottom-up version at the same n, which should run fine:
    // vector<int> crash_prices2 = build_price_table(crash_n);
    // cout << cut_rod_bottom_up(crash_n, crash_prices2) << endl;

    cout << "Data written to data_rodcut.txt" << endl;
    return 0;
}