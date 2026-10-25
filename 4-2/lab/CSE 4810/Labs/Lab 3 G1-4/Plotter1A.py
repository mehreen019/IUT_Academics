import matplotlib.pyplot as plt

# Initialize coordinate lists
alpha_vals, time_lp, time_dh, probes_lp, probes_dh = [], [], [], [], []

# Open and parse structural matrix columns
with open('data.txt', 'r') as f:
    for line in f:
        if line.startswith('#') or not line.strip():
            continue
        parts = line.split()
        alpha_vals.append(float(parts[0]))
        time_lp.append(float(parts[1]))
        time_dh.append(float(parts[2]))
        probes_lp.append(float(parts[3]))
        probes_dh.append(float(parts[4]))

# Compute analytical curve points based on Theorem 11.2 (Ideal Unsuccessful Bounds)
theo_unsuccessful = [1.0 / (1.0 - a) for a in alpha_vals]

# Establish Subplot layouts
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 11))

# --- Subplot 1: Latency Metrics ---
ax1.plot(alpha_vals, time_lp, label='Linear Probing Search Time', marker='o', color='red', linewidth=1.5)
ax1.plot(alpha_vals, time_dh, label='Double Hashing Search Time', marker='x', color='blue', linewidth=1.5)
ax1.set_title('Unsuccessful Search Execution Latency vs. Load Factor', fontsize=12, fontweight='bold')
ax1.set_xlabel('Load Factor (\u03B1)', fontsize=10)
ax1.set_ylabel('Execution Time (\u03BCs)', fontsize=10)
ax1.legend(loc='upper left')
ax1.grid(True, linestyle=':', alpha=0.6)

# --- Subplot 2: Probe Steps vs Theoretical Constraint Boundary ---
ax2.plot(alpha_vals, probes_lp, label='Empirical Linear Probing Probes', marker='s', color='green', linewidth=2)
ax2.plot(alpha_vals, probes_dh, label='Empirical Double Hashing Probes', marker='^', color='orange', linewidth=2)
ax2.plot(alpha_vals, theo_unsuccessful, label='Theoretical Uniform Boundary (1 / (1-\u03B1))', linestyle='--', color='black', linewidth=2)

ax2.set_title('Empirical Probe Step Trajectories vs. Theoretical Baseline Limit', fontsize=12, fontweight='bold')
ax2.set_xlabel('Load Factor (\u03B1)', fontsize=10)
ax2.set_ylabel('Mean Probe Iterations Per Operation', fontsize=10)
ax2.legend(loc='upper left')
ax2.grid(True, linestyle=':', alpha=0.6)

plt.tight_layout()
plt.show()