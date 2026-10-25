// =============================================================================
// CSE 4810: Algorithm Engineering -- Lab (Group 2)
// Task 1: Kruskal's Algorithm with an Optimized Union-Find (DSU)
// =============================================================================
// You will implement:
//   1) A Disjoint-Set Union (DSU) structure with UNION BY RANK and PATH
//      COMPRESSION.
//   2) Kruskal's MST algorithm built on top of that DSU.
//
// A brute-force reference (small-n, exponential) is provided at the bottom
// for validating your Kruskal implementation -- do not modify it.
// =============================================================================

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Edge {
    int u, v;
    long long weight;
};

// -----------------------------------------------------------------------
// TODO 1: Implement the DSU class (union by rank + path compression)
// -----------------------------------------------------------------------
class DSU {
public:
    vector<int> parent, rank_;

    DSU(int n) {
        parent.resize(n);
        rank_.assign(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    // TODO: implement find(x) with PATH COMPRESSION.
    // (recursive or iterative two-pass -- either is fine, must compress)
    int find(int x) {
        // TODO
        return -1;
    }

    // TODO: implement unite(x, y) with UNION BY RANK.
    // Return true if a union happened (x and y were in different sets),
    // false if they were already in the same set (this edge would form
    // a cycle).
    bool unite(int x, int y) {
        // TODO
        return false;
    }
};

// -----------------------------------------------------------------------
// TODO 2: Implement kruskal_mst(n, edges)
// -----------------------------------------------------------------------
// Requirements:
//   - Sort all edges by weight ascending.
//   - Use a DSU to process edges in order, adding an edge to the MST only
//     if its endpoints are in different components (use DSU::unite).
//   - Return the total MST weight. If the graph is disconnected, return
//     the weight of the resulting minimum spanning FOREST (sum over all
//     components), i.e. simply keep processing edges until none can be
//     added.
long long kruskal_mst(int n, vector<Edge> edges) {
    // TODO: implement Kruskal's algorithm using the DSU above
    return -1;
}

// =============================================================================
// -------------------------- Graph generation utils --------------------------
// =============================================================================
vector<Edge> make_random_connected_edges(int n, double density, unsigned seed, int maxW = 1000) {
    vector<Edge> edges;
    mt19937 rng(seed);
    uniform_int_distribution<int> w(1, maxW);

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);
    set<pair<int,int>> existing;
    for (int i = 1; i < n; i++) {
        int a = perm[i - 1], b = perm[i];
        int wt = w(rng);
        edges.push_back({a, b, wt});
        existing.insert({min(a,b), max(a,b)});
    }

    long long maxExtra = (long long)(density * n * (n - 1) / 2.0);
    uniform_int_distribution<int> vd(0, n - 1);
    long long added = 0, attempts = 0;
    while (added < maxExtra && attempts < maxExtra * 20 + 1000) {
        attempts++;
        int u = vd(rng), v = vd(rng);
        if (u == v) continue;
        int a = min(u, v), b = max(u, v);
        if (existing.count({a, b})) continue;
        int wt = w(rng);
        edges.push_back({a, b, wt});
        existing.insert({a, b});
        added++;
    }
    return edges;
}

// =============================================================================
// ------------------- Brute-force reference (DO NOT MODIFY) -------------------
// =============================================================================
// Exponential-time reference: tries all subsets of edges of size (n-1) that
// form a spanning tree, keeps the minimum weight one. Only usable for tiny n.
long long brute_force_mst(int n, const vector<Edge> &edges) {
    int m = edges.size();
    long long best = LLONG_MAX;
    vector<int> idx(m);
    iota(idx.begin(), idx.end(), 0);

    // iterate all combinations of (n-1) edges out of m
    vector<bool> mask(m, false);
    fill(mask.end() - (n - 1), mask.end(), true);

    do {
        vector<int> chosen;
        for (int i = 0; i < m; i++) if (mask[i]) chosen.push_back(i);

        // check acyclic + spanning via simple union-find
        vector<int> par(n);
        iota(par.begin(), par.end(), 0);
        function<int(int)> f = [&](int x) { return par[x] == x ? x : par[x] = f(par[x]); };
        long long total = 0;
        bool valid = true;
        for (int i : chosen) {
            int a = f(edges[i].u), b = f(edges[i].v);
            if (a == b) { valid = false; break; }
            par[a] = b;
            total += edges[i].weight;
        }
        if (valid) {
            // check all connected
            int root = f(0);
            for (int i = 1; i < n; i++) if (f(i) != root) { valid = false; break; }
        }
        if (valid) best = min(best, total);
    } while (next_permutation(mask.begin(), mask.end()));

    return best;
}

// =============================================================================
// ------------------------------- Sanity Check -------------------------------
// =============================================================================
void sanity_check() {
    // Same graph as Group 1's Prim sanity check, n=5, MST weight = 16
    int n = 5;
    vector<Edge> edges = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };

    long long expected = brute_force_mst(n, edges);
    long long result = kruskal_mst(n, edges);

    cout << "--- KRUSKAL'S MST SANITY CHECK (n=5) ---\n";
    cout << "Brute-force reference : " << expected << "\n";
    cout << "Kruskal (yours)       : " << result << " (should match reference)\n";
    cout << "-----------------------------------------\n";
}

// =============================================================================
// ------------------------------ Live Profiling -------------------------------
// =============================================================================
void run_benchmark() {
    ofstream fout("data_kruskal.txt");
    fout << "n density time_ms\n";

    vector<int> sizes = {200, 500, 1000, 2000, 4000, 8000};
    vector<double> densities = {0.02, 0.2};

    for (double density : densities) {
        for (int n : sizes) {
            vector<Edge> edges = make_random_connected_edges(n, density, 999 + n);

            auto t1 = high_resolution_clock::now();
            long long result = kruskal_mst(n, edges);
            auto t2 = high_resolution_clock::now();

            double ms = duration<double, milli>(t2 - t1).count();
            cout << "n=" << n << " density=" << density
                 << " edges=" << edges.size() << " time_ms=" << ms
                 << " mst_weight=" << result << "\n";
            fout << n << " " << density << " " << ms << "\n";
        }
    }
    fout.close();
    cout << "Benchmark data written to data_kruskal.txt\n";
}

int main() {
    sanity_check();
    cout << "\nRunning benchmark (this may take a moment for large n)...\n";
    run_benchmark();
    return 0;
}
