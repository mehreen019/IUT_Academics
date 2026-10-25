"""
Plotter for Group 4: Project Selection Problem (Open-Pit Mining) benchmark.

Usage:
    python3 plotter_group4.py data_mining.txt

Produces:
    mining_runtime.png - Max-Flow-based project selection runtime growth curve
"""

import sys
import matplotlib.pyplot as plt


def load_data(path):
    rows = []
    with open(path) as f:
        header = f.readline()
        for line in f:
            numBlocks, time_ms, net_profit = line.split()
            rows.append((int(numBlocks), float(time_ms), int(net_profit)))
    return rows


def plot_runtime(rows, out_path="mining_runtime.png"):
    rows = sorted(rows, key=lambda r: r[0])
    ns = [r[0] for r in rows]
    times = [r[1] for r in rows]

    plt.figure(figsize=(7, 5))
    plt.plot(ns, times, marker='o', color='#5B2A86')
    plt.title("Project Selection Runtime (Max-Flow Min-Cut)")
    plt.xlabel("Number of blocks")
    plt.ylabel("Time (ms)")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    print(f"Saved {out_path}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 plotter_group4.py data_mining.txt")
        sys.exit(1)

    rows = load_data(sys.argv[1])
    plot_runtime(rows)
