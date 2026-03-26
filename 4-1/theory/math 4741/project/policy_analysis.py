"""
policy_analysis.py
------------------
Member 4 — Nafisa Haque (210041231)
Math 4741 Term Project: Optimal Queue Control via CTMDP

Responsibilities:
  - Extract threshold values k1, k2 from the solved optimal policy
  - Verify monotonicity of the policy
  - Generate report-quality plots of the optimal policy
  - Compare optimal policy against naive (always μ2) baseline visually

Usage (standalone demo):
  python policy_analysis.py

Usage (as module):
  from policy_analysis import PolicyAnalyzer
  analyzer = PolicyAnalyzer(policy=pi, service_rates=[mu1, mu2, mu3])
  analyzer.run_all()
"""

import numpy as np
import matplotlib
matplotlib.use('Agg')          # non-interactive backend for saving figures
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from typing import Optional


# ──────────────────────────────────────────────────────────────────────────────
# Helper: generate a simple demo policy so the file can be run standalone
# ──────────────────────────────────────────────────────────────────────────────

def _demo_policy(N: int = 50,
                 mu_rates: list = None,
                 k1: int = 4,
                 k2: int = 10) -> np.ndarray:
    """
    Returns a synthetic threshold policy for standalone testing.
    States 0..k1-1  → action index 0  (slowest rate μ1)
    States k1..k2-1 → action index 1  (medium  rate μ2)
    States k2..N-1  → action index 2  (fastest rate μ3)
    """
    if mu_rates is None:
        mu_rates = [2, 4, 6]
    policy = np.zeros(N, dtype=int)
    policy[k1:k2] = 1
    policy[k2:]   = 2
    return policy


# ──────────────────────────────────────────────────────────────────────────────
# Core class
# ──────────────────────────────────────────────────────────────────────────────

