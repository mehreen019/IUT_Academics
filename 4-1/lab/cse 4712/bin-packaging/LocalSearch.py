"""
LocalSearch.py
--------------
Implements the Iterated Destroy-and-Repair local search for Bin Packing.

Only calls *public* methods of BinPackingProblem.

Escape mechanisms (applied in order when stuck):
  1. Random restart   – after RESTART_PATIENCE iterations without improvement
                        re-initialise with a fresh FFD on a random permutation.
  2. Wider neighbourhood – after WIDEN_AFTER_RESTARTS restarts, increase the
                        number of bins destroyed per step.
  3. Bad-move window  – temporarily accept solutions with (best + 1) bins for
                        up to BAD_MOVE_LIMIT consecutive iterations.
"""

import random
from typing import List
from BinPackingProblem import BinPackingProblem


# ──────────────────────────────────────────────────────────────────────────────
#  Hyper-parameters
# ──────────────────────────────────────────────────────────────────────────────

MAX_ITERATIONS      = 2_000   # hard stop
RESTART_PATIENCE    = 120     # iterations without improvement → restart
WIDEN_AFTER_RESTARTS = 3      # restarts before neighbourhood widening
BAD_MOVE_LIMIT      = 40      # consecutive bad-move accepts allowed

# Neighbourhood sizes (bins destroyed per step)
#   phase 0  (standard)              : single=1, multi=2
#   phase 1  (after widening kicks in): single=3, multi=5
DESTROY_SIZES = {
    "standard": {"single": 1, "multi": 2},
    "wide":     {"single": 3, "multi": 5},
}


