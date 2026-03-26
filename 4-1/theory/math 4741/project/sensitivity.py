"""
sensitivity.py
Member 5 - Jannatul Fardus Rakhi (210041237)
Math 4741 Term Project: Optimal Queue Control via CTMDP

======================================================================
HOW TO SWITCH BETWEEN STANDALONE AND TEAM MODE:

  RIGHT NOW (running alone):
    - MODE A block below is UNCOMMENTED  → uses embedded classes
    - MODE B block below is COMMENTED OUT

  WHEN TEAM FILES ARE READY:
    - Comment out the entire MODE A block
    - Uncomment the 3 lines in MODE B
    - Make sure all .py files are in the same folder
    - Done. Everything else stays exactly the same.
======================================================================
"""

import numpy as np
import matplotlib.pyplot as plt


# ======================================================================
# MODE A — STANDALONE (comment this entire block out when team is ready)
# ======================================================================

# class CTMDPModel:
#     """
#     M/M/1 queue with 3 controllable service rates.
#     State  : n in {0, 1, ..., N}
#     Actions: a in {0, 1, 2}  (index into mu_list)
#     Cost   : c(n, a) = c_h * n + c_a[a]
#     """
#     def __init__(self, lam, mu_list, c_h, c_a_list, N=50):
#         self.lam       = lam
#         self.mu_list   = mu_list
#         self.c_h       = c_h
#         self.c_a_list  = c_a_list
#         self.N         = N
#         self.n_states  = N + 1
#         self.n_actions = len(mu_list)
#
#     def cost(self, n, a):
#         return self.c_h * n + self.c_a_list[a]
#
#     def transition_rates(self, n, n_prime, a):
#         mu = self.mu_list[a]
#         if n_prime == n + 1 and n < self.N:
#             return self.lam
#         elif n_prime == n - 1 and n > 0:
#             return mu
#         return 0.0
#
#
# class UniformMDP:
#     """
#     Converts CTMDPModel to discrete-time MDP via uniformization.
#     Lambda >= lam + max(mu_list)
#     Rescaled cost: c_tilde(n,a) = c(n,a) / Lambda
#     """
#     def __init__(self, model):
#         self.model  = model
#         self.Lambda = model.lam + max(model.mu_list) + 1e-9
#         N  = model.N
#         nA = model.n_actions
#         self.P       = np.zeros((N+1, N+1, nA))
#         self.c_tilde = np.zeros((N+1, nA))
#         for n in range(N+1):
#             for a in range(nA):
#                 mu = model.mu_list[a]
#                 if n > 0:
#                     self.P[n, n-1, a] = mu / self.Lambda
#                 if n < N:
#                     self.P[n, n+1, a] = model.lam / self.Lambda
#                 self.P[n, n, a] = 1.0 - (model.lam * (n < N) + mu * (n > 0)) / self.Lambda
#                 self.c_tilde[n, a] = model.cost(n, a) / self.Lambda
#
#
# def relative_value_iteration(mdp, tol=1e-6, max_iter=10000):
#     """Solves average-cost Bellman equation via RVI."""
#     N  = mdp.model.N
#     nA = mdp.model.n_actions
#     h  = np.zeros(N+1)
#     ref = 0
#     for _ in range(max_iter):
#         h_new = np.array([
#             np.min([mdp.c_tilde[n, a] + mdp.P[n, :, a] @ h for a in range(nA)])
#             for n in range(N+1)
#         ])
#         h_new -= h_new[ref]
#         if np.max(np.abs(h_new - h)) < tol:
#             break
#         h = h_new
#     policy = np.array([
#         np.argmin([mdp.c_tilde[n, a] + mdp.P[n, :, a] @ h for a in range(nA)])
#         for n in range(N+1)
#     ])
#     q_ref  = [mdp.c_tilde[ref, a] + mdp.P[ref, :, a] @ h for a in range(nA)]
#     g_star = np.min(q_ref) * mdp.Lambda
#     return policy, g_star, h

# ======================================================================
# END OF MODE A
# ======================================================================


# ======================================================================
# MODE B — TEAM MODE (uncomment these 3 lines when team files are ready)
# ======================================================================

from ctmdp_model import CTMDPModel
from uniformize import UniformMDP
from solvers import relative_value_iteration

# ======================================================================
# END OF MODE B
# ======================================================================


# ======================================================================
# BASELINE PARAMETERS  (agreed by the whole team — do not change)
# ======================================================================

BASE_LAM = 3.0
BASE_MU  = [2.0, 4.0, 6.0]
BASE_CH  = 1.0
BASE_CA  = [0.0, 1.0, 3.0]
N        = 50


# ======================================================================
# HELPER: build → solve → extract thresholds k1, k2, g*
# ======================================================================

