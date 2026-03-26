"""
solvers.py — MDP Solvers for Optimal Queue Control via CTMDP
Member 3: Meftahul Jannati Anonna

Implements:
  - relative_value_iteration(mdp, tol=1e-6)
  - policy_iteration(mdp)

Both accept a UniformMDP object and return:
  (policy, g_star, h)
  where policy[n] = index of optimal action at state n (0, 1, or 2)
        g_star    = optimal long-run average cost
        h         = relative value (bias) function, shape (N,)
"""

import numpy as np


# ---------------------------------------------------------------------------
# Helper: compute Q-factors (action-value function) for a given h
# ---------------------------------------------------------------------------
def _compute_q_factors(mdp, h):
    """
    Q(n, a) = c̃(n, a) + Σ_m P(m | n, a) * h(m)
    Returns array of shape (N+1, |A|).
    """
    n_states = mdp.N + 1
    n_actions = mdp.n_actions
    Q = np.zeros((n_states, n_actions))
    for a_idx in range(n_actions):
        # Transition matrix for action a: shape (N+1, N+1)
        P_a = mdp.P[:, :, a_idx]          # P[n, m, a]
        # Cost vector for action a: shape (N+1,)
        c_a = mdp.c_tilde[:, a_idx]
        Q[:, a_idx] = c_a + P_a @ h
    return Q


# ---------------------------------------------------------------------------
# Solver 1: Relative Value Iteration (RVI)
# ---------------------------------------------------------------------------
def relative_value_iteration(mdp, tol=1e-6, max_iter=100_000):
    """
    Average-cost Relative Value Iteration.

    Algorithm:
      1. Initialize h = 0
      2. At each iteration, compute
            h_new(n) = min_a [ c̃(n,a) + Σ_m P(m|n,a) h(m) ]
      3. Subtract h_new[ref] to fix the gauge (ref = state 0)
      4. Repeat until max|h_new - h| < tol
      5. g* = (h_new[ref] before subtraction) / 1  (already per step)
             equivalently, the span of h_new - h at convergence / 2

    Parameters
    ----------
    mdp : UniformMDP object
    tol : convergence tolerance on the span of Bellman residuals

    Returns
    -------
    policy : np.ndarray, shape (N+1,), dtype int
        policy[n] = index of optimal action at state n
    g_star : float
        optimal long-run average cost (in original time, multiply by Lambda)
    h : np.ndarray, shape (N+1,)
        relative value (bias) function
    """
    n_states = mdp.N + 1
    h = np.zeros(n_states)
    ref = 0  # reference state for gauge fixing

    for iteration in range(max_iter):
        Q = _compute_q_factors(mdp, h)
        h_new = Q.min(axis=1)

        # Estimate g* from the reference state shift
        g_hat = h_new[ref]

        # Gauge fix: subtract reference value so h_new[ref] = 0
        h_new = h_new - g_hat

        # Check convergence via span semi-norm
        diff = h_new - h
        span = diff.max() - diff.min()
        h = h_new

        if span < tol:
            break
    else:
        print(f"[RVI] Warning: did not converge in {max_iter} iterations.")

    # Recover optimal policy
    Q_final = _compute_q_factors(mdp, h)
    policy = Q_final.argmin(axis=1)

    # g* in original continuous-time units = g_hat * Lambda
    g_star = g_hat * mdp.Lambda

    print(f"[RVI] Converged in {iteration + 1} iterations.")
    print(f"[RVI] Optimal average cost g* = {g_star:.6f}")
    print(f"[RVI] Thresholds (action indices): {_find_thresholds(policy)}")

    return policy, g_star, h