class LocalSearch:
    """
    Iterated Destroy-and-Repair search for Bin Packing.

    Parameters
    ----------
    problem  : BinPackingProblem  – already initialised (bins populated)
    use_multi_operator : bool     – if True, the multi-bin destroy variant
                                    is used throughout
    verbose  : bool               – print progress to stdout
    """

    def __init__(self,
                 problem: BinPackingProblem,
                 use_multi_operator: bool = False,
                 verbose: bool = True):
        self.prob               = problem
        self.use_multi          = use_multi_operator
        self.verbose            = verbose

        # ── restart bookkeeping ──────────────────────────────────────────
        self._no_improve_count: int = 0   # iterations since last improvement
        self._restart_count:    int = 0   # total restarts so far

        # ── neighbourhood scale ──────────────────────────────────────────
        # "standard" until WIDEN_AFTER_RESTARTS restarts have occurred
        self._neighbourhood_phase: str = "standard"

        # ── bad-move window ──────────────────────────────────────────────
        self._bad_move_active:  bool = False
        self._bad_move_steps:   int  = 0   # consecutive bad-move iters used

        # ── best solution memory ─────────────────────────────────────────
        self._best_bins:       List[List[int]] = self.prob.copy_bins()
        self._best_score:      float           = self.prob.objective()
        self._best_k:          int             = self.prob.num_bins()
        self._best_found_at:   int             = 0
        self._bad_moves_this_restart: int      = 0
        self._max_bad_moves:          int      = 0

    # ──────────────────────────────────────────────────────────────────────
    #  Public entry point
    # ──────────────────────────────────────────────────────────────────────

    def run(self, max_iterations: int = MAX_ITERATIONS) -> BinPackingProblem:
        """
        Execute the search for up to *max_iterations* steps.

        Returns the problem object in its best-found state.
        """
        mode = "multi-op" if self.use_multi else "single-op"
        self._log(f"[START]  mode={mode}  initial_bins={self._best_k}  obj={self._best_score:.6f}")

        for iteration in range(1, max_iterations + 1):

            # ── 1. Save current state ────────────────────────────────────
            saved = self.prob.copy_bins()

            # ── 2. Select destroy width ──────────────────────────────────
            n_destroy = self._select_destroy_count()

            # ── 3. Destroy ───────────────────────────────────────────────
            target_bins = self.prob.least_filled_bin_indices(n_destroy)
            displaced   = self.prob.remove_bins(target_bins)

            # ── 4. Repair ────────────────────────────────────────────────
            self.prob.first_fit_insert(displaced)

            # ── 5. Evaluate candidate ────────────────────────────────────
            cand_score = self.prob.objective()
            cand_k     = self.prob.num_bins()

            # ── 6. Acceptance logic ──────────────────────────────────────
            accepted, accept_reason = self._accept(cand_score, cand_k, saved)

            if not accepted:
                self.prob.restore_bins(saved)

            # ── 7. Update global best ────────────────────────────────────
            improved = self._update_best(iteration)

            # ── 8. Update counters & log only new bests ──────────────────
            if improved:
                self._no_improve_count       = 0
                self._bad_move_active        = False
                self._bad_move_steps         = 0
                self._log(f"[BEST]   iter={iteration}  bins={self._best_k}  obj={self._best_score:.6f}")
            else:
                self._no_improve_count += 1

            # ── 9. Escape mechanisms ─────────────────────────────────────
            self._try_restart(iteration)
            self._try_activate_bad_move()

            # ── 10. Early exit ───────────────────────────────────────────
            if self._best_k == 1:
                self._log(f"[DONE]   optimal (1 bin) reached at iter={iteration}")
                break

        # Restore best found solution before returning
        self.prob.restore_bins(self._best_bins)
        self._log("")
        self._log("Summary " + "-" * 34)
        self._log(f"Restarts         : {self._restart_count}")
        self._log(f"Bad moves used   : {self._max_bad_moves}")
        self._log(f"Best found at    : iter {self._best_found_at}")
        self._log(f"Best bins        : {self._best_k}")
        return self.prob

    # ──────────────────────────────────────────────────────────────────────
    #  Destroy width selector  (private)
    # ──────────────────────────────────────────────────────────────────────

    def _select_destroy_count(self) -> int:
        """
        Return how many bins to destroy this iteration based on the
        current neighbourhood phase and whether multi-operator mode is on.
        """
        phase = DESTROY_SIZES[self._neighbourhood_phase]
        key   = "multi" if self.use_multi else "single"
        raw   = phase[key]
        # never destroy more bins than currently exist
        return min(raw, max(1, self.prob.num_bins() - 1))

    # ──────────────────────────────────────────────────────────────────────
    #  Acceptance logic  (private)
    # ──────────────────────────────────────────────────────────────────────

    def _accept(self,
                cand_score: float,
                cand_k:     int,
                saved_bins: List[List[int]]):
        """
        Decide whether to accept the candidate solution.
        Returns (accepted: bool, reason: str).

        Normal acceptance  : strictly better objective  → reason "improvement"
        Bad-move window    : cand_k <= best_k + 1       → reason "bad_move"
        Rejected                                         → reason "rejected"
        """
        # Standard improvement
        if cand_score < self._best_score:
            return True, "improvement"

        # Bad-move window (Escape #3) — step counting is done per-iteration
        # in _try_activate_bad_move, not here
        if self._bad_move_active and cand_k <= self._best_k + 1:
            self._bad_moves_this_restart += 1
            return True, "bad_move"

        return False, "rejected"

    # ──────────────────────────────────────────────────────────────────────
    #  Best-solution tracker  (private)
    # ──────────────────────────────────────────────────────────────────────

    def _update_best(self, iteration: int = 0) -> bool:
        """
        Compare current solution to the recorded best.
        If better, save it and return True; otherwise return False.
        """
        score = self.prob.objective()
        k     = self.prob.num_bins()
        if score < self._best_score:
            self._best_score    = score
            self._best_k        = k
            self._best_bins     = self.prob.copy_bins()
            self._best_found_at = iteration
            return True
        return False

    # ──────────────────────────────────────────────────────────────────────
    #  Escape #1 & #2 – restart logic  (private)
    # ──────────────────────────────────────────────────────────────────────

    def _try_restart(self, iteration: int) -> None:
        """
        Escape #1 – Random restart after RESTART_PATIENCE idle iterations.
        Escape #2 – After WIDEN_AFTER_RESTARTS restarts, switch neighbourhood.
        """
        if self._no_improve_count < RESTART_PATIENCE:
            return

        self._restart_count          += 1
        self._no_improve_count        = 0
        self._bad_move_active         = False
        self._bad_move_steps          = 0
        if self._bad_moves_this_restart > self._max_bad_moves:
            self._max_bad_moves = self._bad_moves_this_restart
        self._bad_moves_this_restart  = 0

        # Escape #2 – widen neighbourhood once enough restarts have occurred
        if (self._restart_count >= WIDEN_AFTER_RESTARTS
                and self._neighbourhood_phase == "standard"):
            self._neighbourhood_phase = "wide"
            self._log(f"[WIDEN]  neighbourhood expanded to WIDE phase after restart #{self._restart_count}")

        # Perform fresh FFD initialisation on a random permutation
        self.prob.initialize_ffd_random_permutation()

        new_score = self.prob.objective()
        new_k     = self.prob.num_bins()
        self._log(
            f"[RESTART #{self._restart_count}]  iter={iteration}  new_k={new_k}  no_improve_streak_reset"
        )

        # If the restart already beats our best, record it
        self._update_best(iteration)

    # ──────────────────────────────────────────────────────────────────────
    #  Escape #3 – bad-move activation  (private)
    # ──────────────────────────────────────────────────────────────────────

    def _try_activate_bad_move(self) -> None:
        """
        Escape #3 - Bad-move window.
        Only activates after at least one restart (spec order: restarts first).
        Window stays open for exactly BAD_MOVE_LIMIT consecutive iterations
        (not accepted moves), then closes. Resets on every restart.
        """
        # Spec says bad moves come after restarts - never before first restart
        if self._restart_count == 0:
            return

        if self._bad_move_active:
            # Tick the iteration counter regardless of whether move was accepted
            self._bad_move_steps += 1
            if self._bad_move_steps >= BAD_MOVE_LIMIT:
                self._bad_move_active = False
                self._log(f"[BADMOV] window closed  (40 iterations elapsed)")
        elif self._no_improve_count == RESTART_PATIENCE // 2:
            # Open once per no-improve cycle: halfway to the next restart
            self._bad_move_active = True
            self._bad_move_steps  = 0
            self._log(f"[BADMOV] window opened  no_improve={self._no_improve_count}  budget={BAD_MOVE_LIMIT}")

      # Close the window once budget is exhausted
        if self._bad_move_active and self._bad_move_steps >= BAD_MOVE_LIMIT:
            self._bad_move_active = False
            self._log(f"[BADMOV] window closed  (budget exhausted)")

    # ──────────────────────────────────────────────────────────────────────
    #  Logging helper  (private)
    # ──────────────────────────────────────────────────────────────────────

    def _log(self, msg: str, force: bool = False) -> None:
        if self.verbose or force:
            print(msg)