def solve_instance(lam, mu_list, c_h, c_a_list, N=50):
    model  = CTMDPModel(lam, mu_list, c_h, c_a_list, N=N)
    mdp    = UniformMDP(model)
    policy, g_star, _ = relative_value_iteration(mdp)

    k1, k2 = None, None
    for n in range(N):
        if k1 is None and policy[n] == 0 and policy[n+1] >= 1:
            k1 = n + 1
        if k2 is None and policy[n+1] == 2:
            k2 = n + 1
    if k1 is None: k1 = 0
    if k2 is None: k2 = N

    return int(k1), int(k2), float(g_star), policy


# ======================================================================
# SENSITIVITY EXPERIMENT 1 — Vary arrival rate lambda
# ======================================================================

print("Running sensitivity analysis...")
print("  [1/3] Varying lambda...")

lam_range = np.linspace(0.5, 5.5, 20)
k1_lam, k2_lam, g_lam = [], [], []
for lam in lam_range:
    k1, k2, g, _ = solve_instance(lam, BASE_MU, BASE_CH, BASE_CA, N)
    k1_lam.append(k1); k2_lam.append(k2); g_lam.append(g)


# ======================================================================
# SENSITIVITY EXPERIMENT 2 — Vary holding cost c_h
# ======================================================================

print("  [2/3] Varying c_h...")

ch_range = np.linspace(0.2, 4.0, 20)
k1_ch, k2_ch, g_ch = [], [], []
for c_h in ch_range:
    k1, k2, g, _ = solve_instance(BASE_LAM, BASE_MU, c_h, BASE_CA, N)
    k1_ch.append(k1); k2_ch.append(k2); g_ch.append(g)


# ======================================================================
# SENSITIVITY EXPERIMENT 3 — Vary service cost c_a (scale factor)
# ======================================================================

print("  [3/3] Varying c_a scale...")

ca_scale_range = np.linspace(0.1, 3.0, 20)
k1_ca, k2_ca, g_ca = [], [], []
for s in ca_scale_range:
    c_a = [0.0, 1.0 * s, 3.0 * s]
    k1, k2, g, _ = solve_instance(BASE_LAM, BASE_MU, BASE_CH, c_a, N)
    k1_ca.append(k1); k2_ca.append(k2); g_ca.append(g)


# ======================================================================
# OPTIMAL vs NAIVE COMPARISON across lambda grid
# ======================================================================

print("  Computing optimal vs naive comparison...")

g_optimal, g_naive = [], []
for lam in lam_range:
    _, _, g_opt, _ = solve_instance(lam, BASE_MU, BASE_CH, BASE_CA, N)
    g_optimal.append(g_opt)

    model   = CTMDPModel(lam, BASE_MU, BASE_CH, BASE_CA, N=N)
    mdp     = UniformMDP(model)
    P_naive = mdp.P[:, :, 1]
    c_naive = mdp.c_tilde[:, 1]
    A = (P_naive.T - np.eye(N+1))
    A[-1, :] = 1.0
    b = np.zeros(N+1); b[-1] = 1.0
    try:
        pi = np.linalg.solve(A, b)
        pi = np.maximum(pi, 0); pi /= pi.sum()
        g_naive.append(float(pi @ c_naive) * mdp.Lambda)
    except Exception:
        g_naive.append(np.nan)


# ======================================================================
# BASELINE RESULTS PRINTOUT
# ======================================================================

print("  Generating plots...")
k1_base, k2_base, g_base, baseline_policy = solve_instance(BASE_LAM, BASE_MU, BASE_CH, BASE_CA, N)

print(f"\n--- BASELINE RESULTS ---")
print(f"  lambda={BASE_LAM}, mu={BASE_MU}, c_h={BASE_CH}, c_a={BASE_CA}")
print(f"  Threshold k1 = {k1_base}  (switch slow -> medium)")
print(f"  Threshold k2 = {k2_base}  (switch medium -> fast)")
print(f"  Optimal average cost g* = {g_base:.4f}")

violations = [n for n in range(N) if baseline_policy[n] > baseline_policy[n+1]]
if violations:
    print(f"  WARNING: monotonicity violated at states {violations}")
else:
    print(f"  Monotonicity check: PASSED")


# ======================================================================
# FIGURE 1 — Baseline optimal policy (step function)
# ======================================================================

fig1, ax = plt.subplots(figsize=(9, 4))
ax.step(np.arange(N+1), baseline_policy, where='post',
        color='#1a237e', linewidth=2.5, label='Optimal policy pi*(n)')
