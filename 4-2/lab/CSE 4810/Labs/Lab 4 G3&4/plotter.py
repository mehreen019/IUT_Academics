import matplotlib.pyplot as plt
import os
import sys

def plot_queue(filename):
    op_indices, actual_costs, running_averages = [], [], []
    with open(filename, 'r') as f:
        f.readline()
        for line in f:
            parts = line.strip().split()
            if len(parts) == 3:
                op_indices.append(int(parts[0]))
                actual_costs.append(float(parts[1]))
                running_averages.append(float(parts[2]))

    plt.figure(figsize=(12, 6))
    plt.scatter(op_indices, actual_costs, color='dodgerblue', s=3, alpha=0.4, label='Actual Cost (Transfer Spikes)')
    plt.plot(op_indices, running_averages, color='crimson', linewidth=2.5, label='Running Amortized Average')
    plt.title("Two-Stack Queue: Periodic Burst Latency vs. Constant Amortized Cost", fontsize=13, fontweight='bold')
    plt.xlabel("Operation Sequence Index", fontsize=11)
    plt.ylabel("Computational Work Units", fontsize=11)
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.legend()
    
    out_img = filename.replace('.txt', '_plot.png')
    plt.savefig(out_img, dpi=300)
    plt.show()

def plot_huffman(filename):
    n_vals, time_naive, time_pq = [], [], []
    with open(filename, 'r') as f:
        f.readline()
        for line in f:
            parts = line.strip().split()
            if len(parts) == 3:
                n_vals.append(int(parts[0]))
                time_naive.append(float(parts[1]))
                time_pq.append(float(parts[2]))

    plt.figure(figsize=(10, 6))
    plt.plot(n_vals, time_naive, color='darkorange', marker='s', linewidth=2, label='O(N²) Naive Vector Scan')
    plt.plot(n_vals, time_pq, color='teal', marker='o', linewidth=2.5, label='O(N log N) Priority Queue')
    
    plt.title("Huffman Greedy Choice Optimization: Data Structure Performance Divergence", fontsize=13, fontweight='bold')
    plt.xlabel("Number of Input Leaf Nodes (N)", fontsize=11)
    plt.ylabel("Execution Runtime Duration (Seconds)", fontsize=11)
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.legend()
    
    out_img = filename.replace('.txt', '_plot.png')
    plt.savefig(out_img, dpi=300)
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python plotter.py <filename.txt>")
        sys.exit(1)
    
    target_file = sys.argv[1]
    if "queue" in target_file.lower():
        plot_queue(target_file)
    elif "huffman" in target_file.lower():
        plot_huffman(target_file)
    else:
        print("Error: Name must contain 'queue' or 'huffman'")