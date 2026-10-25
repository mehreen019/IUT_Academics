// =============================================================================
// OBST.cpp
// Task 4: Structural Engineering of an Optimal BST (OBST)
// Compile: g++ -O2 -o obst OBST.cpp
// Run:     ./obst
// =============================================================================
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <climits>
#include <random>
#include <map>

using namespace std;
using Clock = chrono::high_resolution_clock;

const double INF = 1e18;

// -----------------------------------------------------------------------------
// TODO 1: obst_naive
// Standard OBST recurrence, but the frequency-range sum freq_sum(i, j) is
// recomputed with a fresh loop for EVERY root candidate r, even though it
// does not depend on r. That redundant O(n) work inside the root loop turns
// what should be an O(n^3) recurrence into O(n^4).
// Fills cost[][] and root[][] as side effects (pass empty n x n tables in).
// keys are implicit 0..n-1; probabilities[i] is the search frequency of key i.
// -----------------------------------------------------------------------------
double obst_naive(const vector<double>& probabilities,
                   vector<vector<double>>& cost,
                   vector<vector<int>>& root) {
    int n = probabilities.size();
    // TODO: 
    return -1.0; // placeholder, replace me
}

// -----------------------------------------------------------------------------
// TODO 2: obst_optimized
// Identical recurrence to obst_naive, but freq_sum(i, j) is computed ONCE per
// (i, j) pair via a precomputed prefix-sum array, in O(1), instead of being
// recomputed inside the root loop. This removes the hidden O(n) factor and
// restores the textbook O(n^3) bound.
// -----------------------------------------------------------------------------
double obst_optimized(const vector<double>& probabilities,
                       vector<vector<double>>& cost,
                       vector<vector<int>>& root) {
    int n = probabilities.size();
    // TODO: 
    return -1.0; // placeholder, replace me
}

// -----------------------------------------------------------------------------
// Benchmark helper: simulate weighted lookups against a std::map (red-black
// tree backed) and count comparisons via a comparator wrapper.
// -----------------------------------------------------------------------------
struct CountingLess {
    static long long comparisons;
    bool operator()(int a, int b) const {
        comparisons++;
        return a < b;
    }
};
long long CountingLess::comparisons = 0;

long long simulate_rbtree_lookups(int n, const vector<double>& probabilities, int trials) {
    map<int, int, CountingLess> tree;
    for (int i = 0; i < n; i++) tree[i] = i;

    mt19937 rng(42);
    discrete_distribution<int> dist(probabilities.begin(), probabilities.end());

    CountingLess::comparisons = 0;
    for (int t = 0; t < trials; t++) {
        int key = dist(rng);
        tree.find(key); // counted via CountingLess
    }
    return CountingLess::comparisons;
}

// TODO 3 (optional extension): walk the OBST root[][] table to build an actual
// tree structure and count real comparisons per simulated lookup (depth of
// the key in the OBST), instead of relying only on the cost[0][n-1] value.
long long simulate_obst_lookups(int n, const vector<double>& probabilities,
                                 const vector<vector<int>>& root, int trials) {
    // TODO: for each simulated key (drawn the same way as simulate_rbtree_lookups),
    //       walk down from root[0][n-1], following the recursive root structure
    //       (if key == root[lo][hi] stop; if key < root go left to root[lo][r-1];
    //       else go right to root[r+1][hi]), counting one comparison per node
    //       visited until the key is found.
    return -1; // placeholder, replace me
}

