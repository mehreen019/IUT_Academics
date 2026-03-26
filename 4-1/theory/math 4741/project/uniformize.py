import numpy as np
from ctmdp_model import CTMDPModel


class UniformMDP:
    """
    Discrete-time MDP obtained by uniformizing a CTMDPModel.

    Uniformization converts the CTMDP into an equivalent discrete-time
    MDP by introducing a fictitious self-loop transition at every state
    so that all states transition at the same total rate Lambda. The
    optimal policy of the uniformized MDP is identical to the original CTMDP.

    Attributes
    ----------
    model     : CTMDPModel  The original continuous-time model
    Lambda    : float       Uniformization constant (>= lambda + max(mu))
    P         : np.ndarray  Transition tensor, shape (N+1, N+1, n_actions)
                            P[n, n_prime, a] = P(n' | n, a)
    c_tilde   : np.ndarray  Rescaled per-step costs, shape (N+1, n_actions)
                            c_tilde[n, a] = c(n, a) / Lambda
    N         : int         State space size (states 0 .. N)
    n_actions : int         Number of actions
    """

    def __init__(self, model: CTMDPModel):
        self.model = model
        self.N = model.N
        self.n_actions = len(model.mu_list)
        self.Lambda = model.lambda_ + max(model.mu_list)
        self.P = self._build_transition_tensor()
        self.c_tilde = self._build_cost_matrix()

    def _build_transition_tensor(self) -> np.ndarray:
        """
        Compute discrete transition probabilities via uniformization.

        For interior states n in {1, ..., N-1} under action a:
            P(n+1 | n, a) = lambda / Lambda          [arrival]
            P(n-1 | n, a) = mu(a) / Lambda           [departure]
            P(n   | n, a) = 1 - (lambda+mu(a))/Lambda [self-loop]

        For boundary n = 0:
            P(1 | 0, a) = lambda / Lambda
            P(0 | 0, a) = 1 - lambda / Lambda

        For boundary n = N:
            P(N-1 | N, a) = mu(a) / Lambda
            P(N   | N, a) = 1 - mu(a) / Lambda
        """
        N = self.N
        n_a = self.n_actions
        lam = self.model.lambda_
        Lambda = self.Lambda
        P = np.zeros((N + 1, N + 1, n_a))

        for a_idx, mu in enumerate(self.model.mu_list):
            for n in range(N + 1):

                # Arrival: n -> n+1 (blocked at N)
                if n < N:
                    P[n, n + 1, a_idx] = lam / Lambda

                # Departure: n -> n-1 (blocked at 0)
                if n > 0:
                    P[n, n - 1, a_idx] = mu / Lambda

                # Self-loop (fictitious do-nothing transition)
                if n == 0:
                    P[n, n, a_idx] = 1.0 - lam / Lambda
                elif n == N:
                    P[n, n, a_idx] = 1.0 - mu / Lambda
                else:
                    P[n, n, a_idx] = 1.0 - (lam + mu) / Lambda

        return P

    def _build_cost_matrix(self) -> np.ndarray:
        """
        Compute rescaled per-step costs.

        Each discrete step corresponds on average to a sojourn of duration
        1/Lambda in continuous time. Rescaling preserves the long-run
        average cost:

            c_tilde(n, a) = c(n, a) / Lambda
        """
        N = self.N
        n_a = self.n_actions
        c_tilde = np.zeros((N + 1, n_a))
        for n in range(N + 1):
            for a_idx in range(n_a):
                c_tilde[n, a_idx] = self.model.cost(n, a_idx) / self.Lambda
        return c_tilde

    def verify_transition_rows(self, tol: float = 1e-10) -> bool:
        """
        Verify that every row of P sums to 1 for all actions.

        Returns True if valid, raises AssertionError otherwise.
        """
        for a_idx, mu in enumerate(self.model.mu_list):
            row_sums = self.P[:, :, a_idx].sum(axis=1)
            if not np.allclose(row_sums, 1.0, atol=tol):
                bad = np.where(np.abs(row_sums - 1.0) > tol)[0]
                raise AssertionError(
                    f"Action mu={mu}: rows {bad} do not sum to 1. "
                    f"Values: {row_sums[bad]}"
                )
        print("Verification passed: all transition rows sum to 1.")
        return True

    def get_transition_summary(self, n: int) -> None:
        """
        Print a human-readable summary of transition probabilities
        from state n under all actions.
        """
        print(f"Transition probabilities from state n={n}:")
        print(f"  Lambda = {self.Lambda}")
        for a_idx, mu in enumerate(self.model.mu_list):
            probs = {}
            if n > 0:
                probs[n - 1] = self.P[n, n - 1, a_idx]
            probs[n] = self.P[n, n, a_idx]
            if n < self.N:
                probs[n + 1] = self.P[n, n + 1, a_idx]
            total = sum(probs.values())
            prob_str = ", ".join(f"P({k}|{n})={v:.4f}" for k, v in sorted(probs.items()))
            print(f"  mu={mu}: {prob_str}  [sum={total:.6f}]")

    def __repr__(self):
        return (
            f"UniformMDP("
            f"N={self.N}, "
            f"n_actions={self.n_actions}, "
            f"Lambda={self.Lambda:.4f})"
        )


if __name__ == "__main__":
    # Baseline parameters agreed by the group
    model = CTMDPModel(
        lambda_=3,
        mu_list=[2, 4, 6],
        c_h=1,
        c_a_list=[0, 1, 3],
        N=50
    )

    mdp = UniformMDP(model)
    print(mdp)
    print(f"Lambda = {mdp.Lambda}")
    print()

    # Show transition probabilities from a few representative states
    for n in [0, 5, 25, 50]:
        mdp.get_transition_summary(n)
        print()

    # Show rescaled costs for n = 0..5
    print("Rescaled costs c_tilde[n, a] for n=0..5:")
    header = f"{'n':>4}" + "".join(f"  mu={mu}" for mu in model.mu_list)
    print(header)
    for n in range(6):
        row = f"{n:>4}"
        for a_idx in range(mdp.n_actions):
            row += f"  {mdp.c_tilde[n, a_idx]:.5f}"
        print(row)
    print()

    # Full row-sum verification
    mdp.verify_transition_rows()

    # Verify Lambda is a valid upper bound
    print()
    print("Lambda validity check:")
    max_rate = model.lambda_ + max(model.mu_list)
    print(f"  lambda + max(mu) = {model.lambda_} + {max(model.mu_list)} = {max_rate}")
    print(f"  Lambda = {mdp.Lambda}")
    print(f"  Lambda >= lambda + max(mu): {mdp.Lambda >= max_rate}")

    # Check that all self-loop probabilities are non-negative
    min_selfloop = min(
        mdp.P[n, n, a_idx]
        for n in range(mdp.N + 1)
        for a_idx in range(mdp.n_actions)
    )
    print(f"  Min self-loop probability: {min_selfloop:.6f} (must be >= 0)")