class PolicyAnalyzer:
    """
    Analyzes the structure of an optimal policy returned by solvers.py.

    Parameters
    ----------
    policy : np.ndarray, shape (N,)
        policy[n] is the *index* of the chosen action at state n.
        Index 0 → μ1 (slowest), 1 → μ2 (medium), 2 → μ3 (fastest).
    service_rates : list of float
        [μ1, μ2, μ3]  — the three available service rates.
    lam : float
        Arrival rate λ (used only for plot annotations).
    c_h : float
        Holding cost per customer (used only for plot annotations).
    c_a : list of float
        Action costs [c_a1, c_a2, c_a3] (used only for plot annotations).
    """

    def __init__(self,
                 policy: np.ndarray,
                 service_rates: list,
                 lam:   float = 3.0,
                 c_h:   float = 1.0,
                 c_a:   Optional[list] = None):

        self.policy        = np.asarray(policy, dtype=int)
        self.service_rates = service_rates
        self.N             = len(policy)
        self.lam           = lam
        self.c_h           = c_h
        self.c_a           = c_a if c_a is not None else [0, 1, 3]

        # Map action index → service rate value
        self.rate_for_state = np.array([service_rates[a] for a in policy])

        # Results filled in by analysis methods
        self.k1:  Optional[int]  = None
        self.k2:  Optional[int]  = None
        self.monotone: bool      = False
        self.violations: list    = []

    # ──────────────────────────────────────────────────────────────────────────
    # 1.  Extract thresholds
    # ──────────────────────────────────────────────────────────────────────────

    def find_thresholds(self) -> dict:
        """
        Scans the policy for the first upward transitions in action index:
          k1 = first state where the policy switches from action 0 to action 1
          k2 = first state where the policy switches from action 1 to action 2

        Returns
        -------
        dict with keys 'k1', 'k2', and descriptive messages.
        """
        k1 = k2 = None

        for n in range(self.N - 1):
            if self.policy[n] == 0 and self.policy[n + 1] >= 1:
                if k1 is None:
                    k1 = n + 1          # first state at which action ≥ 1 is used
            if self.policy[n] <= 1 and self.policy[n + 1] == 2:
                if k2 is None:
                    k2 = n + 1          # first state at which action 2 is used

        self.k1 = k1
        self.k2 = k2

        result = {
            'k1': k1,
            'k2': k2,
            'k1_desc': (f"Switch from mu1 to mu2 at queue length {k1}"
                        if k1 is not None else "mu2 never used"),
            'k2_desc': (f"Switch from mu2 to mu3 at queue length {k2}"
                        if k2 is not None else "mu3 never used"),
        }
        return result

    # ──────────────────────────────────────────────────────────────────────────
    # 2.  Verify monotonicity
    # ──────────────────────────────────────────────────────────────────────────

    def verify_monotonicity(self) -> dict:
        """
        Checks whether π(n) ≤ π(n+1) for all n in {0, …, N-2}.

        A monotone increasing policy means: the controller never chooses a
        *slower* service rate as the queue grows, which is the expected
        threshold structure proven via submodularity.

        Returns
        -------
        dict with keys 'monotone' (bool) and 'violations' (list of state indices).
        """
        violations = [n for n in range(self.N - 1)
                      if self.policy[n] > self.policy[n + 1]]
        self.monotone   = (len(violations) == 0)
        self.violations = violations
        return {'monotone': self.monotone, 'violations': violations}

    # ──────────────────────────────────────────────────────────────────────────
    # 3.  Print summary to console
    # ──────────────────────────────────────────────────────────────────────────

    def print_summary(self):
        """Prints threshold values and monotonicity check to stdout."""

        thresholds = self.find_thresholds()
        mono       = self.verify_monotonicity()

        mu1, mu2, mu3 = self.service_rates
        print("=" * 60)
        print("   THRESHOLD POLICY ANALYSIS")
        print("=" * 60)
        print(f"  Parameters : λ={self.lam}, c_h={self.c_h}, c_a={self.c_a}")
        print(f"  State space: N={self.N}")
        print(f"  Service rates: μ1={mu1}, μ2={mu2}, μ3={mu3}")
        print("-" * 60)
        print(f"  k1 = {thresholds['k1']}  :  {thresholds['k1_desc']}")
        print(f"  k2 = {thresholds['k2']}  :  {thresholds['k2_desc']}")
        print("-" * 60)
        if mono['monotone']:
            print("  ✓  Policy is MONOTONE NON-DECREASING  (no violations)")
        else:
            print(f"  ✗  Monotonicity VIOLATED at states: {mono['violations']}")
        print("=" * 60)

    # ──────────────────────────────────────────────────────────────────────────
    # 4.  Plot 1 — optimal policy as a step function
    # ──────────────────────────────────────────────────────────────────────────

    def plot_policy(self, save_path: str = "policy_plot.png") -> plt.Figure:
        """
        Plots π*(n) (chosen service rate) as a step function of queue length n.
        Shaded bands indicate the three service-rate regions.

        Parameters
        ----------
        save_path : str
            File path for the saved figure.

        Returns
        -------
        matplotlib Figure object.
        """
        if self.k1 is None:
            self.find_thresholds()

        mu1, mu2, mu3 = self.service_rates
        states = np.arange(self.N)
        rates  = self.rate_for_state

        fig, ax = plt.subplots(figsize=(10, 4.5))

        # ── shaded region backgrounds ─────────────────────────────────────
        k1 = self.k1 if self.k1 is not None else self.N
        k2 = self.k2 if self.k2 is not None else self.N

        ax.axvspan(0,       k1,      alpha=0.08, color='steelblue',  label=None)
        ax.axvspan(k1,      k2,      alpha=0.08, color='darkorange', label=None)
        ax.axvspan(k2, self.N - 1,   alpha=0.08, color='forestgreen',label=None)

        # ── step function of chosen rate ──────────────────────────────────
        ax.step(states, rates, where='post', color='#1a1a2e', linewidth=2.0,
                label='Optimal policy $\\pi^*(n)$')

        # ── threshold vertical lines ──────────────────────────────────────
        if self.k1 is not None:
            ax.axvline(self.k1, color='darkorange', linestyle='--', linewidth=1.4,
                       label=f'$k_1 = {self.k1}$')
        if self.k2 is not None:
            ax.axvline(self.k2, color='forestgreen', linestyle='--', linewidth=1.4,
                       label=f'$k_2 = {self.k2}$')

        # ── horizontal dashed lines at each rate ─────────────────────────
        for mu_val, lbl, clr in zip([mu1, mu2, mu3],
                                    [f'$\\mu_1={mu1}$', f'$\\mu_2={mu2}$', f'$\\mu_3={mu3}$'],
                                    ['steelblue', 'darkorange', 'forestgreen']):
            ax.axhline(mu_val, color=clr, linestyle=':', linewidth=1.0, alpha=0.6)

        # ── axes formatting ───────────────────────────────────────────────
        ax.set_xlabel('Queue length $n$', fontsize=12)
        ax.set_ylabel('Service rate $\\mu(n)$', fontsize=12)
        ax.set_title('Optimal Policy $\\pi^*(n)$: Service Rate vs Queue Length',
                     fontsize=13, fontweight='bold')
        ax.set_xlim(0, self.N - 1)
        ax.set_yticks([mu1, mu2, mu3])
        ax.set_yticklabels([f'$\\mu_1$={mu1}', f'$\\mu_2$={mu2}', f'$\\mu_3$={mu3}'])
        ax.legend(loc='center right', fontsize=10, framealpha=0.9)
        ax.grid(True, axis='x', alpha=0.3)
        ax.grid(True, axis='y', alpha=0.3)

        # ── region labels ─────────────────────────────────────────────────
        mid1 = k1 / 2
        mid2 = (k1 + k2) / 2
        mid3 = (k2 + self.N - 1) / 2
        y_top = mu3 + 0.3
        for mid, txt, clr in [(mid1, 'Slow\nregion', 'steelblue'),
                               (mid2, 'Medium\nregion', 'darkorange'),
                               (mid3, 'Fast\nregion', 'forestgreen')]:
            ax.text(mid, y_top, txt, ha='center', va='bottom',
                    fontsize=8, color=clr, style='italic')

        plt.tight_layout()
        fig.savefig(save_path, dpi=150, bbox_inches='tight')
        print(f"[policy_analysis] Policy plot saved: {save_path}")
        return fig

    # ──────────────────────────────────────────────────────────────────────────
    # 5.  Plot 2 — value function h(n)  (optional, if h is provided)
    # ──────────────────────────────────────────────────────────────────────────

    def plot_value_function(self,
                            h: np.ndarray,
                            save_path: str = "value_function_plot.png") -> plt.Figure:
        """
        Plots the relative value function h(n) to visually confirm convexity,
        which is the key structural property underlying the threshold result.

        Parameters
        ----------
        h         : relative value function from the solver (length N)
        save_path : file path for the saved figure
        """
        states = np.arange(len(h))

        fig, axes = plt.subplots(1, 2, figsize=(11, 4.2))

        # ── left: h(n) ────────────────────────────────────────────────────
        axes[0].plot(states, h, color='#2c7be5', linewidth=2)
        axes[0].set_xlabel('Queue length $n$', fontsize=11)
        axes[0].set_ylabel('$h(n)$', fontsize=11)
        axes[0].set_title('Relative Value Function $h(n)$', fontsize=12, fontweight='bold')
        axes[0].grid(True, alpha=0.3)

        # ── right: second difference Δ²h(n)  (convexity check) ───────────
        delta2 = np.diff(h, n=2)
        axes[1].bar(states[:-2], delta2, color='#e85d04', alpha=0.7, width=0.7)
        axes[1].axhline(0, color='black', linewidth=0.8)
        axes[1].set_xlabel('State $n$', fontsize=11)
        axes[1].set_ylabel('$\\Delta^2 h(n)$', fontsize=11)
        axes[1].set_title('Second Difference $\\Delta^2 h(n)$ (Convexity Check)',
                           fontsize=12, fontweight='bold')
        axes[1].grid(True, alpha=0.3)

        # Annotate convexity conclusion
        pct_positive = 100 * np.mean(delta2 >= 0)
        axes[1].text(0.97, 0.95,
                     f'{pct_positive:.0f}% ≥ 0\n(convex)',
                     transform=axes[1].transAxes,
                     ha='right', va='top', fontsize=9,
                     bbox=dict(boxstyle='round,pad=0.3', facecolor='lightyellow',
                               edgecolor='gray', alpha=0.8))

        plt.suptitle('Value Function Analysis', fontsize=13, fontweight='bold', y=1.01)
        plt.tight_layout()
        fig.savefig(save_path, dpi=150, bbox_inches='tight')
        print(f"[policy_analysis] Value function plot saved: {save_path}")
        return fig

    # ──────────────────────────────────────────────────────────────────────────
    # 6.  Convenience: run everything at once
    # ──────────────────────────────────────────────────────────────────────────

    def run_all(self,
                h: Optional[np.ndarray] = None,
                policy_plot_path: str = "policy_plot.png",
                value_plot_path:  str = "value_function_plot.png"):
        """
        Runs the full analysis pipeline:
          1. Print threshold summary
          2. Generate policy plot
          3. (Optional) Generate value function plot if h is supplied
        """
        self.print_summary()
        self.plot_policy(save_path=policy_plot_path)
        if h is not None:
            self.plot_value_function(h, save_path=value_plot_path)


