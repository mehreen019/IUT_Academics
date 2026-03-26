"""
BinPackingProblem.py
--------------------
Owns the data model for the Bin Packing Problem:
  - item list (weights)
  - bin list (each bin = list of item indices)
  - capacity checks
  - objective evaluator

All mutation helpers return *new* state so LocalSearch can compare
candidates without corrupting the incumbent.
"""

import random
import math
from typing import List, Tuple


class BinPackingProblem:
    """
    Represents one complete solution to the bin-packing problem.

    Attributes
    ----------
    weights   : list[int]  – weight of each item (index = item id)
    capacity  : int        – maximum load per bin
    bins      : list[list[int]]  – bins[b] = list of item indices in bin b
    """

    # ------------------------------------------------------------------ #
    #  Construction                                                        #
    # ------------------------------------------------------------------ #

    def __init__(self, weights: List[int], capacity: int):
        self.weights: List[int] = weights          # immutable item data
        self.capacity: int = capacity
        self.bins: List[List[int]] = []            # mutable solution state

    # ------------------------------------------------------------------ #
    #  Class-level factory helpers                                        #
    # ------------------------------------------------------------------ #

    @classmethod
    def generate_random_instance(cls, n: int = 20,
                                 weight_lo: int = 5,
                                 weight_hi: int = 40,
                                 capacity: int = 100,
                                 seed: int = None) -> "BinPackingProblem":
        """Create a problem instance with *n* items of random weights."""
        if seed is not None:
            random.seed(seed)
        weights = [random.randint(weight_lo, weight_hi) for _ in range(n)]
        return cls(weights, capacity)

    # ------------------------------------------------------------------ #
    #  Initialisation strategies                                          #
    # ------------------------------------------------------------------ #

    def initialize_random(self) -> None:
        """
        Randomly assign each item to a random existing bin, opening a new
        bin whenever the chosen bin would exceed capacity.  Guarantees a
        feasible starting solution.
        """
        n = len(self.weights)
        order = list(range(n))
        random.shuffle(order)

        self.bins = []
        for item in order:
            # collect bins that can still accommodate this item
            feasible = [b for b, items in enumerate(self.bins)
                        if self.bin_load(b) + self.weights[item] <= self.capacity]
            if feasible:
                chosen = random.choice(feasible)
                self.bins[chosen].append(item)
            else:
                self.bins.append([item])

    def initialize_ffд(self, permutation: List[int] = None) -> None:
        """
        First-Fit Decreasing initialisation.

        Parameters
        ----------
        permutation : optional pre-sorted order of item indices.
                      If None, items are sorted by weight descending.
        """
        if permutation is None:
            order = sorted(range(len(self.weights)),
                           key=lambda i: self.weights[i], reverse=True)
        else:
            order = permutation

        self.bins = []
        for item in order:
            placed = False
            for b in range(len(self.bins)):
                if self.bin_load(b) + self.weights[item] <= self.capacity:
                    self.bins[b].append(item)
                    placed = True
                    break
            if not placed:
                self.bins.append([item])

    def initialize_ffd_random_permutation(self) -> None:
        """
        Restart helper: shuffle items randomly *then* apply First-Fit
        Decreasing on that shuffled order (items within the shuffled prefix
        are still packed largest-first relative to each other after sorting
        the full list by weight descending, but the key randomness comes
        from starting with a fresh random seed passed to the sort).
        Actually: shuffle → sort descending → FFD, giving a fresh FFD
        solution.
        """
        indices = list(range(len(self.weights)))
        random.shuffle(indices)
        # sort by weight descending to get FFD behaviour
        indices.sort(key=lambda i: self.weights[i], reverse=True)
        self.initialize_ffд(permutation=indices)

    # ------------------------------------------------------------------ #
    #  Bin-level queries (public)                                         #
    # ------------------------------------------------------------------ #

    def bin_load(self, b: int) -> int:
        """Total weight of items currently in bin *b*."""
        return sum(self.weights[i] for i in self.bins[b])

    def all_loads(self) -> List[int]:
        """Return the load of every bin."""
        return [self.bin_load(b) for b in range(len(self.bins))]

    def is_feasible(self) -> bool:
        """Check that every bin respects capacity and every item appears exactly once."""
        seen = []
        for b, items in enumerate(self.bins):
            if self.bin_load(b) > self.capacity:
                return False
            seen.extend(items)
        return sorted(seen) == list(range(len(self.weights)))

    # ------------------------------------------------------------------ #
    #  Objective function (public)                                        #
    # ------------------------------------------------------------------ #

    def objective(self) -> float:
        """
        Primary:   number of bins used  (minimise)
        Secondary: small balance term   (minimise standard deviation of
                   fill levels, scaled so it never dominates the primary)

        objective = num_bins + 1e-4 * std_dev(loads)
        """
        loads = self.all_loads()
        k = len(loads)
        if k == 0:
            return 0.0
        mean = sum(loads) / k
        variance = sum((l - mean) ** 2 for l in loads) / k
        std = math.sqrt(variance)
        return k + 1e-4 * std

    def num_bins(self) -> int:
        """Return the raw integer bin count (used for convergence checks)."""
        return len(self.bins)

    # ------------------------------------------------------------------ #
    #  Destroy helpers (public)                                           #
    # ------------------------------------------------------------------ #

    def least_filled_bin_indices(self, k: int = 1) -> List[int]:
        """
        Return the indices of the *k* least-filled bins, sorted by load
        ascending (so index 0 is the emptiest).
        """
        if not self.bins:
            return []
        indexed_loads = [(b, self.bin_load(b)) for b in range(len(self.bins))]
        indexed_loads.sort(key=lambda x: x[1])
        return [b for b, _ in indexed_loads[:k]]

    def remove_bins(self, bin_indices: List[int]) -> List[int]:
        """
        Remove the bins at *bin_indices* from the solution and return the
        list of displaced item indices.  Bin indices are interpreted
        *before* any removal (largest-first removal to keep indices valid).
        """
        displaced: List[int] = []
        for b in sorted(bin_indices, reverse=True):
            displaced.extend(self.bins[b])
            del self.bins[b]
        return displaced

    # ------------------------------------------------------------------ #
    #  Repair helpers (public)                                            #
    # ------------------------------------------------------------------ #

    def first_fit_insert(self, items: List[int]) -> None:
        """
        Insert each item in *items* using First-Fit: place it in the first
        existing bin where it fits, otherwise open a new bin.
        """
        for item in items:
            placed = False
            for b in range(len(self.bins)):
                if self.bin_load(b) + self.weights[item] <= self.capacity:
                    self.bins[b].append(item)
                    placed = True
                    break
            if not placed:
                self.bins.append([item])

    # ------------------------------------------------------------------ #
    #  State copy (public)                                                #
    # ------------------------------------------------------------------ #

    def copy_bins(self) -> List[List[int]]:
        """Return a deep copy of the current bin assignment."""
        return [list(b) for b in self.bins]

    def restore_bins(self, saved: List[List[int]]) -> None:
        """Restore bins from a previously saved copy."""
        self.bins = [list(b) for b in saved]

    # ------------------------------------------------------------------ #
    #  Pretty-print                                                       #
    # ------------------------------------------------------------------ #

    def __str__(self) -> str:
        lines = [f"BinPackingProblem  |  {len(self.weights)} items  |  "
                 f"capacity={self.capacity}  |  bins used={self.num_bins()}"]
        for b, items in enumerate(self.bins):
            load = self.bin_load(b)
            fill_pct = 100 * load / self.capacity
            lines.append(f"  Bin {b:>2}: items={items}  "
                         f"load={load}/{self.capacity} ({fill_pct:.1f}%)")
        return "\n".join(lines)
