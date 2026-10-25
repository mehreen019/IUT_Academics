"""
Plotter for Group 3: Bipartite Maximum Matching (Kuhn's Algorithm) benchmark.

Usage:
    python3 plotter_group3.py data_matching.txt

Produces:
    matching_runtime.png - Kuhn's algorithm runtime growth curve
"""

import sys
import matplotlib.pyplot as plt


def load_data(path):
    rows = []
    with open(path) as f:
        header = f.readline()
        for line in f:
            n, density, time_ms, matching_size = line.split()
            rows.append((int(n), float(density), float(time_ms), int(matching_size)))
    return rows


def plot_runtime(rows, out_path="matching_runtime.png"):
    densities = sorted(set(r[1] for r in rows))
    colors = ['#1F4E79', '#833C00']

    plt.figure(figsize=(7, 5))
    for density, color in zip(densities, colors):
        subset = sorted([r for r in rows if r[1] == density], key=lambda r: r[0])
        ns = [r[0] for r in subset]
        times = [r[2] for r in subset]
        plt.plot(ns, times, marker='o', label=f'density={density}', color=color)

    plt.title("Kuhn's Algorithm Runtime (Bipartite Matching)")
    plt.xlabel("n (|Left| = |Right|)")
    plt.ylabel("Time (ms)")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    print(f"Saved {out_path}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 plotter_group3.py data_matching.txt")
        sys.exit(1)

    rows = load_data(sys.argv[1])
    plot_runtime(rows)
