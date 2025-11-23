def secant_method(f, x0, x1, tol=1e-6, max_iter=100):
    """
    Secant Method for solving f(x) = 0
    Args:
        f: The function for which we want to find the root.
        x0, x1: Initial guesses.
        tol: Tolerance for stopping.
        max_iter: Maximum number of iterations.
    Returns:
        Approximate root or None if it doesn't converge.
    """
    for i in range(max_iter):
        if abs(f(x1) - f(x0)) < 1e-12:
            print("Denominator too small.")
            return None
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0))
        print(f"Iteration {i+1}: x = {x2}")
        if abs(x2 - x1) < tol:
            return x2
        x0, x1 = x1, x2
    print("Secant method did not converge.")
    return None


def false_position_method(f, a, b, tol=1e-6, max_iter=100):
    """
    False Position (Regula Falsi) Method for solving f(x) = 0
    Args:
        f: Function for which we are finding the root.
        a, b: Interval endpoints such that f(a) and f(b) have opposite signs.
        tol: Desired tolerance.
        max_iter: Max number of iterations.
    Returns:
        Approximate root or None.
    """
    if f(a) * f(b) >= 0:
        print("Function must have opposite signs at a and b.")
        return None

    for i in range(max_iter):
        c = b - f(b) * (b - a) / (f(b) - f(a))
        print(f"Iteration {i+1}: c = {c}")
        if abs(f(c)) < tol:
            return c
        elif f(a) * f(c) < 0:
            b = c
        else:
            a = c
    print("False position method did not converge.")
    return None
