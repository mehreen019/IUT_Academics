def bisection(f, a, b, tol=1e-6):
    """Bisection method for finding root of f in [a, b].
    
    Args:
        f (function): Function to find root of.
        a (float): Lower bound for root.
        b (float): Upper bound for root.
        tol (float): Tolerance for root.
    
    Returns:
        float: Root of f in [a, b].
    """
    fa = f(a)
    fb = f(b)
    if fa * fb > 0:
        raise ValueError("Root must be bracketed by [a, b].")
    while b - a > tol:
        c = (a + b) / 2
        fc = f(c)
        if fa * fc < 0:
            b = c
            fb = fc
        else:
            a = c
            fa = fc
    return c

f = lambda x: x**2 - 2  # Example function
a = 0  # Lower bound for root
b = 1  # Upper bound for root
root = bisection(f, a, b)
print(f"Root of f(x) = x^2 - 2 in [{a}, {b}] is {root}.")