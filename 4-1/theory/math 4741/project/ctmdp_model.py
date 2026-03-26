import numpy as np


class CTMDPModel:
    """
    Continuous-Time Markov Decision Process model for a single-server
    queue with controllable service rates.

    Parameters
    ----------
    lambda_    : float       Poisson arrival rate
    mu_list    : list[float] Available service rates [mu1, mu2, mu3]
    c_h        : float       Holding cost per customer per unit time
    c_a_list   : list[float] Staffing cost for each service rate action
    N          : int         State space truncation (states 0 .. N)
    """

    def __init__(self, lambda_: float, mu_list: list, c_h: float,
                 c_a_list: list, N: int = 50):
        assert len(mu_list) == len(c_a_list), (
            "mu_list and c_a_list must have the same length."
        )
        assert lambda_ > 0, "Arrival rate lambda must be positive."
        assert all(mu > 0 for mu in mu_list), "All service rates must be positive."
        assert N >= 1, "State space truncation N must be at least 1."

        self.lambda_ = lambda_
        self.mu_list = mu_list
        self.c_h = c_h
        self.c_a_list = c_a_list
        self.N = N
        self.n_states = N + 1
        self.n_actions = len(mu_list)

        self._check_stability()

    def _check_stability(self):
        """
        Warn if any action yields an unstable queue (rho >= 1).
        At least one action must be stable for the MDP to be well-posed.
        """
        stable_actions = []
        for i, mu in enumerate(self.mu_list):
            rho = self.lambda_ / mu
            if rho < 1.0:
                stable_actions.append(i)
            else:
                print(
                    f"Warning: Action {i} (mu={mu}) is unstable "
                    f"(rho={rho:.3f} >= 1). Queue will grow without bound."
                )
        if not stable_actions:
            raise ValueError(
                "No stable action found. At least one service rate "
                "must satisfy mu > lambda."
            )

    def cost(self, n: int, a_index: int) -> float:
        """
        One-step cost rate at state n under action a_index.

        c(n, a) = c_h * n + c_a(a)

        Parameters
        ----------
        n       : int   Queue length (state)
        a_index : int   Action index into mu_list

        Returns
        -------
        float : cost rate
        """
        return self.c_h * n + self.c_a_list[a_index]

    def transition_rate(self, n: int, n_prime: int, a_index: int) -> float:
        """
        Infinitesimal transition rate q(n, n', a) from state n to n'
        under action a_index.

        Rules
        -----
        q(n, n+1, a) = lambda       for n < N   (arrival)
        q(n, n-1, a) = mu(a)        for n >= 1  (departure)
        q(n, n,   a) = -(lambda + mu(a))         (diagonal, n >= 1)
        q(0, 0,   a) = -lambda                   (diagonal, n = 0)
        q(n, n',  a) = 0            for |n-n'| > 1

        Parameters
        ----------
        n       : int   Current state
        n_prime : int   Next state
        a_index : int   Action index

        Returns
        -------
        float : transition rate
        """
        mu = self.mu_list[a_index]
        lam = self.lambda_

        if n_prime == n + 1 and n < self.N:
            return lam
        elif n_prime == n - 1 and n >= 1:
            return mu
        elif n_prime == n:
            if n == 0:
                return -lam
            else:
                return -(lam + mu)
        else:
            return 0.0

    def get_all_rates(self) -> np.ndarray:
        """
        Build the full generator tensor Q of shape (N+1, N+1, n_actions).

        Q[n, n_prime, a] = q(n, n', a)

        The diagonal entries satisfy Q[n, n, a] = -sum_{n' != n} Q[n, n', a].

        Returns
        -------
        np.ndarray of shape (N+1, N+1, n_actions)
        """
        Q = np.zeros((self.n_states, self.n_states, self.n_actions))
        for a_idx in range(self.n_actions):
            for n in range(self.n_states):
                for n_prime in range(self.n_states):
                    Q[n, n_prime, a_idx] = self.transition_rate(n, n_prime, a_idx)
        return Q

    def __repr__(self):
        return (
            f"CTMDPModel("
            f"lambda={self.lambda_}, "
            f"mu_list={self.mu_list}, "
            f"c_h={self.c_h}, "
            f"c_a_list={self.c_a_list}, "
            f"N={self.N})"
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

    print(model)
    print()

    # Print cost table for n = 0..5, all actions
    print("Cost c(n, a) for n=0..5:")
    header = f"{'n':>4}" + "".join(f"  mu={mu}" for mu in model.mu_list)
    print(header)
    for n in range(6):
        row = f"{n:>4}"
        for a_idx in range(model.n_actions):
            row += f"  {model.cost(n, a_idx):>6.2f}"
        print(row)

    print()

    # Print generator matrix slice for action mu2 (index 1), states 0..5
    print("Generator matrix Q[:6, :6, action=mu2=4]:")
    Q = model.get_all_rates()
    slice_ = Q[:6, :6, 1]
    header = f"{'':>4}" + "".join(f"  n'={j}" for j in range(6))
    print(header)
    for n in range(6):
        row = f"n={n:>1}"
        for n_prime in range(6):
            row += f"  {slice_[n, n_prime]:>6.1f}"
        print(row)

    print()

    # Verify row sums of off-diagonal entries equal negative of diagonal
    print("Row sum check (should all be ~0.0):")
    for a_idx, mu in enumerate(model.mu_list):
        row_sums = Q[:, :, a_idx].sum(axis=1)
        max_err = np.abs(row_sums).max()
        print(f"  Action mu={mu}: max|row_sum| = {max_err:.2e}")