# ---------------------------------------------------------------------------
# Solver 2: Policy Iteration (PI)
# ---------------------------------------------------------------------------
def policy_iteration(mdp, max_iter=1000):
    """
    Average-cost Policy Iteration.

    Algorithm:
      1. Start with arbitrary policy π (e.g., always use action 0)
      2. Policy Evaluation: solve the linear system
            h(n) - Σ_m P(m|n,π(n)) h(m) = c̃(n,π(n)) - g,   ∀ n
         with normalization h[ref] = 0 → solve for (g, h)
      3. Policy Improvement: greedy update
            π_new(n) = argmin_a [ c̃(n,a) + Σ_m P(m|n,a) h(m) ]
      4. Repeat until policy does not change

    Parameters
    ----------
    mdp : UniformMDP object

    Returns
    -------
    policy : np.ndarray, shape (N+1,), dtype int
    g_star : float
    h : np.ndarray, shape (N+1,)
    """
    n_states = mdp.N + 1
    ref = 0  # reference state: h[ref] = 0

    # Step 1: Initialize with a stable policy (highest service rate)
    # This ensures the Markov chain is ergodic for policy evaluation
    n_actions = mdp.n_actions
    policy = np.full(n_states, n_actions - 1, dtype=int)

    h = np.zeros(n_states)
    g_star = 0.0

    for iteration in range(max_iter):
        # ------------------------------------------------------------------
        # Step 2: Policy Evaluation — solve linear system for (g, h)
        # Average cost equation: g + h(n) = c(n, pi(n)) + sum_m P(m|n,pi(n)) h(m)
        # Rearranged: (I - P_pi) h + g * 1 = c_pi
        # We fix h[ref] = 0 and solve for remaining h and g
        # ------------------------------------------------------------------
        # Transition matrix under current policy
        P_pi = np.zeros((n_states, n_states))
        c_pi = np.zeros(n_states)
        for n in range(n_states):
            a = policy[n]
            P_pi[n, :] = mdp.P[n, :, a]
            c_pi[n] = mdp.c_tilde[n, a]

        # Build square system by combining constraint h[ref]=0
        # Unknowns: [h(0), h(1), ..., h(N), g] but h(ref)=0 reduces dimension
        #
        # Alternative approach: Use iterative policy evaluation
        # h_new = c_pi + P_pi @ h - g, with g = mean update
        h_eval = np.zeros(n_states)
        for _ in range(10000):
            h_new = c_pi + P_pi @ h_eval
            g = h_new[ref]  # Extract average cost estimate
            h_new = h_new - g  # Normalize
            if np.max(np.abs(h_new - h_eval)) < 1e-10:
                break
            h_eval = h_new
        h = h_eval
        g = g  # This is g in discrete time

        # ------------------------------------------------------------------
        # Step 3: Policy Improvement — greedy
        # ------------------------------------------------------------------
        Q = _compute_q_factors(mdp, h)
        policy_new = Q.argmin(axis=1)

        # ------------------------------------------------------------------
        # Step 4: Check convergence
        # ------------------------------------------------------------------
        if np.all(policy_new == policy):
            policy = policy_new
            g_star = g * mdp.Lambda  # back to continuous time
            break

        policy = policy_new
    else:
        print(f"[PI] Warning: did not converge in {max_iter} iterations.")
        g_star = g * mdp.Lambda

    print(f"[PI] Converged in {iteration + 1} iterations.")
    print(f"[PI] Optimal average cost g* = {g_star:.6f}")
    print(f"[PI] Thresholds (action indices): {_find_thresholds(policy)}")

    return policy, g_star, h


# ---------------------------------------------------------------------------
# Helper: extract threshold values from a monotone policy
# ---------------------------------------------------------------------------
def _find_thresholds(policy):
    """
    Given a monotone policy array, find thresholds k1, k2 such that:
      policy[n] = 0  for n < k1
      policy[n] = 1  for k1 <= n < k2
      policy[n] = 2  for n >= k2
    Returns dict with k1 and k2 (or None if a region is absent).
    """
    k1, k2 = None, None
    for n in range(1, len(policy)):
        if policy[n] != policy[n - 1]:
            if policy[n] == 1 and k1 is None:
                k1 = n
            elif policy[n] == 2 and k2 is None:
                k2 = n
    return {"k1": k1, "k2": k2}


# ---------------------------------------------------------------------------
# Verification: compare RVI and PI outputs
# ---------------------------------------------------------------------------
def verify_solvers(mdp, tol=1e-4):
    """Run both solvers and verify they produce the same policy and g*."""
    print("=" * 55)
    print("Running Relative Value Iteration...")
    pi_rvi, g_rvi, h_rvi = relative_value_iteration(mdp)

    print("\nRunning Policy Iteration...")
    pi_pi, g_pi, h_pi = policy_iteration(mdp)

    print("\n--- Verification ---")
    policy_match = np.all(pi_rvi == pi_pi)
    g_match = abs(g_rvi - g_pi) < tol

    print(f"Policies match:   {policy_match}")
    print(f"g* match (tol={tol}): {g_match}  "
          f"(RVI={g_rvi:.6f}, PI={g_pi:.6f})")

    if not policy_match:
        diff_states = np.where(pi_rvi != pi_pi)[0]
        print(f"Policy differs at states: {diff_states}")

    print("=" * 55)
    return pi_rvi, g_rvi, h_rvi, pi_pi, g_pi, h_pi
