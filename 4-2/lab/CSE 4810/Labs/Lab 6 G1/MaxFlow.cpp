// =============================================================================
// CSE 4810: Algorithm Engineering -- Lab (Group 1)
// Task 2: Max-Flow from Scratch (Edmonds-Karp)
// =============================================================================
// You will implement the Edmonds-Karp algorithm (Ford-Fulkerson using BFS to
// find augmenting paths) on a directed, capacitated graph, represented with
// an explicit residual-graph edge list (forward + backward edge pairs).
// =============================================================================

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct FlowEdge {
    int to;
    long long capacity;
    long long flow;
    int rev; // index of the reverse edge in graph[to]
};

class FlowNetwork {
public:
    int n;
    vector<vector<FlowEdge>> graph;

    FlowNetwork(int n) : n(n), graph(n) {}

    // Adds a directed edge u -> v with given capacity, plus a reverse edge
    // v -> u with capacity 0 (used to represent residual "undo" flow).
    void add_edge(int u, int v, long long capacity) {
        FlowEdge a{v, capacity, 0, (int)graph[v].size()};
        FlowEdge b{u, 0, 0, (int)graph[u].size()};
        graph[u].push_back(a);
        graph[v].push_back(b);
    }

    // -------------------------------------------------------------------
    // TODO 1: Implement bfs_augmenting_path(source, sink, parentEdge)
    // -------------------------------------------------------------------
    // Requirements:
    //   - Run a BFS from `source` over edges with residual capacity
    //     (capacity - flow > 0).
    //   - Record, for each visited vertex v, the (u, edge_index) pair used
    //     to reach it in parentEdge[v] = {u, edge_index}, so the augmenting
    //     path can be reconstructed by walking parentEdge[] backwards from
    //     `sink` to `source`.
    //   - Return true if `sink` was reached, false otherwise.
    bool bfs_augmenting_path(int source, int sink, vector<pair<int,int>> &parentEdge) {
        // TODO: implement BFS over residual edges
        return false;
    }

    // -------------------------------------------------------------------
    // TODO 2: Implement max_flow(source, sink)
    // -------------------------------------------------------------------
    // Requirements:
    //   - Repeatedly call bfs_augmenting_path to find an augmenting path.
    //   - For each path found, compute the bottleneck (minimum residual
    //     capacity along the path).
    //   - Push `bottleneck` units of flow along every edge on the path,
    //     and subtract `bottleneck` from the corresponding reverse edges
    //     (i.e., graph[u][idx].flow += bottleneck and
    //           graph[v][rev].flow -= bottleneck).
    //   - Accumulate and return the total max-flow value once no more
    //     augmenting paths exist.
    long long max_flow(int source, int sink) {
        // TODO: implement Edmonds-Karp using bfs_augmenting_path above
        return -1;
    }

    // -------------------------------------------------------------------
    // TODO 3: Implement find_saturated_edges(source)
    // -------------------------------------------------------------------
    // Requirements: (call this AFTER max_flow has been run to completion)
    //   - An original edge (u -> v, capacity C > 0) is "saturated" if
    //     flow == capacity (i.e., residual capacity is 0) on that edge.
    //   - Return a vector of (u, v, capacity) triples for every saturated
    //     ORIGINAL edge (skip the artificial reverse edges, which always
    //     have capacity 0).
    vector<tuple<int,int,long long>> find_saturated_edges() {
        // TODO: scan graph[] for original edges (capacity > 0) with
        // flow == capacity and collect them
        return {};
    }
};

// =============================================================================
// ------------------------------- Sanity Check -------------------------------
// =============================================================================
void sanity_check() {
    // Classic textbook flow network, 6 vertices (0=source, 5=sink)
    // Known max flow = 23
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

    long long result = fn.max_flow(0, 5);
    cout << "--- MAX-FLOW SANITY CHECK (6 vertices) ---\n";
    cout << "Computed Max-Flow : " << result << " (Expected 23)\n";
    cout << "-------------------------------------------\n";
}

// =============================================================================
// --------------------------- Case Study: Pipeline ----------------------------
// =============================================================================
void case_study_pipeline() {
    // A small "pipeline capacity" network: 0 = intake, 7 = delivery station
    // Intermediate nodes represent pumping/junction stations.
    FlowNetwork fn(8);
    fn.add_edge(0, 1, 10);
    fn.add_edge(0, 2, 8);
    fn.add_edge(1, 3, 5);
    fn.add_edge(1, 4, 8);
    fn.add_edge(2, 4, 10);
    fn.add_edge(2, 5, 6);
    fn.add_edge(3, 6, 7);
    fn.add_edge(4, 6, 6);
    fn.add_edge(4, 7, 5);
    fn.add_edge(5, 7, 8);
    fn.add_edge(6, 7, 9);

    long long result = fn.max_flow(0, 7);
    cout << "\n--- CASE STUDY: PIPELINE CAPACITY ---\n";
    cout << "Max deliverable flow (intake -> delivery): " << result << "\n";

    auto saturated = fn.find_saturated_edges();
    cout << "Saturated (bottleneck) edges:\n";
    for (auto &[u, v, cap] : saturated) {
        cout << "  " << u << " -> " << v << " (capacity " << cap << ", fully used)\n";
    }
    cout << "--------------------------------------\n";
}

// =============================================================================
// ------------------------------ Live Profiling -------------------------------
// =============================================================================
FlowNetwork make_random_flow_network(int n, double density, unsigned seed, int maxCap = 50) {
    FlowNetwork fn(n);
    mt19937 rng(seed);
    uniform_int_distribution<int> cap(1, maxCap);

    // Ensure source (0) can reach sink (n-1) via a random layered path
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    // keep 0 first and n-1 last, shuffle the middle
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

void run_benchmark() {
    ofstream fout("data_maxflow.txt");
    fout << "n density time_ms flow_value\n";

    vector<int> sizes = {20, 40, 80, 120, 160};
    vector<double> densities = {0.1, 0.25};

    for (double density : densities) {
        for (int n : sizes) {
            FlowNetwork fn = make_random_flow_network(n, density, 777 + n);

            auto t1 = high_resolution_clock::now();
            long long flow = fn.max_flow(0, n - 1);
            auto t2 = high_resolution_clock::now();

            double ms = duration<double, milli>(t2 - t1).count();
            cout << "n=" << n << " density=" << density
                 << " time_ms=" << ms << " flow=" << flow << "\n";
            fout << n << " " << density << " " << ms << " " << flow << "\n";
        }
    }
    fout.close();
    cout << "Benchmark data written to data_maxflow.txt\n";
}

int main() {
    sanity_check();
    case_study_pipeline();
    cout << "\nRunning benchmark...\n";
    run_benchmark();
    return 0;
}
