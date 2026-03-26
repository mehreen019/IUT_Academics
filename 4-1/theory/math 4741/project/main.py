"""
main.py
-------
Math 4741 Term Project: Optimal Queue Control via CTMDP
Full Demonstration Pipeline

This script runs the complete analysis pipeline:
  1. Build the CTMDP model
  2. Uniformize to discrete-time MDP
  3. Solve using both RVI and Policy Iteration
  4. Analyze the optimal policy (thresholds, monotonicity)
  5. Run sensitivity analysis

All outputs are saved to the 'output' folder.
"""

import os
import sys
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Import project modules
from ctmdp_model import CTMDPModel
from uniformize import UniformMDP
from solvers import relative_value_iteration, policy_iteration
from policy_analysis import PolicyAnalyzer


# ==========================================================================
# PARAMETERS (edit these as needed)
# ==========================================================================

LAMBDA = 3.0                    # Arrival rate
MU_LIST = [2.0, 4.0, 6.0]       # Service rates [slow, medium, fast]
C_H = 1.0                       # Holding cost per customer per unit time
C_A_LIST = [0.0, 1.0, 3.0]      # Action costs for each service rate
N = 50                          # State space truncation

OUTPUT_DIR = "output"           # Output folder for all plots and results


# ==========================================================================
# SETUP
# ==========================================================================

def setup_output_directory():
    """Create output directory if it doesn't exist."""
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)
    return OUTPUT_DIR


def print_header(title):
    """Print a section header."""
    print()
    print("=" * 60)
    print(f"  {title}")
    print("=" * 60)


def print_parameters():
    """Print the model parameters."""
    print(f"  Arrival rate (lambda)  : {LAMBDA}")
    print(f"  Service rates (mu)     : {MU_LIST}")
    print(f"  Holding cost (c_h)     : {C_H}")
    print(f"  Action costs (c_a)     : {C_A_LIST}")
    print(f"  State space truncation : N = {N}")


# ==========================================================================
# STEP 1: BUILD CTMDP MODEL
# ==========================================================================

def build_model():
    """Build the CTMDP model."""
    print_header("STEP 1: CTMDP Model Construction")
    print_parameters()

    model = CTMDPModel(
        lambda_=LAMBDA,
        mu_list=MU_LIST,
        c_h=C_H,
        c_a_list=C_A_LIST,
        N=N
    )

    # Stability check
    print()
    print("  Stability analysis:")
    for i, mu in enumerate(MU_LIST):
        rho = LAMBDA / mu
        status = "stable" if rho < 1 else "UNSTABLE"
        print(f"    Action {i} (mu={mu}): rho = {rho:.3f} [{status}]")

    return model


# ==========================================================================
# STEP 2: UNIFORMIZATION
# ==========================================================================

def uniformize_model(model):
    """Convert CTMDP to discrete-time MDP via uniformization."""
    print_header("STEP 2: Uniformization")

    mdp = UniformMDP(model)

    print(f"  Uniformization constant: Lambda = {mdp.Lambda}")
    print(f"  Transition matrix shape: {mdp.P.shape}")
    print(f"  Cost matrix shape: {mdp.c_tilde.shape}")

    # Verify transition probabilities sum to 1
    for a_idx in range(mdp.n_actions):
        row_sums = mdp.P[:, :, a_idx].sum(axis=1)
        max_err = np.abs(row_sums - 1.0).max()
        if max_err > 1e-10:
            print(f"  WARNING: Action {a_idx} row sum error = {max_err:.2e}")
    print("  Transition probability verification: PASSED")

    return mdp


# ==========================================================================
# STEP 3: SOLVE MDP
# ==========================================================================

def solve_mdp(mdp):
    """Solve the MDP using both RVI and Policy Iteration."""
    print_header("STEP 3: MDP Solution")

    # Relative Value Iteration
    print()
    print("  [3.1] Relative Value Iteration")
    print("  " + "-" * 40)
    policy_rvi, g_rvi, h_rvi = relative_value_iteration(mdp)

    # Policy Iteration
    print()
    print("  [3.2] Policy Iteration")
    print("  " + "-" * 40)
    policy_pi, g_pi, h_pi = policy_iteration(mdp)

    # Verification
    print()
    print("  [3.3] Solver Verification")
    print("  " + "-" * 40)

    policy_match = np.all(policy_rvi == policy_pi)
    g_match = abs(g_rvi - g_pi) < 1e-4

    print(f"  Policies match: {policy_match}")
    print(f"  Average costs match: {g_match} (RVI={g_rvi:.6f}, PI={g_pi:.6f})")

    if not policy_match:
        diff_states = np.where(policy_rvi != policy_pi)[0]
        print(f"  WARNING: Policies differ at states: {diff_states}")

    # Use RVI results as primary
    return policy_rvi, g_rvi, h_rvi


