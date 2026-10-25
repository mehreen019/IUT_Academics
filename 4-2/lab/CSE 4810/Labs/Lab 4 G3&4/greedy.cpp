#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Representing a node in the Huffman Tree structure
struct Node {
    int freq;
    // Note: Left and right pointers can be omitted here since we only need 
    // to simulate the cost of matching frequencies to build the tree structure.
    Node(int f) : freq(f) {}
};

// Comparator for the min-heap priority queue
struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Approach 1: O(N^2) Naive Array Search
// Repeatedly scans a vector to find the two nodes with the lowest frequencies.
long long buildHuffmanNaive(vector<int>& freqs) {
    vector<Node*> nodes;
    for (int f : freqs) {
        nodes.push_back(new Node(f));
    }

    long long total_internal_cost = 0;

    // TODO: [IMPLEMENTATION REQUIRED]
    // Loop until only 1 node remains in the 'nodes' vector:
    // 1. Perform a linear scan to find the index of the absolute smallest frequency node.
    // 2. Perform a second linear scan to find the next smallest frequency node.
    // 3. Combine their frequencies into a new parent node.
    // 4. Add the parent's frequency to 'total_internal_cost'.
    // 5. Erase the two merged nodes from the vector and insert the new parent node.
    
    // Clean up memory
    for (Node* n : nodes) delete n;
    
    return total_internal_cost;
}

// Approach 2: O(N log N) Priority Queue (Min-Heap)
// Uses a min-heap structure to extract the two lowest frequency elements in O(log N) time.
long long buildHuffmanPQ(vector<int>& freqs) {
    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;
    for (int f : freqs) {
        minHeap.push(new Node(f));
    }

    long long total_internal_cost = 0;

    // TODO: [IMPLEMENTATION REQUIRED]
    // Loop until the minHeap size is 1:
    // 1. Pop the top two elements from 'minHeap' (the two absolute lowest frequencies).
    // 2. Combine their frequencies into a new parent node.
    // 3. Add the parent's frequency to 'total_internal_cost'.
    // 4. Push the new parent node back into the 'minHeap'.

    // Clean up memory
    if(!minHeap.empty()) delete minHeap.top();

    return total_internal_cost;
}

int main() {
    // Input scale sizes ranging up to 30,000 leaf nodes
    vector<int> N_values = {1000, 5000, 10000, 15000, 20000, 30000};
    
    ofstream out("data_huffman.txt");
    out << "#Input_N Time_Naive Time_PQ\n";

    cout << "Starting Huffman Benchmarking Simulation..." << endl;

    for (int N : N_values) {
        // Generate pseudo-random frequencies for the leaf nodes
        vector<int> freqs(N);
        for (int i = 0; i < N; ++i) {
            freqs[i] = (rand() % 500) + 1;
        }

        // Measure Naive Vector Scan Runtime
        auto start1 = high_resolution_clock::now();
        buildHuffmanNaive(freqs);
        auto stop1 = high_resolution_clock::now();
        double duration_naive = duration_cast<duration<double>>(stop1 - start1).count();

        // Measure Priority Queue Runtime
        auto start2 = high_resolution_clock::now();
        buildHuffmanPQ(freqs);
        auto stop2 = high_resolution_clock::now();
        double duration_pq = duration_cast<duration<double>>(stop2 - start2).count();

        out << N << " " << duration_naive << " " << duration_pq << "\n";
        cout << "N = " << N << " processing complete." << endl;
    }

    out.close();
    cout << "Data cleanly recorded in 'data_huffman.txt'." << endl;
    return 0;
}