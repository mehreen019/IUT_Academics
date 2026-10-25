// =============================================================================
// CSE 4810: Algorithm Engineering -- Lab (Group 3)
// Task: Bipartite Maximum Matching via Max-Flow (Super Source / Super Sink)
// =============================================================================
// You will reduce Bipartite Maximum Matching to Max-Flow:
//   - Add a super SOURCE connected to every LEFT vertex.
//   - Add a super SINK connected to every RIGHT vertex.
//   - Keep the original bipartite edges (left -> right) in the middle.
//   - Run Max-Flow from source to sink. The max-flow VALUE equals the
//     maximum matching size, and the saturated left->right edges give you
//     the matching itself.
//
// Vertex numbering convention (fixed, do not change):
//   vertex 0                       = source
//   vertex 1 .. nLeft               = left vertices  (left i = vertex i+1)
//   vertex nLeft+1 .. nLeft+nRight  = right vertices (right j = vertex nLeft+1+j)
//   vertex nLeft+nRight+1           = sink
// =============================================================================

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const long long INF_CAP = (long long)1e15;

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
    // TODO 1: Implement bfs_augmenting_path(source, sink, parentEdge)
    // -------------------------------------------------------------------
    // Requirements:
    //   - BFS from `source` over edges with residual capacity
    //     (capacity - flow > 0).
    //   - Record parentEdge[v] = {u, edge_index} for every vertex visited.
    //   - Return true if `sink` was reached.
    bool bfs_augmenting_path(int source, int sink, vector<pair<int,int>> &parentEdge) {
        // TODO: implement BFS over residual edges
        return false;
    }

    // -------------------------------------------------------------------
    // TODO 2: Implement max_flow(source, sink)
    // -------------------------------------------------------------------
    // Requirements:
    //   - Repeatedly call bfs_augmenting_path to find an augmenting path.
    //   - Compute the bottleneck (min residual capacity) along each path
    //     found, push that much flow along every edge on the path, and
    //     subtract it from every corresponding reverse edge.
    //   - Return the total max-flow value.
    long long max_flow(int source, int sink) {
        // TODO: implement Edmonds-Karp using bfs_augmenting_path above
        return -1;
    }

    // -------------------------------------------------------------------
    // TODO 3: Implement extract_matching(nLeft, nRight)
    // -------------------------------------------------------------------
    // Requirements: (call this AFTER max_flow has been run to completion)
    //   - Scan every ORIGINAL left->right edge (i.e. edges you added with
    //     add_edge(vertex(left i), vertex(right j), INF_CAP) in
    //     build_matching_network -- skip edges touching the source or sink).
    //   - An edge is part of the matching iff its flow > 0 (each such edge
    //     will carry exactly 1 unit of flow, never more, because the
    //     source->left(i) and right(j)->sink boundary edges cap it at 1).
    //   - Return a vector of (left_i, right_j) pairs using ORIGINAL 0-indexed
    //     ids, i.e. vertex(left i) - 1 = i, vertex(right j) - nLeft - 1 = j.
    vector<pair<int,int>> extract_matching(int nLeft, int nRight) {
        // TODO: scan graph[] for saturated (flow > 0) left->right edges
        // and collect (i, j) pairs
        return {};
    }
};

// -----------------------------------------------------------------------
// TODO 4: Implement build_matching_network(nLeft, nRight, adj)
// -----------------------------------------------------------------------
// Requirements:
//   - `adj[i]` lists the right vertices (0-indexed) that left vertex i
//     (0-indexed) connects to in the original bipartite graph.
//   - Vertex numbering: source = 0, left i = vertex i+1,
//     right j = vertex nLeft+1+j, sink = nLeft+nRight+1.
//
//   *** CAPACITY ASSIGNMENT -- READ THIS CAREFULLY ***
//   - source -> left(i):   capacity 1        for every left vertex i.
//   - right(j) -> sink :   capacity 1        for every right vertex j.
//   - left(i) -> right(j): capacity INF_CAP  for every original edge (i, j).
//
//   Why capacity 1 at the SOURCE and SINK boundary (not infinite)? Because
//   THAT is what forces each left vertex to send at most 1 unit of flow
//   total, and each right vertex to receive at most 1 unit -- i.e. each
//   vertex is matched at most once. The middle (original) edges can safely
//   be given a large/infinite capacity, because the true bottleneck
//   restricting each vertex to "used once" already comes from the boundary
//   edges -- giving the middle edges capacity 1 as well would not change
//   the answer, but giving the BOUNDARY edges infinite capacity WOULD
//   break correctness (a single left vertex could then be matched to
//   several right vertices simultaneously).
FlowNetwork build_matching_network(int nLeft, int nRight, const vector<vector<int>> &adj) {
    int source = 0, sink = nLeft + nRight + 1;
    FlowNetwork fn(nLeft + nRight + 2);

    // TODO: add source -> left(i) edges, capacity 1
    // TODO: add right(j) -> sink edges, capacity 1
    // TODO: add left(i) -> right(j) edges, capacity INF_CAP, for every
    //       edge in adj[]

    return fn;
}

