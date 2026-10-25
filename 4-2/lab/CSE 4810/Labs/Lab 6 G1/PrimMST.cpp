// =============================================================================
// CSE 4810: Algorithm Engineering -- Lab (Group 1)
// Task 1: Structural Engineering of Prim's Algorithm
// =============================================================================
// You will implement TWO variants of Prim's Algorithm:
//   1) prim_naive  : O(V^2) array-based variant (no priority queue)
//   2) prim_heap   : O(E log V) binary-heap (priority_queue) based variant
//
// Both must return the SAME total MST weight on any connected, undirected,
// weighted graph. Do not change function signatures.
// =============================================================================

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Edge {
    int to;
    long long weight;
};

typedef vector<vector<Edge>> Graph; // adjacency list, 0-indexed vertices

// -----------------------------------------------------------------------
// TODO 1: Implement prim_naive(n, graph)
// -----------------------------------------------------------------------
// Requirements:
//   - Maintain a key[] array (min edge weight connecting each vertex to the
//     growing MST) and an inMST[] boolean array.
//   - At every step, LINEARLY SCAN all n vertices to find the minimum-key
//     vertex not yet in the MST (this is the O(V) "select" step that runs
//     V times, giving O(V^2) overall -- do NOT use a heap here).
//   - Relax all neighbors of the newly added vertex.
//   - Return the total MST weight (sum of the key[] values used to add
//     each vertex, excluding the starting vertex's initial key of 0).
//
// Assume the graph is connected. Start from vertex 0.
long long prim_naive(int n, const Graph &graph) {
    // TODO: implement the O(V^2) array-based Prim's algorithm
    return -1;
}

// -----------------------------------------------------------------------
// TODO 2: Implement prim_heap(n, graph)
// -----------------------------------------------------------------------
// Requirements:
//   - Use a min-priority-queue (std::priority_queue with negation, or
//     with a custom comparator) keyed on edge weight.
//   - Maintain an inMST[] boolean array. Push (weight, vertex) pairs and
//     pop the minimum; skip vertices already in the MST (lazy deletion --
//     do NOT implement decrease-key by hand).
//   - Push all outgoing edges of a newly added vertex onto the heap.
//   - Return the total MST weight.
//
// Assume the graph is connected. Start from vertex 0.
long long prim_heap(int n, const Graph &graph) {
    // TODO: implement the O(E log V) binary-heap based Prim's algorithm
    return -1;
}

// =============================================================================
// -------------------------- Graph generation utils --------------------------
// =============================================================================
Graph make_random_connected_graph(int n, double density, unsigned seed, int maxW = 1000) {
    Graph g(n);
    mt19937 rng(seed);
    uniform_int_distribution<int> w(1, maxW);

    // Guarantee connectivity with a random spanning path first
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);
    for (int i = 1; i < n; i++) {
        int u = perm[i - 1], v = perm[i];
        int wt = w(rng);
        g[u].push_back({v, wt});
        g[v].push_back({u, wt});
    }

    // Add extra random edges based on density (0.0 - 1.0)
    long long maxExtraEdges = (long long)(density * n * (n - 1) / 2.0);
    uniform_int_distribution<int> vd(0, n - 1);
    set<pair<int,int>> existing;
    for (int i = 1; i < n; i++) existing.insert({min(perm[i-1],perm[i]), max(perm[i-1],perm[i])});

    long long added = 0, attempts = 0;
    while (added < maxExtraEdges && attempts < maxExtraEdges * 20 + 1000) {
        attempts++;
        int u = vd(rng), v = vd(rng);
        if (u == v) continue;
        int a = min(u, v), b = max(u, v);
        if (existing.count({a, b})) continue;
        int wt = w(rng);
        g[a].push_back({b, wt});
        g[b].push_back({a, wt});
        existing.insert({a, b});
        added++;
    }
    return g;
}

// =============================================================================
// ------------------------------- Sanity Check -------------------------------
// =============================================================================
void sanity_check() {
    // Small fixed graph, n = 5, known MST weight
    // Edges: (0,1,2) (0,3,6) (1,2,3) (1,3,8) (1,4,5) (2,4,7) (3,4,9)
    int n = 5;
    Graph g(n);
    auto addEdge = [&](int u, int v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };
    addEdge(0,1,2);
    addEdge(0,3,6);
    addEdge(1,2,3);
    addEdge(1,3,8);
    addEdge(1,4,5);
    addEdge(2,4,7);
    addEdge(3,4,9);

    long long expected = 16; // MST: (0,1,2)+(1,2,3)+(1,4,5)+(0,3,6) = 16
    long long naive_res = prim_naive(n, g);
    long long heap_res  = prim_heap(n, g);

    cout << "--- PRIM'S MST SANITY CHECK (n=5) ---\n";
    cout << "Naive : " << naive_res << " (Expected " << expected << ")\n";
    cout << "Heap  : " << heap_res  << " (Expected " << expected << ", should match Naive)\n";
    cout << "--------------------------------------\n";
}

// =============================================================================
// ------------------------------ Live Profiling -------------------------------
// =============================================================================
void run_benchmark() {
    ofstream fout("data_prim.txt");
    fout << "n density naive_ms heap_ms\n";

    vector<int> sizes = {100, 300, 600, 1000, 1500, 2000};
    vector<double> densities = {0.02, 0.3}; // sparse, dense

    for (double density : densities) {
        for (int n : sizes) {
            Graph g = make_random_connected_graph(n, density, 12345 + n);

            auto t1 = high_resolution_clock::now();
            long long r1 = prim_naive(n, g);
            auto t2 = high_resolution_clock::now();
            long long r2 = prim_heap(n, g);
            auto t3 = high_resolution_clock::now();

            double naive_ms = duration<double, milli>(t2 - t1).count();
            double heap_ms  = duration<double, milli>(t3 - t2).count();

            cout << "n=" << n << " density=" << density
                 << " naive_ms=" << naive_ms << " heap_ms=" << heap_ms
                 << " (match=" << (r1 == r2 ? "yes" : "NO") << ")\n";

            fout << n << " " << density << " " << naive_ms << " " << heap_ms << "\n";
        }
    }
    fout.close();
    cout << "Benchmark data written to data_prim.txt\n";
}

int main() {
    sanity_check();
    cout << "\nRunning benchmark (this may take a moment for large n)...\n";
    run_benchmark();
    return 0;
}
