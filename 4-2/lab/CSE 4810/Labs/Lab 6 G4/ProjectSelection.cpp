// =============================================================================
// CSE 4810: Algorithm Engineering -- Lab (Group 4)
// Task: Project Selection Problem (Open-Pit Mining) via Max-Flow Min-Cut
// =============================================================================
// You are given a set of "blocks" (projects). Each block i has a net value
// value[i] (positive = profit if extracted, negative = cost if extracted).
// Some blocks REQUIRE other blocks to be extracted first (precedence
// constraints), e.g. you must remove an overlying block before an
// underlying one becomes accessible.
//
// You will:
//   1) Build the corresponding flow network (source -> profitable blocks,
//      costly blocks -> sink, infinite-capacity precedence edges).
//   2) Implement Edmonds-Karp max-flow from scratch to solve it.
//   3) Extract the optimal selection set from the min-cut and report the
//      maximum achievable net profit.
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
    // TODO 3: Implement find_selected_set(source)
    // -------------------------------------------------------------------
    // Requirements: (call this AFTER max_flow has been run to completion)
    //   - Run BFS/DFS from `source` using ONLY edges with residual
    //     capacity (capacity - flow > 0) to find the set S of vertices
    //     reachable in the residual graph.
    //   - The set of SELECTED BLOCKS is exactly S, minus the artificial
    //     `source` vertex itself. Return this as a sorted vector of block
    //     indices (0-indexed, matching the `value[]` array -- NOT
    //     including the source/sink node IDs).
    vector<int> find_selected_set(int source, int numBlocks) {
        // TODO: BFS/DFS from source over residual edges, collect blocks
        // (vertex ids 1..numBlocks, mapped back to 0..numBlocks-1) in S
        return {};
    }
};

// -----------------------------------------------------------------------
// TODO 4: Implement build_project_selection_network(value, precedence)
// -----------------------------------------------------------------------
// Requirements:
//   - `value[i]` is the net value of block i (i = 0 .. numBlocks-1).
//     Positive = profit, negative = cost.
//   - `precedence[i]` is a list of blocks that block i DEPENDS ON (i.e.
//     block i can only be selected if every block in precedence[i] is
//     also selected).
//   - Vertex numbering convention: vertex 0 = source, vertices 1..numBlocks
//     correspond to blocks 0..numBlocks-1 (block i = vertex i+1),
//     vertex numBlocks+1 = sink.
//   - For every block i with value[i] > 0: add edge source -> vertex(i)
//     with capacity value[i].
//   - For every block i with value[i] < 0: add edge vertex(i) -> sink
//     with capacity -value[i] (i.e. the cost, made positive).
//   - For every dependency: if block i requires block j (j is in
//     precedence[i]), add edge vertex(i) -> vertex(j) with capacity
//     INF_CAP (this forces: if i is on the source side of the min-cut,
//     j must be too, otherwise the cut would have to sever this
//     infinite-capacity edge, which is never optimal).
//   - Return the constructed FlowNetwork (with numBlocks + 2 vertices).
FlowNetwork build_project_selection_network(const vector<long long> &value,
                                             const vector<vector<int>> &precedence) {
    int numBlocks = value.size();
    int source = 0, sink = numBlocks + 1;
    FlowNetwork fn(numBlocks + 2);

    // TODO: add source->block and block->sink edges based on value[]
    // TODO: add infinite-capacity precedence edges

    return fn;
}