// =============================================================================
// -------------------------- Graph generation utils --------------------------
// =============================================================================
vector<vector<int>> make_random_bipartite(int nLeft, int nRight, double density, unsigned seed) {
    vector<vector<int>> adj(nLeft);
    mt19937 rng(seed);
    uniform_real_distribution<double> coin(0.0, 1.0);

    for (int u = 0; u < nLeft; u++) {
        for (int v = 0; v < nRight; v++) {
            if (coin(rng) < density) {
                adj[u].push_back(v);
            }
        }
        if (adj[u].empty()) {
            uniform_int_distribution<int> vd(0, nRight - 1);
            adj[u].push_back(vd(rng));
        }
    }
    return adj;
}

// =============================================================================
// ------------------------------- Sanity Check -------------------------------
// =============================================================================
void sanity_check() {
    // 4 left vertices {0,1,2,3}, 4 right vertices {0,1,2,3}
    // Edges: 0-{0,1}, 1-{0}, 2-{1,2}, 3-{2,3}
    // Known maximum matching size = 4
    int nLeft = 4, nRight = 4;
    vector<vector<int>> adj(nLeft);
    adj[0] = {0, 1};
    adj[1] = {0};
    adj[2] = {1, 2};
    adj[3] = {2, 3};

    FlowNetwork fn = build_matching_network(nLeft, nRight, adj);
    int source = 0, sink = nLeft + nRight + 1;
    long long result = fn.max_flow(source, sink);
    auto matching = fn.extract_matching(nLeft, nRight);

    cout << "--- BIPARTITE MATCHING (MAX-FLOW) SANITY CHECK ---\n";
    cout << "Max-Flow value (= matching size) : " << result << " (Expected 4)\n";
    cout << "Matched pairs (left, right):\n";
    for (auto &[l, r] : matching) {
        cout << "  left " << l << " <-> right " << r << "\n";
    }
    cout << "-----------------------------------------------------\n";

    // Second fixed example with a KNOWN deficiency (not a perfect matching)
    int nLeft2 = 3, nRight2 = 2;
    vector<vector<int>> adj2(nLeft2);
    adj2[0] = {0};
    adj2[1] = {0};
    adj2[2] = {1};
    FlowNetwork fn2 = build_matching_network(nLeft2, nRight2, adj2);
    int source2 = 0, sink2 = nLeft2 + nRight2 + 1;
    long long result2 = fn2.max_flow(source2, sink2);
    cout << "--- SECOND SANITY CHECK (deficient matching) ---\n";
    cout << "Computed matching size : " << result2 << " (Expected 2)\n";
    cout << "---------------------------------------------------\n";
}

// =============================================================================
// ------------------------------ Live Profiling -------------------------------
// =============================================================================
void run_benchmark() {
    ofstream fout("data_matching.txt");
    fout << "n density time_ms matching_size\n";

    vector<int> sizes = {50, 100, 200, 350, 500, 700};
    vector<double> densities = {0.05, 0.3};

    for (double density : densities) {
        for (int n : sizes) {
            vector<vector<int>> adj = make_random_bipartite(n, n, density, 2024 + n);
            FlowNetwork fn = build_matching_network(n, n, adj);
            int source = 0, sink = n + n + 1;

            auto t1 = high_resolution_clock::now();
            long long result = fn.max_flow(source, sink);
            auto t2 = high_resolution_clock::now();

            double ms = duration<double, milli>(t2 - t1).count();
            cout << "n=" << n << " density=" << density
                 << " time_ms=" << ms << " matching_size=" << result << "\n";
            fout << n << " " << density << " " << ms << " " << result << "\n";
        }
    }
    fout.close();
    cout << "Benchmark data written to data_matching.txt\n";
}

int main() {
    sanity_check();
    cout << "\nRunning benchmark (this may take a moment for large n)...\n";
    run_benchmark();
    return 0;
}
