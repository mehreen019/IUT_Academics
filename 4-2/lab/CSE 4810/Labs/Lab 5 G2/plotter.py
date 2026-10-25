import sys
import os
import matplotlib.pyplot as plt


def read_table(path):
    """Read a whitespace-delimited text file with a header row.
    Returns (header: list[str], rows: list[list[str]])."""
    with open(path, "r") as f:
        lines = [ln.strip() for ln in f if ln.strip()]
    header = lines[0].split()
    rows = [ln.split() for ln in lines[1:]]
    return header, rows


def to_float_or_nan(x):
    try:
        return float(x)
    except ValueError:
        return float("nan")



# -----------------------------------------------------------------------------
# Task 1: Knapsack
# Columns: n W bytes_2D bytes_1D time_1D_ms   (single data row)
# -----------------------------------------------------------------------------
def plot_knapsack(path):
    header, rows = read_table(path)
    r = rows[0]
    n, W = int(r[0]), int(r[1])
    bytes_2D = float(r[2])
    bytes_1D = float(r[3])
    time_1D = float(r[4])
    time_2D = float(r[5])
 

    fig, axes = plt.subplots(1, 2, figsize=(10, 5))

    # Memory comparison (log scale, since 2D dwarfs 1D)
    ax = axes[0]
    bars = ax.bar(["2D Table", "1D Array"],
                   [bytes_2D, bytes_1D],
                   color=["#8C1C24", "#375623"])
    ax.set_yscale("log")
    ax.set_ylabel("Bytes allocated (log scale)")
    ax.set_title(f"Memory Footprint (n={n}, W={W})")
    for b, val in zip(bars, [bytes_2D, bytes_1D]):
        ax.text(b.get_x() + b.get_width() / 2, b.get_height(),
                f"{val:,.0f} B", ha="center", va="bottom", fontsize=8)

    # Time for the 1D version (2D often can't even run at this scale)
    ax = axes[1]
    ax.bar(["1D Array", "2D Array"], [time_1D, time_2D], color=["#8C1C24", "#375623"])
    ax.set_ylabel("Execution time (ms)")
    ax.set_title("1D Knapsack Runtime")

    fig.suptitle("Task 2: 0-1 Knapsack -- 2D Table vs. Space-Optimized 1D Array")
    fig.tight_layout()

    out = "knapsack_plot.png"
    fig.savefig(out, dpi=150)
    print(f"Saved: {out}")
    print("Use the memory bars to justify why the 2D table risks an OOM fault "
          "at this n and W while the 1D array does not.")
    plt.show()

# -----------------------------------------------------------------------------
# Dispatcher
# -----------------------------------------------------------------------------
DISPATCH = {
    "data_knapsack.txt": plot_knapsack,
}


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 plotter.py <data_file.txt>")
        sys.exit(1)

    path = sys.argv[1]
    if not os.path.exists(path):
        print(f"Error: file not found: {path}")
        sys.exit(1)

    filename = os.path.basename(path)
    handler = DISPATCH.get(filename)

    if handler is None:
        print(f"Error: unrecognized data file '{filename}'.")
        print(f"Expected one of: {', '.join(DISPATCH.keys())}")
        sys.exit(1)

    handler(path)


if __name__ == "__main__":
    main()