# ──────────────────────────────────────────────────────────────────────────────
#  Demo / entry-point
# ──────────────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    import time

    print("=" * 65)
    print("  BIN PACKING  –  Iterated Destroy-and-Repair Local Search")
    print("=" * 65)

    # ── Create problem instance ──────────────────────────────────────────
    prob = BinPackingProblem.generate_random_instance(
        n=20, weight_lo=5, weight_hi=40, capacity=100, seed=22
    )
    print(f"\nItem weights : {prob.weights}")
    print(f"Bin capacity : {prob.capacity}\n")

    # ── Run single-operator variant ──────────────────────────────────────
    prob.initialize_random()
    print(f"Initial solution (random): {prob.num_bins()} bins")
    print(prob)
    print()

    t0 = time.perf_counter()
    ls = LocalSearch(prob, use_multi_operator=False, verbose=True)
    ls.run(max_iterations=2_000)
    elapsed_single = time.perf_counter() - t0

    print("\n── Single-operator final bins ──")
    print(prob)
    print(f"Time: {elapsed_single:.3f}s")
    assert prob.is_feasible(), "INFEASIBLE SOLUTION!"
    print("Feasibility check: PASSED\n")

    # ── Run multi-operator variant ───────────────────────────────────────
    prob2 = BinPackingProblem.generate_random_instance(
        n=20, weight_lo=5, weight_hi=40, capacity=100, seed=22
    )
    prob2.initialize_random()

    t0 = time.perf_counter()
    ls2 = LocalSearch(prob2, use_multi_operator=True, verbose=True)
    ls2.run(max_iterations=2_000)
    elapsed_multi = time.perf_counter() - t0

    print("\n── Multi-operator final bins ──")
    print(prob2)
    print(f"Time: {elapsed_multi:.3f}s")
    assert prob2.is_feasible(), "INFEASIBLE SOLUTION!"
    print("Feasibility check: PASSED\n")

    # ── Summary ──────────────────────────────────────────────────────────
    print("=" * 65)
    print(f"  Single-op  → {prob.num_bins()} bins  ({elapsed_single:.3f}s)")
    print(f"  Multi-op   → {prob2.num_bins()} bins  ({elapsed_multi:.3f}s)")
    print("=" * 65)