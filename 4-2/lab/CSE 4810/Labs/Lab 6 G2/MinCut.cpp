// =============================================================================
// CSE 4810: Algorithm Engineering -- Lab (Group 2)
// Task 2: Min-Cut from Scratch (via the Max-Flow Min-Cut Theorem)
// =============================================================================
// You will implement:
//   1) Edmonds-Karp max-flow (same core algorithm as the Max-Flow task --
//      you are re-implementing it here to build the underlying engine).
//   2) A min-cut extraction step: after max-flow saturates, find the set S
//      of vertices reachable from the source in the RESIDUAL graph. The
//      min cut consists of all original edges (u, v) with u in S, v not in
//      S, and original capacity > 0. By the Max-Flow Min-Cut theorem, the
//      total capacity of these edges equals the max-flow value.
// =============================================================================

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct FlowEdge {
    int to;
    long long capacity;
    long long flow;
    int rev;
};

class FlowNetwork {
public:
    int n;
    vector<vector<FlowEdge>> graph;

    FlowNetwork(int n) : n(n), graph(n) {}

    void add_edge(int u, int v, long long capacity) {
        FlowEdge a{v, capacity, 0, (int)graph[v].size()};
        FlowEdge b{u, 0, 0, (int)graph[u].size()};
        graph[u].push_back(a);
        graph[v].push_back(b);
    }

    // -------------------------------------------------------------------
    // TODO 1: Implement bfs_augmenting_path (same requirements as the
    // Max-Flow task -- BFS over residual edges, record parentEdge[]).
    // -------------------------------------------------------------------
    bool bfs_augmenting_path(int source, int sink, vector<pair<int,int>> &parentEdge) {
        // TODO
        return false;
    }

    // -------------------------------------------------------------------
    // TODO 2: Implement max_flow(source, sink) (same requirements as the
    // Max-Flow task -- repeatedly augment along shortest paths).
    // -------------------------------------------------------------------
    long long max_flow(int source, int sink) {
        // TODO
        return -1;
    }

    // -------------------------------------------------------------------
    // TODO 3: Implement find_min_cut(source)
    // -------------------------------------------------------------------
    // Requirements: (call this AFTER max_flow has been run to completion)
    //   - Run a BFS/DFS from `source` using ONLY edges with residual
    //     capacity (capacity - flow > 0) to find the set S of reachable
    //     vertices in the residual graph.
    //   - Scan all ORIGINAL edges (capacity > 0, skip the artificial
    //     reverse edges) and collect every edge (u, v) such that u is in S
    //     and v is NOT in S -- these crossing edges form the min cut.
    //   - Return a vector of (u, v, capacity) triples for the min cut.
    vector<tuple<int,int,long long>> find_min_cut(int source) {
        // TODO
        return {};
    }
};

// =============================================================================
// ------------------------------- Sanity Check -------------------------------
// =============================================================================
void sanity_check() {
    // Same 6-vertex network as Group 1's Max-Flow sanity check.
    // Known max-flow = min-cut = 23
    FlowNetwork fn(6);
    fn.add_edge(0, 1, 16);
    fn.add_edge(0, 2, 13);
    fn.add_edge(1, 2, 10);
    fn.add_edge(2, 1, 4);
    fn.add_edge(1, 3, 12);
    fn.add_edge(2, 4, 14);
    fn.add_edge(3, 2, 9);
    fn.add_edge(3, 5, 20);
    fn.add_edge(4, 3, 7);
    fn.add_edge(4, 5, 4);

    long long flow = fn.max_flow(0, 5);
    auto cut = fn.find_min_cut(0);
    long long cutCapacity = 0;
    for (auto &[u, v, cap] : cut) cutCapacity += cap;

    cout << "--- MIN-CUT SANITY CHECK (6 vertices) ---\n";
    cout << "Max-Flow value        : " << flow << " (Expected 23)\n";
    cout << "Min-Cut edges:\n";
    for (auto &[u, v, cap] : cut) {
        cout << "  " << u << " -> " << v << " (capacity " << cap << ")\n";
    }
    cout << "Total Min-Cut capacity: " << cutCapacity
         << " (should equal Max-Flow value = " << flow << ")\n";
    cout << "--------------------------------------------\n";
}

// =============================================================================
// ------------------- Verification: Max-Flow == Min-Cut ----------------------
// =============================================================================
FlowNetwork make_random_flow_network(int n, double density, unsigned seed, int maxCap = 50) {
    FlowNetwork fn(n);
    mt19937 rng(seed);
    uniform_int_distribution<int> cap(1, maxCap);

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin() + 1, order.end() - 1, rng);
    for (int i = 0; i + 1 < n; i++) {
        fn.add_edge(order[i], order[i + 1], cap(rng));
    }

    long long maxExtra = (long long)(density * n * (n - 1) / 2.0);
    uniform_int_distribution<int> vd(0, n - 1);
    long long added = 0, attempts = 0;
    while (added < maxExtra && attempts < maxExtra * 20 + 1000) {
        attempts++;
        int u = vd(rng), v = vd(rng);
        if (u == v) continue;
        fn.add_edge(u, v, cap(rng));
        added++;
    }
    return fn;
}

void verify_maxflow_mincut_equivalence() {
    cout << "\n--- VERIFICATION: Max-Flow value == Min-Cut capacity ---\n";
    vector<int> sizes = {15, 30};
    for (int n : sizes) {
        FlowNetwork fn = make_random_flow_network(n, 0.2, 42 + n);
        long long flow = fn.max_flow(0, n - 1);
        auto cut = fn.find_min_cut(0);
        long long cutCapacity = 0;
        for (auto &[u, v, cap] : cut) cutCapacity += cap;

        cout << "n=" << n << "  max-flow=" << flow
             << "  min-cut=" << cutCapacity
             << "  match=" << (flow == cutCapacity ? "YES" : "NO -- BUG") << "\n";
    }
    cout << "----------------------------------------------------------\n";
}

// =============================================================================
// ------------------------------ Live Profiling -------------------------------
// =============================================================================
void run_benchmark() {
    ofstream fout("data_mincut.txt");
    fout << "n density time_ms\n";

    vector<int> sizes = {20, 40, 80, 120, 160};
    vector<double> densities = {0.1, 0.25};

    for (double density : densities) {
        for (int n : sizes) {
            FlowNetwork fn = make_random_flow_network(n, density, 555 + n);

            auto t1 = high_resolution_clock::now();
            long long flow = fn.max_flow(0, n - 1);
            auto cut = fn.find_min_cut(0);
            auto t2 = high_resolution_clock::now();

            double ms = duration<double, milli>(t2 - t1).count();
            cout << "n=" << n << " density=" << density
                 << " time_ms=" << ms << " flow=" << flow << "\n";
            fout << n << " " << density << " " << ms << "\n";
        }
    }
    fout.close();
    cout << "Benchmark data written to data_mincut.txt\n";
}

int main() {
    sanity_check();
    verify_maxflow_mincut_equivalence();
    cout << "\nRunning benchmark...\n";
    run_benchmark();
    return 0;
}