int main() {
    // ---------------- Sanity Check ----------------
    cout << "--- OBST SANITY CHECK (n=4) ---" << endl;
    vector<double> probs_sanity = {0.1, 0.2, 0.4, 0.3}; // classic small example
    vector<vector<double>> cost_sanity_a, cost_sanity_b;
    vector<vector<int>> root_sanity_a, root_sanity_b;

    double result_naive = obst_naive(probs_sanity, cost_sanity_a, root_sanity_a);
    double result_opt = obst_optimized(probs_sanity, cost_sanity_b, root_sanity_b);
    cout << "Naive     : " << result_naive << " (Expected 1.7)" << endl;
    cout << "Optimized : " << result_opt << " (Expected 1.7, should match Naive)" << endl;
    cout << "--------------------------------" << endl;

    // ---------------- Helper: build a skewed distribution ----------------
    auto build_skewed = [](int n) {
        vector<double> probabilities(n, 0.0);
        int k1 = n / 10, k2 = n / 2, k3 = (4 * n) / 5; // 3 "hot" keys
        probabilities[k1] = 0.4;
        probabilities[k2] = 0.3;
        probabilities[k3] = 0.2;
        double remaining = 0.1 / (n - 3);
        for (int i = 0; i < n; i++) {
            if (i != k1 && i != k2 && i != k3) probabilities[i] = remaining;
        }
        return probabilities;
    };

    // ---------------- Live Experimentation Run: n = 50, 100, 150 ----------------
    ofstream fout("data_obst.txt");
    fout << "n time_naive_ms time_optimized_ms rb_comparisons obst_comparisons\n";

    vector<vector<double>> cost_last;
    vector<vector<int>> root_last;
    vector<double> probs_last;
    int n_last = 0;

    for (int n : {50, 100, 150}) {
        vector<double> probabilities = build_skewed(n);
        vector<vector<double>> cost_a, cost_b;
        vector<vector<int>> root_a, root_b;

        auto s1 = Clock::now();
        obst_naive(probabilities, cost_a, root_a);
        auto e1 = Clock::now();
        double t_naive = chrono::duration<double, milli>(e1 - s1).count();

        auto s2 = Clock::now();
        obst_optimized(probabilities, cost_b, root_b);
        auto e2 = Clock::now();
        double t_opt = chrono::duration<double, milli>(e2 - s2).count();

        cout << "n=" << n << "  naive=" << t_naive << "ms  optimized=" << t_opt << "ms" << endl;
        fout << n << " " << t_naive << " " << t_opt << " NA NA\n";

        cost_last = cost_b; root_last = root_b; probs_last = probabilities; n_last = n;
    }

    // ---------------- Stress Test: n = 400 ----------------
    // Naive is still O(n^4) but with n=400 this completes in a few seconds;
    // kill it manually if it exceeds 30 seconds on your machine.
    {
        int n = 400;
        vector<double> probabilities = build_skewed(n);
        vector<vector<double>> cost_a, cost_b;
        vector<vector<int>> root_a, root_b;

        auto s1 = Clock::now();
        obst_naive(probabilities, cost_a, root_a);
        auto e1 = Clock::now();
        double t_naive = chrono::duration<double, milli>(e1 - s1).count();

        auto s2 = Clock::now();
        obst_optimized(probabilities, cost_b, root_b);
        auto e2 = Clock::now();
        double t_opt = chrono::duration<double, milli>(e2 - s2).count();

        cout << "STRESS n=400  naive=" << t_naive << "ms  optimized=" << t_opt << "ms" << endl;
        fout << n << " " << t_naive << " " << t_opt << " NA NA\n";
    }

    // ---------------- The Benchmark: 100,000 weighted lookups (n = 100) ----------------
    int trials = 100000;
    long long rb_comparisons = simulate_rbtree_lookups(n_last, probs_last, trials);
    long long obst_comparisons = simulate_obst_lookups(n_last, probs_last, root_last, trials);

    cout << "Red-Black tree total comparisons over " << trials << " lookups (n="
         << n_last << "): " << rb_comparisons << endl;
    cout << "OBST total comparisons over " << trials << " lookups (n=" << n_last
         << "): " << obst_comparisons << " (requires TODO 3 to be implemented)" << endl;

    fout << n_last << " NA NA " << rb_comparisons << " " << obst_comparisons << "\n";
    fout.close();

    cout << "Data written to data_obst.txt" << endl;
    return 0;
}