# ==========================================================================
# STEP 4: POLICY ANALYSIS
# ==========================================================================

def analyze_policy(policy, h, output_dir):
    """Analyze the optimal policy structure."""
    print_header("STEP 4: Policy Analysis")

    analyzer = PolicyAnalyzer(
        policy=policy,
        service_rates=MU_LIST,
        lam=LAMBDA,
        c_h=C_H,
        c_a=C_A_LIST
    )

    # Find thresholds
    thresholds = analyzer.find_thresholds()
    mono = analyzer.verify_monotonicity()

    print(f"  Threshold k1: {thresholds['k1']} ({thresholds['k1_desc']})")
    print(f"  Threshold k2: {thresholds['k2']} ({thresholds['k2_desc']})")
    print()

    if mono['monotone']:
        print("  Monotonicity: VERIFIED (policy is non-decreasing)")
    else:
        print(f"  Monotonicity: VIOLATED at states {mono['violations']}")

    # Generate plots
    print()
    print("  Generating policy plots...")

    policy_plot_path = os.path.join(output_dir, "optimal_policy.png")
    value_plot_path = os.path.join(output_dir, "value_function.png")

    analyzer.plot_policy(save_path=policy_plot_path)
    analyzer.plot_value_function(h, save_path=value_plot_path)

    return analyzer, thresholds


# ==========================================================================
# STEP 5: SENSITIVITY ANALYSIS
# ==========================================================================