// =============================================================================
// ------------------------------- Sanity Check -------------------------------
// =============================================================================
void sanity_check() {
    // 5 blocks. value[] = profit (+) or cost (-).
    //   Block 0: +10 (profit, no prerequisites)
    //   Block 1: +8  (profit, requires Block 0)
    //   Block 2: -3  (cost, requires Block 0)
    //   Block 3: +6  (profit, requires Block 1 and Block 2)
    //   Block 4: -20 (very costly, requires Block 3 -- should NOT be selected)
    //
    // Total available profit (if selection were free) = 10+8+6 = 24
    // Optimal choice: select {0,1,2,3}, skip block 4 (its cost outweighs its
    // unlock value). Net profit = 10 + 8 - 3 + 6 = 21.
    vector<long long> value = {10, 8, -3, 6, -20};
    vector<vector<int>> precedence(5);
    precedence[1] = {0};
    precedence[2] = {0};
    precedence[3] = {1, 2};
    precedence[4] = {3};

    FlowNetwork fn = build_project_selection_network(value, precedence);
    int numBlocks = value.size();
    int source = 0, sink = numBlocks + 1;

    long long totalProfit = 0;
    for (long long v : value) if (v > 0) totalProfit += v;

    long long minCut = fn.max_flow(source, sink);
    long long optimalNet = totalProfit - minCut;

    vector<int> selected = fn.find_selected_set(source, numBlocks);

    cout << "--- PROJECT SELECTION SANITY CHECK (5 blocks) ---\n";
    cout << "Total available profit : " << totalProfit << "\n";
    cout << "Min-cut value          : " << minCut << "\n";
    cout << "Optimal net profit      : " << optimalNet << " (Expected 21)\n";
    cout << "Selected blocks         : ";
    for (int b : selected) cout << b << " ";
    cout << "(Expected 0 1 2 3)\n";

    // Verify no selected block violates a precedence constraint
    vector<bool> isSelected(numBlocks, false);
    for (int b : selected) isSelected[b] = true;
    bool valid = true;
    for (int i = 0; i < numBlocks; i++) {
        if (!isSelected[i]) continue;
        for (int req : precedence[i]) {
            if (!isSelected[req]) {
                valid = false;
                cout << "VIOLATION: block " << i << " selected without prerequisite " << req << "\n";
            }
        }
    }
    cout << "Precedence constraints satisfied: " << (valid ? "YES" : "NO -- BUG") << "\n";
    cout << "----------------------------------------------------\n";
}

// =============================================================================
// -------------------------- Grid generation utils ---------------------------
// =============================================================================
// Generates a simple "open-pit" style grid: blocks arranged in `rows` layers,
// `cols` blocks wide. Each block in row r (r > 0) requires the block
// directly "above" it (row r-1, same column) plus its two diagonal
// neighbors, mimicking a real pit's overburden-removal constraint. Deeper
// rows tend to have higher profit but the top rows tend to have small
// costs (representing overburden removal).
pair<vector<long long>, vector<vector<int>>> make_mining_grid(int rows, int cols, unsigned seed) {
    int numBlocks = rows * cols;
    vector<long long> value(numBlocks);
    vector<vector<int>> precedence(numBlocks);
    mt19937 rng(seed);
    uniform_int_distribution<int> costDist(1, 5);
    uniform_int_distribution<int> profitDist(5, 30);

    auto idx = [&](int r, int c) { return r * cols + c; };

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int id = idx(r, c);
            if (r < rows / 3) {
                value[id] = -costDist(rng); // shallow overburden = cost
            } else {
                value[id] = profitDist(rng); // deeper ore = profit
            }
            if (r > 0) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nc = c + dc;
                    if (nc >= 0 && nc < cols) {
                        precedence[id].push_back(idx(r - 1, nc));
                    }
                }
            }
        }
    }
    return {value, precedence};
}

// =============================================================================
// ------------------------------ Live Profiling -------------------------------
// =============================================================================
void run_benchmark() {
    ofstream fout("data_mining.txt");
    fout << "numBlocks time_ms net_profit\n";

    vector<pair<int,int>> gridSizes = {
        {5, 5}, {10, 10}, {15, 15}, {20, 20}, {25, 25}, {30, 30}
    };

    for (auto [rows, cols] : gridSizes) {
        auto [value, precedence] = make_mining_grid(rows, cols, 4242 + rows * cols);
        int numBlocks = value.size();

        auto t1 = high_resolution_clock::now();
        FlowNetwork fn = build_project_selection_network(value, precedence);
        int source = 0, sink = numBlocks + 1;
        long long totalProfit = 0;
        for (long long v : value) if (v > 0) totalProfit += v;
        long long minCut = fn.max_flow(source, sink);
        auto t2 = high_resolution_clock::now();

        long long netProfit = totalProfit - minCut;
        double ms = duration<double, milli>(t2 - t1).count();

        cout << "grid=" << rows << "x" << cols << " blocks=" << numBlocks
             << " time_ms=" << ms << " net_profit=" << netProfit << "\n";
        fout << numBlocks << " " << ms << " " << netProfit << "\n";
    }
    fout.close();
    cout << "Benchmark data written to data_mining.txt\n";
}

int main() {
    sanity_check();
    cout << "\nRunning benchmark (this may take a moment for large grids)...\n";
    run_benchmark();
    return 0;
}
