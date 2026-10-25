"""
Plotter for Group 1: Prim's Algorithm (naive vs heap) and Max-Flow benchmarks.

Usage:
    python3 plotter_group1.py data_prim.txt data_maxflow.txt

Produces:
    prim_runtime.png     - naive vs heap runtime curves, split by density
    maxflow_runtime.png  - Edmonds-Karp runtime growth curve
"""

import sys
import matplotlib.pyplot as plt


def load_prim_data(path):
    rows = []
    with open(path) as f:
        header = f.readline()
        for line in f:
            n, density, naive_ms, heap_ms = line.split()
            rows.append((int(n), float(density), float(naive_ms), float(heap_ms)))
    return rows


def load_maxflow_data(path):
    rows = []
    with open(path) as f:
        header = f.readline()
        for line in f:
            n, density, time_ms, flow = line.split()
            rows.append((int(n), float(density), float(time_ms), float(flow)))
    return rows


def plot_prim(rows, out_path="prim_runtime.png"):
    densities = sorted(set(r[1] for r in rows))
    fig, axes = plt.subplots(1, len(densities), figsize=(6 * len(densities), 5))
    if len(densities) == 1:
        axes = [axes]

    for ax, density in zip(axes, densities):
        subset = sorted([r for r in rows if r[1] == density], key=lambda r: r[0])
        ns = [r[0] for r in subset]
        naive = [r[2] for r in subset]
        heap = [r[3] for r in subset]

        ax.plot(ns, naive, marker='o', label='prim_naive (O(V^2))', color='#833C00')
        ax.plot(ns, heap, marker='s', label='prim_heap (O(E log V))', color='#1F4E79')
        ax.set_title(f"Prim's Runtime -- density={density}")
        ax.set_xlabel("Number of vertices (n)")
        ax.set_ylabel("Time (ms)")
        ax.legend()
        ax.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    print(f"Saved {out_path}")


def plot_maxflow(rows, out_path="maxflow_runtime.png"):
    densities = sorted(set(r[1] for r in rows))
    plt.figure(figsize=(7, 5))
    colors = ['#1F4E79', '#833C00']

    for density, color in zip(densities, colors):
        subset = sorted([r for r in rows if r[1] == density], key=lambda r: r[0])
        ns = [r[0] for r in subset]
        times = [r[2] for r in subset]
        plt.plot(ns, times, marker='o', label=f'density={density}', color=color)

    plt.title("Edmonds-Karp Max-Flow Runtime")
    plt.xlabel("Number of vertices (n)")
    plt.ylabel("Time (ms)")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    print(f"Saved {out_path}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 plotter_group1.py data_prim.txt data_maxflow.txt")
        sys.exit(1)

    prim_rows = load_prim_data(sys.argv[1])
    maxflow_rows = load_maxflow_data(sys.argv[2])

    plot_prim(prim_rows)
    plot_maxflow(maxflow_rows)