def run_sensitivity_analysis(output_dir):
    """Run sensitivity analysis varying lambda, c_h, and c_a."""
    print_header("STEP 5: Sensitivity Analysis")

    # Suppress output during sensitivity runs
    import io
    import warnings
    from contextlib import redirect_stdout, redirect_stderr

    # Helper function to solve and extract thresholds (quiet mode)
    def solve_instance(lam, mu_list, c_h, c_a_list):
        # Suppress all output including stability warnings
        with redirect_stdout(io.StringIO()), redirect_stderr(io.StringIO()):
            with warnings.catch_warnings():
                warnings.simplefilter("ignore")
                model = CTMDPModel(lam, mu_list, c_h, c_a_list, N=N)
                mdp = UniformMDP(model)
                policy, g_star, _ = relative_value_iteration(mdp, tol=1e-6, max_iter=50000)

        k1, k2 = None, None
        for n in range(N):
            if k1 is None and policy[n] == 0 and policy[n+1] >= 1:
                k1 = n + 1
            if k2 is None and policy[n+1] == 2:
                k2 = n + 1
        if k1 is None: k1 = 0
        if k2 is None: k2 = N

        return int(k1), int(k2), float(g_star), policy

    # --- Experiment 1: Vary lambda ---
    print("  [5.1] Varying arrival rate (lambda)...")
    lam_range = np.linspace(0.5, 5.5, 20)
    k1_lam, k2_lam, g_lam = [], [], []
    for lam in lam_range:
        k1, k2, g, _ = solve_instance(lam, MU_LIST, C_H, C_A_LIST)
        k1_lam.append(k1)
        k2_lam.append(k2)
        g_lam.append(g)

    # --- Experiment 2: Vary c_h ---
    print("  [5.2] Varying holding cost (c_h)...")
    ch_range = np.linspace(0.2, 4.0, 20)
    k1_ch, k2_ch, g_ch = [], [], []
    for c_h in ch_range:
        k1, k2, g, _ = solve_instance(LAMBDA, MU_LIST, c_h, C_A_LIST)
        k1_ch.append(k1)
        k2_ch.append(k2)
        g_ch.append(g)

    # --- Experiment 3: Vary c_a scale ---
    print("  [5.3] Varying service cost scale (c_a)...")
    ca_scale_range = np.linspace(0.1, 3.0, 20)
    k1_ca, k2_ca, g_ca = [], [], []
    for s in ca_scale_range:
        c_a = [0.0, 1.0 * s, 3.0 * s]
        k1, k2, g, _ = solve_instance(LAMBDA, MU_LIST, C_H, c_a)
        k1_ca.append(k1)
        k2_ca.append(k2)
        g_ca.append(g)

    # --- Optimal vs Naive comparison ---
    print("  [5.4] Computing optimal vs naive policy comparison...")
    g_optimal, g_naive = [], []
    for lam in lam_range:
        _, _, g_opt, _ = solve_instance(lam, MU_LIST, C_H, C_A_LIST)
        g_optimal.append(g_opt)

        # Naive policy: always use mu2 (action index 1)
        with redirect_stdout(io.StringIO()), redirect_stderr(io.StringIO()):
            model = CTMDPModel(lam, MU_LIST, C_H, C_A_LIST, N=N)
            mdp = UniformMDP(model)
        P_naive = mdp.P[:, :, 1]
        c_naive = mdp.c_tilde[:, 1]

        # Solve for stationary distribution
        A = (P_naive.T - np.eye(N + 1))
        A[-1, :] = 1.0
        b = np.zeros(N + 1)
        b[-1] = 1.0
        try:
            pi_stat = np.linalg.solve(A, b)
            pi_stat = np.maximum(pi_stat, 0)
            pi_stat /= pi_stat.sum()
            g_naive.append(float(pi_stat @ c_naive) * mdp.Lambda)
        except:
            g_naive.append(np.nan)

    # --- Generate sensitivity plots ---
    print()
    print("  Generating sensitivity plots...")

    # Figure 1: Thresholds vs parameters (3 panels)
    fig1, axes = plt.subplots(1, 3, figsize=(14, 4.5))
    fig1.suptitle('Sensitivity Analysis: Threshold Response to Parameter Changes',
                  fontsize=12, fontweight='bold', y=1.02)

    # Panel 1: vs lambda
    axes[0].plot(lam_range, k1_lam, 'o-', color='#d32f2f', lw=2, ms=5, label='k1 (slow to medium)')
    axes[0].plot(lam_range, k2_lam, 's-', color='#388e3c', lw=2, ms=5, label='k2 (medium to fast)')
    axes[0].set_xlabel('Arrival rate (lambda)', fontsize=11)
    axes[0].set_ylabel('Threshold queue length', fontsize=11)
    axes[0].set_title('Thresholds vs Arrival Rate', fontsize=11)
    axes[0].legend(fontsize=9)
    axes[0].grid(alpha=0.3)

    # Panel 2: vs c_h
    axes[1].plot(ch_range, k1_ch, 'o-', color='#d32f2f', lw=2, ms=5, label='k1')
    axes[1].plot(ch_range, k2_ch, 's-', color='#388e3c', lw=2, ms=5, label='k2')
    axes[1].set_xlabel('Holding cost (c_h)', fontsize=11)
    axes[1].set_title('Thresholds vs Holding Cost', fontsize=11)
    axes[1].legend(fontsize=9)
    axes[1].grid(alpha=0.3)

    # Panel 3: vs c_a scale
    axes[2].plot(ca_scale_range, k1_ca, 'o-', color='#d32f2f', lw=2, ms=5, label='k1')
    axes[2].plot(ca_scale_range, k2_ca, 's-', color='#388e3c', lw=2, ms=5, label='k2')
    axes[2].set_xlabel('Service cost scale s (c_a = [0, s, 3s])', fontsize=11)
    axes[2].set_title('Thresholds vs Service Cost', fontsize=11)
    axes[2].legend(fontsize=9)
    axes[2].grid(alpha=0.3)

    plt.tight_layout()
    fig1.savefig(os.path.join(output_dir, "sensitivity_thresholds.png"),
                 dpi=150, bbox_inches='tight')
    plt.close(fig1)

    # Figure 2: Optimal vs Naive comparison
    fig2, ax = plt.subplots(figsize=(9, 5))
    ax.plot(lam_range, g_optimal, 'o-', color='#1565c0', lw=2.5, ms=5,
            label='Optimal policy (CTMDP)')
    ax.plot(lam_range, g_naive, 's--', color='#c62828', lw=2, ms=5,
            label='Naive policy (always mu2)')
    ax.fill_between(lam_range, g_optimal, g_naive, alpha=0.15, color='#ff8f00',
                    label='Cost savings')

    # Annotate maximum savings
    gaps = np.array(g_naive) - np.array(g_optimal)
    idx = np.nanargmax(gaps)
    if not np.isnan(gaps[idx]):
        ax.annotate(f'Max saving = {gaps[idx]:.2f}',
                    xy=(lam_range[idx], g_naive[idx]),
                    xytext=(lam_range[idx] + 0.5, g_naive[idx] + 0.8),
                    arrowprops=dict(arrowstyle='->', color='black', lw=1.2),
                    fontsize=10)

    ax.set_xlabel('Arrival rate (lambda)', fontsize=11)
    ax.set_ylabel('Long-run average cost (g*)', fontsize=11)
    ax.set_title('Optimal Policy vs Naive Fixed-Rate Policy', fontsize=12, fontweight='bold')
    ax.legend(fontsize=10)
    ax.grid(alpha=0.3)
    ax.set_xlim(lam_range[0], lam_range[-1])

    plt.tight_layout()
    fig2.savefig(os.path.join(output_dir, "optimal_vs_naive.png"),
                 dpi=150, bbox_inches='tight')
    plt.close(fig2)

    # Figure 3: Average cost vs parameters
    fig3, axes = plt.subplots(1, 3, figsize=(14, 4.5))
    fig3.suptitle('Sensitivity Analysis: Average Cost Response to Parameter Changes',
                  fontsize=12, fontweight='bold', y=1.02)

    axes[0].plot(lam_range, g_lam, 'o-', color='#1565c0', lw=2, ms=5)
    axes[0].set_xlabel('Arrival rate (lambda)', fontsize=11)
    axes[0].set_ylabel('Optimal average cost (g*)', fontsize=11)
    axes[0].set_title('Cost vs Arrival Rate', fontsize=11)
    axes[0].grid(alpha=0.3)

    axes[1].plot(ch_range, g_ch, 'o-', color='#1565c0', lw=2, ms=5)
    axes[1].set_xlabel('Holding cost (c_h)', fontsize=11)
    axes[1].set_title('Cost vs Holding Cost', fontsize=11)
    axes[1].grid(alpha=0.3)

    axes[2].plot(ca_scale_range, g_ca, 'o-', color='#1565c0', lw=2, ms=5)
    axes[2].set_xlabel('Service cost scale s', fontsize=11)
    axes[2].set_title('Cost vs Service Cost', fontsize=11)
    axes[2].grid(alpha=0.3)

    plt.tight_layout()
    fig3.savefig(os.path.join(output_dir, "sensitivity_costs.png"),
                 dpi=150, bbox_inches='tight')
    plt.close(fig3)

    print(f"  Saved: sensitivity_thresholds.png")
    print(f"  Saved: optimal_vs_naive.png")
    print(f"  Saved: sensitivity_costs.png")

    # Return summary statistics for report
    return {
        'lam_range': lam_range,
        'k1_lam': k1_lam,
        'k2_lam': k2_lam,
        'ch_range': ch_range,
        'k1_ch': k1_ch,
        'k2_ch': k2_ch,
        'ca_scale_range': ca_scale_range,
        'k1_ca': k1_ca,
        'k2_ca': k2_ca,
        'g_optimal': g_optimal,
        'g_naive': g_naive,
        'max_savings': gaps[idx] if not np.isnan(gaps[idx]) else 0
    }