# ──────────────────────────────────────────────────────────────────────────────
# Standalone demo  (python policy_analysis.py)
# ──────────────────────────────────────────────────────────────────────────────

if __name__ == "__main__":

    # ── baseline parameters (agreed by all members) ───────────────────────
    N             = 50
    lam           = 3.0
    service_rates = [2.0, 4.0, 6.0]
    c_h           = 1.0
    c_a           = [0.0, 1.0, 3.0]

    # ── use a demo threshold policy (replace with solver output) ──────────
    pi = _demo_policy(N=N, mu_rates=service_rates, k1=4, k2=10)

    # ── generate a plausible synthetic h(n) for demo  ─────────────────────
    # h(n) should be convex and increasing; use a simple quadratic demo
    rng = np.random.default_rng(42)
    h_demo = 0.5 * np.arange(N) ** 1.6 + rng.normal(0, 0.05, N).cumsum()

    # ── run analysis ──────────────────────────────────────────────────────
    analyzer = PolicyAnalyzer(
        policy        = pi,
        service_rates = service_rates,
        lam           = lam,
        c_h           = c_h,
        c_a           = c_a,
    )

    analyzer.run_all(
        h                = h_demo,
        policy_plot_path = "policy_plot.png",
        value_plot_path  = "value_function_plot.png",
    )

    print("\n[INFO] Demo complete. Plots saved to working directory.")
    print("[INFO] To use with real solver output:")
    print("       from policy_analysis import PolicyAnalyzer")
    print("       analyzer = PolicyAnalyzer(policy=pi, service_rates=[2,4,6])")
    print("       analyzer.run_all(h=h_values)")
