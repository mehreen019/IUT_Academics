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
# Task 1: Rod Cutting
# Columns: n naive_ms memo_ms bottomup_ms   (naive_ms may be "NA" at n=40)
# -----------------------------------------------------------------------------
def plot_rodcut(path):
    header, rows = read_table(path)
    n_vals = [int(r[0]) for r in rows]
    naive = [to_float_or_nan(r[1]) for r in rows]
    memo = [to_float_or_nan(r[2]) for r in rows]
    bottom = [to_float_or_nan(r[3]) for r in rows]

    fig, ax = plt.subplots(figsize=(8, 5.5))
    ax.plot(n_vals, naive, "o-", color="#833C00", label="Naive (exponential)")
    ax.plot(n_vals, memo, "s-", color="#806000", label="Memoized (top-down)")
    ax.plot(n_vals, bottom, "^-", color="#375623", label="Bottom-Up (tabulation)")

    ax.set_yscale("log")
    ax.set_xlabel("Rod length n")
    ax.set_ylabel("Execution time (ms, log scale)")
    ax.set_title("Task 1: Rod Cutting -- Naive vs. Memoized vs. Bottom-Up")
    ax.legend()
    ax.grid(True, which="both", linestyle="--", alpha=0.4)

    out = "rodcut_plot.png"
    fig.tight_layout()
    fig.savefig(out, dpi=150)
    print(f"Saved: {out}")
    print("Look for the point where the naive curve breaks upward while the "
          "memoized/bottom-up curves stay flat -- that is the O(2^n) vs "
          "Theta(n^2) divergence.")
    plt.show()


# -----------------------------------------------------------------------------
# Dispatcher
# -----------------------------------------------------------------------------
DISPATCH = {
    "data_rodcut.txt": plot_rodcut,
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