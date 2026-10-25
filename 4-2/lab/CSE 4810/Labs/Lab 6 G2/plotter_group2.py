"""
Plotter for Group 2: Kruskal's Algorithm and Min-Cut benchmarks.

Usage:
    python3 plotter_group2.py data_kruskal.txt data_mincut.txt

Produces:
    kruskal_runtime.png  - Kruskal's (DSU-based) runtime growth curve
    mincut_runtime.png   - Min-Cut (max-flow engine) runtime growth curve
"""

import sys
import matplotlib.pyplot as plt


def load_data(path):
    rows = []
    with open(path) as f:
        header = f.readline()
        for line in f:
            n, density, time_ms = line.split()
            rows.append((int(n), float(density), float(time_ms)))
    return rows


def plot_runtime(rows, title, out_path, color_a='#375623', color_b='#8C1C24'):
    densities = sorted(set(r[1] for r in rows))
    colors = [color_a, color_b]

    plt.figure(figsize=(7, 5))
    for density, color in zip(densities, colors):
        subset = sorted([r for r in rows if r[1] == density], key=lambda r: r[0])
        ns = [r[0] for r in subset]
        times = [r[2] for r in subset]
        plt.plot(ns, times, marker='o', label=f'density={density}', color=color)

    plt.title(title)
    plt.xlabel("Number of vertices (n)")
    plt.ylabel("Time (ms)")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    print(f"Saved {out_path}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 plotter_group2.py data_kruskal.txt data_mincut.txt")
        sys.exit(1)

    kruskal_rows = load_data(sys.argv[1])
    mincut_rows = load_data(sys.argv[2])

    plot_runtime(kruskal_rows, "Kruskal's MST Runtime (Union-Find)", "kruskal_runtime.png")
    plot_runtime(mincut_rows, "Min-Cut Runtime (Max-Flow Engine)", "mincut_runtime.png")
