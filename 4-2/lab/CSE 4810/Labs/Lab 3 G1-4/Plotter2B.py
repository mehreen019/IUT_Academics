import matplotlib.pyplot as plt
import math

# Initialize data vectors
alpha_vals, time_lp, time_dh, probes_lp, probes_dh = [], [], [], [], []

# Read and parse structural data columns
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

# Compute analytical baseline curves for a pristine clean table layout
theo_successful = [(1.0 / a) * math.log(1.0 / (1.0 - a)) for a in alpha_vals]

# Establish Subplot layouts
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 11))

# --- Subplot 1: Latency Metrics ---
ax1.plot(alpha_vals, time_lp, label='Linear Probing Search (With Deletions)', marker='o', color='purple', linewidth=1.5)
ax1.plot(alpha_vals, time_dh, label='Double Hashing Search (With Deletions)', marker='x', color='teal', linewidth=1.5)
ax1.set_title('Successful Search Execution Latency with Sentinel Pollution', fontsize=12, fontweight='bold')
ax1.set_xlabel('Active Load Factor (\u03B1)', fontsize=10)
ax1.set_ylabel('Execution Time (\u03BCs)', fontsize=10)
ax1.legend(loc='upper left')
ax1.grid(True, linestyle=':', alpha=0.6)

# --- Subplot 2: Probe Steps vs Theoretical Boundary ---
ax2.plot(alpha_vals, probes_lp, label='Empirical Linear Probing (Polluted)', marker='s', color='magenta', linewidth=2)
ax2.plot(alpha_vals, probes_dh, label='Empirical Double Hashing (Polluted)', marker='^', color='cyan', linewidth=2)
ax2.plot(alpha_vals, theo_successful, label='Theoretical Clean Boundary (No Deletions)', linestyle='--', color='black', linewidth=2)

ax2.set_title('Successful Search Probes with Sentinels vs. Theoretical Clean Limit', fontsize=12, fontweight='bold')
ax2.set_xlabel('Active Load Factor (\u03B1)', fontsize=10)
ax2.set_ylabel('Mean Probe Iterations Per Operation', fontsize=10)
ax2.legend(loc='upper left')
ax2.grid(True, linestyle=':', alpha=0.6)

plt.tight_layout()
plt.show()