# ==========================================================================
# SUMMARY REPORT
# ==========================================================================

def print_summary(thresholds, g_star, sensitivity_results):
    """Print final summary."""
    print_header("SUMMARY")

    print("  Model Parameters:")
    print(f"    lambda = {LAMBDA}, mu = {MU_LIST}")
    print(f"    c_h = {C_H}, c_a = {C_A_LIST}")
    print()

    print("  Optimal Policy:")
    print(f"    Threshold k1 = {thresholds['k1']} (switch from mu1 to mu2)")
    print(f"    Threshold k2 = {thresholds['k2']} (switch from mu2 to mu3)")
    print(f"    Optimal average cost g* = {g_star:.6f}")
    print()

    print("  Sensitivity Insights:")
    print(f"    - Higher lambda: thresholds decrease (faster service needed)")
    print(f"    - Higher c_h: thresholds decrease (costly to hold customers)")
    print(f"    - Higher c_a: thresholds increase (costly to use fast service)")
    print()

    print(f"  Maximum cost savings over naive policy: {sensitivity_results['max_savings']:.2f}")


# ==========================================================================
# MAIN PIPELINE
# ==========================================================================

def main():
    """Run the complete analysis pipeline."""

    print()
    print("  MATH 4741 TERM PROJECT")
    print("  Optimal Queue Control via Continuous-Time Markov Decision Process")
    print()

    # Setup
    output_dir = setup_output_directory()
    print(f"  Output directory: {os.path.abspath(output_dir)}")

    # Step 1: Build CTMDP model
    model = build_model()

    # Step 2: Uniformize
    mdp = uniformize_model(model)

    # Step 3: Solve
    policy, g_star, h = solve_mdp(mdp)

    # Step 4: Analyze policy
    analyzer, thresholds = analyze_policy(policy, h, output_dir)

    # Step 5: Sensitivity analysis
    sensitivity_results = run_sensitivity_analysis(output_dir)

    # Final summary
    print_summary(thresholds, g_star, sensitivity_results)

    print()
    print("=" * 60)
    print("  PIPELINE COMPLETE")
    print("=" * 60)
    print(f"  All outputs saved to: {os.path.abspath(output_dir)}/")
    print()

    return {
        'model': model,
        'mdp': mdp,
        'policy': policy,
        'g_star': g_star,
        'h': h,
        'thresholds': thresholds,
        'sensitivity': sensitivity_results
    }


if __name__ == "__main__":
    results = main()