ax.axvline(k1_base, color='#e53935', linestyle='--', linewidth=1.5, label=f'k1 = {k1_base}')
ax.axvline(k2_base, color='#388e3c', linestyle='--', linewidth=1.5, label=f'k2 = {k2_base}')
ax.fill_betweenx([0, 2.2], 0,       k1_base, alpha=0.08, color='#2196F3', label='Slow zone')
ax.fill_betweenx([0, 2.2], k1_base, k2_base, alpha=0.08, color='#FF9800', label='Medium zone')
ax.fill_betweenx([0, 2.2], k2_base, N,       alpha=0.08, color='#4CAF50', label='Fast zone')
ax.set_yticks([0, 1, 2])
ax.set_yticklabels(['mu1 Slow', 'mu2 Medium', 'mu3 Fast'], fontsize=11)
ax.set_xlabel('Queue length n', fontsize=12)
ax.set_title(f'Optimal Threshold Policy  (lam={BASE_LAM}, c_h={BASE_CH}, c_a={BASE_CA})', fontsize=13)
ax.legend(loc='lower right', fontsize=9)
ax.set_xlim(0, N); ax.set_ylim(-0.2, 2.3)
ax.grid(axis='x', alpha=0.3)
plt.tight_layout()
plt.savefig('fig1_baseline_policy.png', dpi=150, bbox_inches='tight')
plt.close()


# ======================================================================
# FIGURE 2 — Sensitivity: thresholds vs each parameter (3 panels)
# ======================================================================

fig2, axes = plt.subplots(1, 3, figsize=(15, 5))
fig2.suptitle('Sensitivity Analysis: How Thresholds Respond to Parameter Changes',
              fontsize=13, fontweight='bold')

axes[0].plot(lam_range, k1_lam, 'o-', color='#e53935', lw=2, ms=5, label='k1 (slow->medium)')
axes[0].plot(lam_range, k2_lam, 's-', color='#388e3c', lw=2, ms=5, label='k2 (medium->fast)')
axes[0].set_xlabel('Arrival rate lambda', fontsize=11)
axes[0].set_ylabel('Threshold queue length', fontsize=11)
axes[0].set_title('Thresholds vs lambda', fontsize=12)
axes[0].legend(fontsize=9); axes[0].grid(alpha=0.3)

axes[1].plot(ch_range, k1_ch, 'o-', color='#e53935', lw=2, ms=5, label='k1')
axes[1].plot(ch_range, k2_ch, 's-', color='#388e3c', lw=2, ms=5, label='k2')
axes[1].set_xlabel('Holding cost c_h', fontsize=11)
axes[1].set_title('Thresholds vs c_h', fontsize=12)
axes[1].legend(fontsize=9); axes[1].grid(alpha=0.3)

axes[2].plot(ca_scale_range, k1_ca, 'o-', color='#e53935', lw=2, ms=5, label='k1')
axes[2].plot(ca_scale_range, k2_ca, 's-', color='#388e3c', lw=2, ms=5, label='k2')
axes[2].set_xlabel('Service cost scale s  (c_a = [0, s, 3s])', fontsize=11)
axes[2].set_title('Thresholds vs c_a', fontsize=12)
axes[2].legend(fontsize=9); axes[2].grid(alpha=0.3)

plt.tight_layout()
plt.savefig('fig2_sensitivity_thresholds.png', dpi=150, bbox_inches='tight')
plt.close()


# ======================================================================
# FIGURE 3 — Optimal vs Naive average cost comparison
# ======================================================================

fig3, ax = plt.subplots(figsize=(9, 4.5))
ax.plot(lam_range, g_optimal, 'o-', color='#1a237e', lw=2.5, ms=5, label='Optimal policy (CTMDP)')
ax.plot(lam_range, g_naive,   's--', color='#b71c1c', lw=2,   ms=5, label='Naive policy (always mu2)')
ax.fill_between(lam_range, g_optimal, g_naive, alpha=0.15,
                color='#ff8f00', label='Cost savings from optimal')
gaps = np.array(g_naive) - np.array(g_optimal)
idx  = np.nanargmax(gaps)
ax.annotate(f'Max saving\n= {gaps[idx]:.2f}',
            xy=(lam_range[idx], g_naive[idx]),
            xytext=(lam_range[idx]+0.4, g_naive[idx]+0.5),
            arrowprops=dict(arrowstyle='->', color='black'), fontsize=9)
ax.set_xlabel('Arrival rate lambda', fontsize=12)
ax.set_ylabel('Long-run average cost g*', fontsize=12)
ax.set_title('Optimal Policy vs Naive Fixed-Rate Policy', fontsize=13)
ax.legend(fontsize=10); ax.grid(alpha=0.3)
ax.set_xlim(lam_range[0], lam_range[-1])
plt.tight_layout()
plt.savefig('fig3_optimal_vs_naive.png', dpi=150, bbox_inches='tight')
plt.close()

print("\nAll figures saved:")
print("  fig1_baseline_policy.png")
print("  fig2_sensitivity_thresholds.png")
print("  fig3_optimal_vs_naive.png")
print("\nDone.")
