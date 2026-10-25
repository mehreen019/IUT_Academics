import matplotlib.pyplot as plt
import os
import sys

def plot_dynamic_table(filename):
    """Plots operation-wise actual cost (spikes) vs. the running average."""
    op_indices = []
    actual_costs = []
    running_averages = []

    with open(filename, 'r') as f:
        # Skip header
        f.readline()
        for line in f:
            parts = line.strip().split()
            if len(parts) == 3:
                op_indices.append(int(parts[0]))
                actual_costs.append(float(parts[1]))
                running_averages.append(float(parts[2]))

    plt.figure(figsize=(12, 6))
    
    # Plot individual operation costs as vertical bars to represent spikes clearly
    plt.bar(op_indices, actual_costs, color='dodgerblue', alpha=0.6, width=1.0, label='Actual Cost (Spikes)')
    
    # Overlay the cumulative running average as a thick trend line
    plt.plot(op_indices, running_averages, color='crimson', linewidth=2.5, label='Running Average Cost')

    plt.title("Dynamic Table Expansion: Latency Spikes vs. Amortized Average", fontsize=14, fontweight='bold')
    plt.xlabel("Operation Index (N)", fontsize=12)
    plt.ylabel("Operation Cost (Units of Work)", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.legend(loc='upper right', fontsize=11)
    plt.tight_layout()
    
    output_png = filename.replace('.txt', '_plot.png')
    plt.savefig(output_png, dpi=300)
    print(f"Successfully generated plot: {output_png}")
    plt.show()


def plot_coin_change(filename):
    """Plots and contrasts Standard Greedy vs Remainder-Aware Greedy across currencies."""
    values = []
    std_canonical = []
    rem_canonical = []
    std_noncanonical = []
    rem_noncanonical = []

    with open(filename, 'r') as f:
        # Skip header
        f.readline()
        for line in f:
            parts = line.strip().split()
            if len(parts) == 5:
                values.append(int(parts[0]))
                std_canonical.append(int(parts[1]))
                rem_canonical.append(int(parts[2]))
                std_noncanonical.append(int(parts[3]))
                rem_noncanonical.append(int(parts[4]))

    # Create side-by-side subplots to cleanly compare canonical vs non-canonical properties
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

    # Left Subplot: Canonical System
    ax1.plot(values, std_canonical, color='green', linewidth=2, label='Standard Greedy')
    ax1.plot(values, rem_canonical, color='orange', linestyle='--', linewidth=2, label='Remainder-Aware Greedy')
    ax1.set_title("Canonical System {1, 5, 10, 25}\n(Heuristics Converge Perfectly)", fontsize=12, fontweight='bold')
    ax1.set_xlabel("Target Value (V)", fontsize=11)
    ax1.set_ylabel("Number of Coins Used", fontsize=11)
    ax1.grid(True, linestyle='--', alpha=0.5)
    ax1.legend()

    # Right Subplot: Non-Canonical System
    ax2.plot(values, std_noncanonical, color='crimson', linewidth=2, label='Standard Greedy')
    ax2.plot(values, rem_noncanonical, color='darkviolet', linestyle='--', linewidth=2, label='Remainder-Aware Greedy')
    ax2.set_title("Non-Canonical System {1, 4, 5, 15, 20}\n(Heuristics Diverge / Fail)", fontsize=12, fontweight='bold')
    ax2.set_xlabel("Target Value (V)", fontsize=11)
    ax2.set_ylabel("Number of Coins Used", fontsize=11)
    ax2.grid(True, linestyle='--', alpha=0.5)
    ax2.legend()

    plt.suptitle("Greedy Choice Property Evaluation: Competing Change-Making Heuristics", fontsize=14, fontweight='bold')
    plt.tight_layout()
    
    output_png = filename.replace('.txt', '_plot.png')
    plt.savefig(output_png, dpi=300)
    print(f"Successfully generated plot: {output_png}")
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python plotter.py <filename.txt>")
        print("Examples:\n  python plotter.py data_dyntable.txt\n  python plotter.py data_coins.txt")
        sys.exit(1)

    target_file = sys.argv[1]
    if not os.path.exists(target_file):
        print(f"Error: File '{target_file}' not found.")
        sys.exit(1)

    if "dyntable" in target_file.lower():
        plot_dynamic_table(target_file)
    elif "coin" in target_file.lower():
        plot_coin_change(target_file)
    else:
        print("Error: Unknown data file format. Filename must contain 'dyntable' or 'coin'.")