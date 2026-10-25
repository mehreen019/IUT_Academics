
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
# Task: OBST
# Columns: n time_standard_ms time_knuth_ms rb_comparisons obst_comparisons
# -----------------------------------------------------------------------------
def plot_obst(path):
    """
    data_obst.txt now has several rows:
      - one row per experimentation size (n=50,100,150,...) with
        time_naive_ms / time_optimized_ms filled and comparisons as "NA"
      - a final row with comparisons filled and times as "NA"
    """
    header, rows = read_table(path)

    timing_rows = [r for r in rows if r[1] != "NA"]
    cmp_rows = [r for r in rows if r[3] != "NA"]

    n_vals = [int(r[0]) for r in timing_rows]
    t_naive = [float(r[1]) for r in timing_rows]
    t_opt = [float(r[2]) for r in timing_rows]

    fig, axes = plt.subplots(1, 2, figsize=(10, 5))

    ax = axes[0]
    ax.plot(n_vals, t_naive, "o-", color="#8C1C24", label="Naive (recomputes freq_sum)")
    ax.plot(n_vals, t_opt, "s-", color="#4B0082", label="Optimized (prefix-sum lookup)")
    ax.set_yscale("log")
    ax.set_xlabel("Number of keys n")
    ax.set_ylabel("Build time (ms, log scale)")
    ax.set_title("OBST Build Time: O(n^4) vs. O(n^3)")
    ax.legend()
    ax.grid(True, which="both", linestyle="--", alpha=0.4)

    ax = axes[1]
    if cmp_rows:
        r = cmp_rows[-1]
        rb_cmp = float(r[3])
        obst_cmp = float(r[4])
        bars = ax.bar(["Red-Black Tree", "OBST"], [rb_cmp, obst_cmp],
                       color=["#2E75B6", "#375623"])
        ax.set_ylabel("Total comparisons (100,000 lookups)")
        ax.set_title(f"Lookup Cost Under Skewed Access (n={int(r[0])})")
        for b, val in zip(bars, [rb_cmp, obst_cmp]):
            ax.text(b.get_x() + b.get_width() / 2, b.get_height(),
                    f"{val:,.0f}", ha="center", va="bottom", fontsize=8)
    else:
        ax.text(0.5, 0.5, "No comparison data found", ha="center", va="center")
        ax.axis("off")

    fig.suptitle("Task 4: Optimal BST -- Build Cost and Lookup Cost")
    fig.tight_layout()

    out = "obst_plot.png"
    fig.savefig(out, dpi=150)
    print(f"Saved: {out}")
    print("Left: watch the naive/optimized gap widen as n grows -- that widening "
          "ratio (not just a constant speedup) is the O(n^4) vs O(n^3) signature. "
          "Right: use the comparison-count bars to argue why a static, skewed OBST "
          "beats a balanced tree when access frequencies are unequal.")
    plt.show()

# -----------------------------------------------------------------------------
# Dispatcher
# -----------------------------------------------------------------------------
DISPATCH = {
    "data_obst.txt": plot_obst,
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
