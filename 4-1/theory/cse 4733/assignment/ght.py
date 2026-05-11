"""
Generalized Hough Transform (Ballard, 1981)
==========================================
Run with:  python ght.py

Change the INPUT_IMAGE variable below to switch between images.
Available:
  'dowels'    -> Fig0941_a__wood_dowels_.tif   (detect all circular dowels)
  'rose'      -> Fig0219_rose1024_.tif         (detect petal/circular pattern)
  'noisy_rect'-> FigP0917_noisy_rectangle_.tif (detect noisy rectangle)

The script also generates all figures used in the tutorial note.
"""

import cv2
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from collections import defaultdict
import os

# =============================================================================
# USER SETTING: change this to 'dowels', 'rose', 'noisy_rect', or 'septagon'
# =============================================================================
INPUT_IMAGE = 'dowels'
# =============================================================================

IMAGE_PATHS = {
    'dowels':     './Fig0941(a)(wood_dowels).tif',
    'rose':       './Fig0219(rose1024).tif',
    'noisy_rect': './FigP0917(noisy_rectangle).tif',
    'septagon':   './Fig1036(a)(original_septagon).tif',
}

OUTPUT_DIR = 'figures'
os.makedirs(OUTPUT_DIR, exist_ok=True)

# ---------------------------------------------------------------------------
# Utility helpers
# ---------------------------------------------------------------------------

def load_gray(path):
    """Load image as uint8 grayscale."""
    img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
    if img is None:
        raise FileNotFoundError(f"Cannot open image: {path}")
    return img


def compute_edges_and_gradients(img, canny_lo=50, canny_hi=150):
    """Return edge mask, gradient angles (radians), and gradient magnitudes."""
    blurred = cv2.GaussianBlur(img, (5, 5), 1)
    edges   = cv2.Canny(blurred, canny_lo, canny_hi)
    Gx = cv2.Sobel(blurred, cv2.CV_64F, 1, 0, ksize=3)
    Gy = cv2.Sobel(blurred, cv2.CV_64F, 0, 1, ksize=3)
    angles = np.arctan2(Gy, Gx)          # radians in [-pi, pi]
    magnitudes = np.sqrt(Gx**2 + Gy**2)
    return edges, angles, magnitudes


# ---------------------------------------------------------------------------
# R-Table construction  (offline / training phase)
# ---------------------------------------------------------------------------

def build_r_table(template_gray, n_bins=72, canny_lo=50, canny_hi=150):
    """
    Build the R-Table from a template image.

    Parameters
    ----------
    template_gray : ndarray  (H x W, uint8)
    n_bins        : int      number of gradient-angle quantisation bins
    canny_lo/hi   : int      Canny thresholds

    Returns
    -------
    r_table : dict  {bin_index -> list of (rx, ry) displacement vectors}
    ref_pt  : (xref, yref)   reference point (centroid of edge pixels)
    """
    edges, angles, _ = compute_edges_and_gradients(template_gray, canny_lo, canny_hi)

    ys, xs = np.where(edges > 0)
    if len(xs) == 0:
        raise ValueError("No edges found in template!")

    xref = int(np.mean(xs))
    yref = int(np.mean(ys))

    r_table = defaultdict(list)
    bin_width = 2 * np.pi / n_bins

    for x, y in zip(xs, ys):
        phi   = angles[y, x]                          # gradient angle at this pixel
        b     = int((phi + np.pi) / bin_width) % n_bins  # quantised bin
        rx    = xref - x                               # displacement to reference
        ry    = yref - y
        r_table[b].append((rx, ry))

    return dict(r_table), (xref, yref)


# ---------------------------------------------------------------------------
# Voting  (online / detection phase)
# ---------------------------------------------------------------------------

def ght_vote(test_gray, r_table, n_bins=72, canny_lo=50, canny_hi=150):
    """
    Cast votes in a 2-D accumulator for each edge pixel.

    Returns
    -------
    accumulator : ndarray (H x W) of int32
    edges       : edge map of the test image
    angles      : gradient angle map
    """
    H, W = test_gray.shape
    accumulator = np.zeros((H, W), dtype=np.int32)

    edges, angles, _ = compute_edges_and_gradients(test_gray, canny_lo, canny_hi)
    ys, xs = np.where(edges > 0)

    bin_width = 2 * np.pi / n_bins

    for x, y in zip(xs, ys):
        phi = angles[y, x]
        b   = int((phi + np.pi) / bin_width) % n_bins
        if b not in r_table:
            continue
        for rx, ry in r_table[b]:
            xv = x + rx
            yv = y + ry
            if 0 <= xv < W and 0 <= yv < H:
                accumulator[yv, xv] += 1

    return accumulator, edges, angles


def smooth_and_find_peaks(accumulator, sigma=3, threshold_ratio=0.5):
    """
    Gaussian-smooth the accumulator and find all local maxima above threshold.

    Returns list of (x, y, vote_count) sorted descending by vote count.
    """
    smoothed = cv2.GaussianBlur(accumulator.astype(np.float32),
                                (0, 0), sigma)
    max_val = smoothed.max()
    thresh  = threshold_ratio * max_val

    # local-max filter: a cell is a peak if it equals the max in a 15x15 window
    from scipy.ndimage import maximum_filter
    local_max = (maximum_filter(smoothed, size=15) == smoothed)
    peaks_mask = local_max & (smoothed >= thresh)

    ys, xs = np.where(peaks_mask)
    peaks  = [(int(x), int(y), float(smoothed[y, x]))
              for x, y in zip(xs, ys)]
    peaks.sort(key=lambda p: -p[2])
    return peaks, smoothed


# ---------------------------------------------------------------------------
# Overlay helper
# ---------------------------------------------------------------------------

def overlay_shape(base_bgr, template_gray, detected_ref, template_ref):
    """
    Draw the template shape centred at detected_ref on base_bgr.
    Returns a copy with green contour and red reference dot.
    """
    result = base_bgr.copy()
    H, W  = template_gray.shape
    edges = cv2.Canny(cv2.GaussianBlur(template_gray, (5,5), 1), 50, 150)
    ys, xs = np.where(edges > 0)

    dx = detected_ref[0] - template_ref[0]
    dy = detected_ref[1] - template_ref[1]

    rH, rW = result.shape[:2]
    for tx, ty in zip(xs, ys):
        nx, ny = tx + dx, ty + dy
        if 0 <= nx < rW and 0 <= ny < rH:
            result[ny, nx] = (0, 200, 0)          # green

    cx, cy = detected_ref
    if 0 <= cx < rW and 0 <= cy < rH:
        cv2.circle(result, (cx, cy), 5, (0, 0, 220), -1)  # red dot
    return result


# =============================================================================
# FIGURE GENERATORS
# =============================================================================

# ---------------------------------------------------------------------------
# Figure 1 — Algorithm flowchart  (clean SVG-style via matplotlib)
# ---------------------------------------------------------------------------

def make_figure1():
    fig, ax = plt.subplots(figsize=(9, 5.5))
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 6)
    ax.axis('off')

    def box(ax, x, y, w, h, text, facecolor='#dce8f5', edgecolor='#2a6099', fontsize=9):
        rect = mpatches.FancyBboxPatch((x - w/2, y - h/2), w, h,
            boxstyle='round,pad=0.1', facecolor=facecolor,
            edgecolor=edgecolor, linewidth=1.4, zorder=3)
        ax.add_patch(rect)
        ax.text(x, y, text, ha='center', va='center', fontsize=fontsize,
                fontfamily='monospace', zorder=4, wrap=True,
                multialignment='center')

    def arrow(ax, x1, y1, x2, y2):
        ax.annotate('', xy=(x2, y2), xytext=(x1, y1),
            arrowprops=dict(arrowstyle='->', color='#555', lw=1.4), zorder=2)

    # --- OFFLINE (left column, x=2.5)
    ax.text(2.5, 5.65, 'OFFLINE  (Training)', ha='center', fontsize=10,
            fontweight='bold', color='#2a6099')
    box(ax, 2.5, 5.1,  3.2, 0.55, 'Prototype image')
    arrow(ax, 2.5, 4.82, 2.5, 4.48)
    box(ax, 2.5, 4.2,  3.2, 0.55, 'Edge detection (Canny)')
    arrow(ax, 2.5, 3.92, 2.5, 3.58)
    box(ax, 2.5, 3.3,  3.2, 0.55, 'Gradient orientation (Sobel)')
    arrow(ax, 2.5, 3.02, 2.5, 2.68)
    box(ax, 2.5, 2.4,  3.2, 0.55, 'Choose reference point')
    arrow(ax, 2.5, 2.12, 2.5, 1.78)
    box(ax, 2.5, 1.5,  3.2, 0.55, 'Build R-Table\n(φ → r-vectors)')

    # --- ONLINE (right column, x=7.5)
    ax.text(7.5, 5.65, 'ONLINE  (Detection)', ha='center', fontsize=10,
            fontweight='bold', color='#b05000')
    box(ax, 7.5, 5.1,  3.2, 0.55, 'Test image', facecolor='#fde8d0', edgecolor='#b05000')
    arrow(ax, 7.5, 4.82, 7.5, 4.48)
    box(ax, 7.5, 4.2,  3.2, 0.55, 'Edge detection (Canny)', facecolor='#fde8d0', edgecolor='#b05000')
    arrow(ax, 7.5, 3.92, 7.5, 3.58)
    box(ax, 7.5, 3.3,  3.2, 0.55, 'Gradient orientation (Sobel)', facecolor='#fde8d0', edgecolor='#b05000')
    arrow(ax, 7.5, 3.02, 7.5, 2.68)
    box(ax, 7.5, 2.4,  3.2, 0.55, 'Vote casting\n(R-Table lookup)', facecolor='#fde8d0', edgecolor='#b05000')
    arrow(ax, 7.5, 2.12, 7.5, 1.78)
    box(ax, 7.5, 1.5,  3.2, 0.55, 'Peak detection', facecolor='#fde8d0', edgecolor='#b05000')

    # R-table shared arrow
    arrow(ax, 3.5+0.7, 1.5, 6.1, 1.5)
    ax.text(5.0, 1.62, 'R-Table', ha='center', fontsize=8.5, style='italic')

    # Bottom result
    arrow(ax, 7.5, 1.22, 7.5, 0.72)
    box(ax, 7.5, 0.45,  3.2, 0.55, 'Detected shape location', facecolor='#d5f0d5', edgecolor='#1a7a1a')

    plt.tight_layout()
    path = f'{OUTPUT_DIR}/fig1_flowchart.png'
    plt.savefig(path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f'  Saved {path}')
    return path


# ---------------------------------------------------------------------------
# Figure 2 — R-table visualisation on a circle template
# ---------------------------------------------------------------------------

def make_figure2():
    # Create a clean circle template
    sz = 200
    template = np.zeros((sz, sz), dtype=np.uint8)
    cv2.circle(template, (100, 100), 55, 255, 2)

    r_table, (xref, yref) = build_r_table(template, n_bins=36)

    # Sample 6 distinct bins for illustration
    edges, angles, _ = compute_edges_and_gradients(template, 50, 150)
    ys, xs = np.where(edges > 0)

    bin_width = 2 * np.pi / 36
    sample_bins = [0, 6, 12, 18, 24, 30]
    colors = ['#e6194b','#3cb44b','#4363d8','#f58231','#911eb4','#42d4f4']

    fig, axes = plt.subplots(1, 2, figsize=(11, 4.5))

    # Left: show r-vectors from sample pixels to reference
    ax = axes[0]
    ax.imshow(template, cmap='gray', vmin=0, vmax=255)
    ax.plot(xref, yref, 'w+', ms=14, mew=2)

    plotted = {b: False for b in sample_bins}
    for x, y in zip(xs, ys):
        phi = angles[y, x]
        b   = int((phi + np.pi) / bin_width) % 36
        if b in sample_bins and not plotted[b]:
            c = colors[sample_bins.index(b)]
            ax.annotate('', xy=(xref, yref), xytext=(x, y),
                arrowprops=dict(arrowstyle='->', color=c, lw=1.5))
            ax.plot(x, y, 'o', color=c, ms=5)
            plotted[b] = True

    ax.set_title('(a) r-vectors from boundary pixels\nto reference point (white +)', fontsize=9)
    ax.axis('off')
    legend_patches = [mpatches.Patch(color=colors[i],
        label=f'Bin {sample_bins[i]}') for i in range(len(sample_bins))]
    ax.legend(handles=legend_patches, fontsize=7.5, loc='lower right',
              framealpha=0.7)

    # Right: R-Table bar chart (entry count per bin)
    ax2 = axes[1]
    bins_list  = sorted(r_table.keys())
    entry_cnts = [len(r_table[b]) for b in bins_list]
    bar_colors = ['#4a90c4'] * len(bins_list)
    for sb, sc in zip(sample_bins, colors):
        if sb in bins_list:
            bar_colors[bins_list.index(sb)] = sc
    ax2.bar(bins_list, entry_cnts, color=bar_colors, edgecolor='none', width=0.8)
    ax2.set_xlabel('Gradient-angle bin index (0 = −180°, 35 = +170°)', fontsize=8)
    ax2.set_ylabel('Number of r-vectors', fontsize=8)
    ax2.set_title('(b) R-Table: entry count per gradient-angle bin', fontsize=9)
    ax2.tick_params(labelsize=8)

    plt.tight_layout()
    path = f'{OUTPUT_DIR}/fig2_rtable.png'
    plt.savefig(path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f'  Saved {path}')
    return path


# ---------------------------------------------------------------------------
# Figure 3 — Step-by-step on FigP0917 (noisy rectangle)
# ---------------------------------------------------------------------------

def make_figure3_noisy_rect():
    """
    Use the noisy rectangle as template AND test image.
    Show: input, edges, gradient map, raw accumulator,
          smoothed accumulator with peak, detection overlay.
    """
    img_path = IMAGE_PATHS['noisy_rect']
    raw = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
    # Binary image: convert to uint8 properly
    if raw is None:
        from PIL import Image as PILImage
        import numpy as _np
        pil = PILImage.open(img_path)
        raw = (_np.array(pil).astype(np.uint8)) * 255

    # Resize to manageable size
    scale = 0.4
    img = cv2.resize(raw, (0, 0), fx=scale, fy=scale)

    r_table, (xref, yref) = build_r_table(img, n_bins=72, canny_lo=30, canny_hi=100)
    acc, edges, angles     = ght_vote(img, r_table, n_bins=72, canny_lo=30, canny_hi=100)
    peaks, smoothed        = smooth_and_find_peaks(acc, sigma=5, threshold_ratio=0.7)

    fig, axes = plt.subplots(2, 3, figsize=(13, 7))
    axes = axes.ravel()

    axes[0].imshow(img, cmap='gray'); axes[0].set_title('(1) Input image'); axes[0].axis('off')
    axes[1].imshow(edges, cmap='gray'); axes[1].set_title('(2) Canny edge map'); axes[1].axis('off')

    # Gradient orientation (HSV-coloured at edge pixels)
    angle_disp = np.full((*img.shape, 3), 30, dtype=np.uint8)  # dark background
    edge_ys, edge_xs = np.where(edges > 0)
    hues = ((angles[edge_ys, edge_xs] + np.pi) / (2*np.pi) * 180).astype(np.uint8)
    hsv_img = np.zeros((*img.shape, 3), dtype=np.uint8)
    hsv_img[:, :, 1] = 255; hsv_img[:, :, 2] = 0
    for ey, ex, h in zip(edge_ys, edge_xs, hues):
        hsv_img[ey, ex] = [h, 230, 210]
    grad_bgr = cv2.cvtColor(hsv_img, cv2.COLOR_HSV2BGR)
    axes[2].imshow(cv2.cvtColor(grad_bgr, cv2.COLOR_BGR2RGB))
    axes[2].set_title('(3) Gradient orientation\n(hue = angle, at edge pixels)'); axes[2].axis('off')

    axes[3].imshow(acc, cmap='hot'); axes[3].set_title('(4) Raw accumulator'); axes[3].axis('off')

    axes[4].imshow(smoothed, cmap='hot')
    if peaks:
        px, py, pv = peaks[0]
        axes[4].plot(px, py, 'c*', ms=12)
        axes[4].axhline(py, color='cyan', lw=0.6, alpha=0.6)
        axes[4].axvline(px, color='cyan', lw=0.6, alpha=0.6)
    axes[4].set_title('(5) Smoothed accumulator\nwith detected peak (★)'); axes[4].axis('off')

    img_bgr = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
    if peaks:
        px, py, _ = peaks[0]
        result = overlay_shape(img_bgr, img, (px, py), (xref, yref))
        axes[5].imshow(cv2.cvtColor(result, cv2.COLOR_BGR2RGB))
    else:
        axes[5].imshow(img, cmap='gray')
    axes[5].set_title('(6) Detection overlay\n(green = shape, red = reference)'); axes[5].axis('off')

    plt.tight_layout()
    path = f'{OUTPUT_DIR}/fig3_noisy_rect_steps.png'
    plt.savefig(path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f'  Saved {path}')
    return path, peaks, img.shape


# ---------------------------------------------------------------------------
# Figure 4 — GHT on Fig0941 (wood dowels) — detect ALL dowels
# ---------------------------------------------------------------------------

def build_circle_rtable_scaled(radius, n_bins=72):
    """Build an R-table from a circular template of the given radius."""
    sz = radius * 2 + 20
    tmpl = np.zeros((sz, sz), dtype=np.uint8)
    cx, cy = sz // 2, sz // 2
    cv2.circle(tmpl, (cx, cy), radius, 255, 2)
    edges, angles, _ = compute_edges_and_gradients(tmpl)
    ys, xs = np.where(edges > 0)
    r_table = defaultdict(list)
    bw = 2 * np.pi / n_bins
    for x, y in zip(xs, ys):
        b = int((angles[y, x] + np.pi) / bw) % n_bins
        r_table[b].append((cx - x, cy - y))
    return dict(r_table), len(xs)


def make_figure4_dowels():
    """
    Multi-scale GHT for Fig0941 (wood dowels).
    Dowels range from radius ~18 to ~50 px, so a single template misses most sizes.
    Nine R-tables are built (r = 18, 22, ..., 50) and their normalised accumulators
    are combined by pointwise maximum (scale-max accumulator), implementing the
    scale-extended GHT described by Ballard (1981).
    """
    img_path = IMAGE_PATHS['dowels']
    img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)

    # --- Multi-scale R-table voting ---
    RADII      = [18, 22, 26, 30, 34, 38, 42, 46, 50]
    scale_accs = {}
    edges_map  = None

    for r in RADII:
        rt, n_edge = build_circle_rtable_scaled(r)
        # Use ght_vote to reuse the shared voting engine
        acc_raw, edges, _ = ght_vote(img, rt, n_bins=72)
        if edges_map is None:
            edges_map = edges
        # Normalise by template edge count; smooth with radius-adaptive sigma
        acc_norm      = acc_raw.astype(np.float32) / max(n_edge, 1)
        sigma         = max(3, r // 8)
        scale_accs[r] = cv2.GaussianBlur(acc_norm, (0, 0), sigma)

    # Combine: pointwise max across all scales
    stack    = np.stack([scale_accs[r] for r in RADII], axis=0)
    combined = stack.max(axis=0)   # shape (H, W)

    # Peak detection on combined accumulator
    from scipy.ndimage import maximum_filter as _mf
    thresh = 0.28 * combined.max()
    lmax   = (_mf(combined, size=32) == combined) & (combined >= thresh)
    ys_p, xs_p = np.where(lmax)
    peaks  = sorted(zip(xs_p.tolist(), ys_p.tolist(), combined[ys_p, xs_p].tolist()),
                    key=lambda p: -p[2])

    # Radius-aware NMS: keep peaks separated by at least (r1+r2)*0.65
    def best_r(px, py):
        return max(RADII, key=lambda r: scale_accs[r][py, px])

    detected = []
    for px, py, pv in peaks:
        r_here = best_r(px, py)
        ok = all(
            np.sqrt((px - qx)**2 + (py - qy)**2) > (r_here + qr) * 0.65
            for (qx, qy, qr) in detected
        )
        if ok:
            detected.append((px, py, r_here))

    # Overlay on original image
    overlay = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
    for px, py, r in detected:
        cv2.circle(overlay, (px, py), r,  (0, 210, 0), 2)
        cv2.circle(overlay, (px, py), 3,  (0, 0, 220), -1)

    fig, axes = plt.subplots(1, 4, figsize=(18, 5.5))

    axes[0].imshow(img, cmap='gray')
    axes[0].set_title('(a) Fig0941: wood dowels\n(original)', fontsize=9)
    axes[0].axis('off')

    axes[1].imshow(edges_map, cmap='gray')
    axes[1].set_title('(b) Canny edge map', fontsize=9)
    axes[1].axis('off')

    axes[2].imshow(combined, cmap='hot')
    for px, py, _ in detected:
        axes[2].plot(px, py, 'c.', ms=4)
    axes[2].set_title(f'(c) Multi-scale accumulator\n({len(detected)} peaks detected)', fontsize=9)
    axes[2].axis('off')

    axes[3].imshow(cv2.cvtColor(overlay, cv2.COLOR_BGR2RGB))
    axes[3].set_title(f'(d) All detections overlaid\n({len(detected)} dowels, variable radius)', fontsize=9)
    axes[3].axis('off')

    plt.tight_layout()
    path = f'{OUTPUT_DIR}/fig4_dowels.png'
    plt.savefig(path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f'  Saved {path}')
    return path, len(detected), detected


# ---------------------------------------------------------------------------
# Figure 5 — GHT on Fig0219 (rose) — robustness / shape detection
# ---------------------------------------------------------------------------

def make_figure5_rose():
    """
    Detect the roughly circular flower head in the rose image.
    Layout: 2 rows x 4 cols
      Row 1 (clean):  original | edge map | accumulator | detection overlay
      Row 2 (noisy):  noisy    | edge map | accumulator | detection overlay
    """
    img_path = IMAGE_PATHS['rose']
    img_full = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
    img      = img_full[200:800, 200:800]   # 600x600 centre crop

    FLOWER_RADIUS = 180
    tsz      = FLOWER_RADIUS * 2 + 20
    template = np.zeros((tsz, tsz), dtype=np.uint8)
    cv2.circle(template, (tsz//2, tsz//2), FLOWER_RADIUS, 255, 2)

    r_table, (xref, yref) = build_r_table(template, n_bins=72)
    acc, edges, _          = ght_vote(img, r_table, n_bins=72)
    peaks, smoothed        = smooth_and_find_peaks(acc, sigma=8, threshold_ratio=0.6)

    # Noisy version (fixed seed for reproducibility)
    rng       = np.random.RandomState(42)
    noise     = rng.normal(0, 30, img.shape).astype(np.int16)
    img_noisy = np.clip(img.astype(np.int16) + noise, 0, 255).astype(np.uint8)
    acc_n, edges_n, _ = ght_vote(img_noisy, r_table, n_bins=72)
    peaks_n, smooth_n = smooth_and_find_peaks(acc_n, sigma=8, threshold_ratio=0.6)

    # Detection overlays
    overlay   = cv2.cvtColor(img,       cv2.COLOR_GRAY2BGR)
    overlay_n = cv2.cvtColor(img_noisy, cv2.COLOR_GRAY2BGR)
    if peaks:
        px, py, _ = peaks[0]
        cv2.circle(overlay, (px, py), FLOWER_RADIUS, (0, 210, 0), 3)
        cv2.circle(overlay, (px, py), 5, (0, 0, 220), -1)
    if peaks_n:
        pxn, pyn, _ = peaks_n[0]
        cv2.circle(overlay_n, (pxn, pyn), FLOWER_RADIUS, (0, 210, 0), 3)
        cv2.circle(overlay_n, (pxn, pyn), 5, (0, 0, 220), -1)

    fig, axes = plt.subplots(2, 4, figsize=(16, 8))

    # Row 1 — clean
    axes[0,0].imshow(img, cmap='gray')
    axes[0,0].set_title('(a) Fig0219: rose (cropped)', fontsize=9); axes[0,0].axis('off')
    axes[0,1].imshow(edges, cmap='gray')
    axes[0,1].set_title('(b) Canny edge map', fontsize=9); axes[0,1].axis('off')
    axes[0,2].imshow(smoothed, cmap='hot')
    if peaks:
        px, py, _ = peaks[0]
        axes[0,2].plot(px, py, 'c*', ms=12)
        axes[0,2].axhline(py, color='c', lw=0.6, alpha=0.7)
        axes[0,2].axvline(px, color='c', lw=0.6, alpha=0.7)
    axes[0,2].set_title('(c) Smoothed accumulator\n(clean image)', fontsize=9); axes[0,2].axis('off')
    axes[0,3].imshow(cv2.cvtColor(overlay, cv2.COLOR_BGR2RGB))
    axes[0,3].set_title('(d) Detection overlay\n(green circle, red centre)', fontsize=9); axes[0,3].axis('off')

    # Row 2 — noisy
    axes[1,0].imshow(img_noisy, cmap='gray')
    axes[1,0].set_title('(e) Rose + Gaussian noise (\u03c3=30)', fontsize=9); axes[1,0].axis('off')
    axes[1,1].imshow(edges_n, cmap='gray')
    axes[1,1].set_title('(f) Noisy edge map', fontsize=9); axes[1,1].axis('off')
    axes[1,2].imshow(smooth_n, cmap='hot')
    if peaks_n:
        pxn, pyn, _ = peaks_n[0]
        axes[1,2].plot(pxn, pyn, 'c*', ms=12)
        axes[1,2].axhline(pyn, color='c', lw=0.6, alpha=0.7)
        axes[1,2].axvline(pxn, color='c', lw=0.6, alpha=0.7)
    axes[1,2].set_title('(g) Smoothed accumulator\n(noisy image)', fontsize=9); axes[1,2].axis('off')
    axes[1,3].imshow(cv2.cvtColor(overlay_n, cv2.COLOR_BGR2RGB))
    axes[1,3].set_title('(h) Detection overlay\n(noisy image)', fontsize=9); axes[1,3].axis('off')

    plt.tight_layout()
    path = f'{OUTPUT_DIR}/fig5_rose.png'
    plt.savefig(path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f'  Saved {path}')
    return path, peaks, peaks_n


# ---------------------------------------------------------------------------
# Figure — GHT on Fig1036 (septagon) — irregular polygon detection
# ---------------------------------------------------------------------------

def make_figure_septagon():
    """
    Detect the irregular seven-sided polygon in Fig1036 (septagon).
    The image is used as both template and test image (self-referential,
    same strategy as the noisy rectangle).
    Shows all 6 intermediate steps matching the noisy_rect layout.
    """
    img_path = IMAGE_PATHS['septagon']
    img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)

    # Build R-table from the septagon itself
    r_table, (xref, yref) = build_r_table(img, n_bins=72, canny_lo=30, canny_hi=100)
    acc, edges, angles     = ght_vote(img, r_table, n_bins=72, canny_lo=30, canny_hi=100)
    peaks, smoothed        = smooth_and_find_peaks(acc, sigma=5, threshold_ratio=0.6)

    # Gradient orientation map (hue-coded at edge pixels)
    ys_e, xs_e = np.where(edges > 0)
    hsv_img    = np.zeros((*img.shape, 3), dtype=np.uint8)
    hues       = ((angles[ys_e, xs_e] + np.pi) / (2*np.pi) * 180).astype(np.uint8)
    for ey, ex, h in zip(ys_e, xs_e, hues):
        hsv_img[ey, ex] = [h, 230, 210]
    grad_bgr = cv2.cvtColor(hsv_img, cv2.COLOR_HSV2BGR)

    # Detection overlay: project template edges at detected reference
    overlay = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
    if peaks:
        px, py, _ = peaks[0]
        dx, dy    = px - xref, py - yref
        H, W      = img.shape
        # Re-extract template edges for projection
        tmpl_edges, _, _ = compute_edges_and_gradients(img, canny_lo=30, canny_hi=100)
        ys_t, xs_t = np.where(tmpl_edges > 0)
        for tx, ty in zip(xs_t, ys_t):
            nx, ny = tx + dx, ty + dy
            if 0 <= nx < W and 0 <= ny < H:
                overlay[ny, nx] = (0, 210, 0)
        cv2.circle(overlay, (px, py), 6, (0, 0, 220), -1)

    fig, axes = plt.subplots(2, 3, figsize=(14, 8))
    axes = axes.ravel()

    axes[0].imshow(img, cmap='gray')
    axes[0].set_title('(1) Input: Fig1036 (septagon)', fontsize=9); axes[0].axis('off')

    axes[1].imshow(edges, cmap='gray')
    axes[1].set_title('(2) Canny edge map', fontsize=9); axes[1].axis('off')

    axes[2].imshow(cv2.cvtColor(grad_bgr, cv2.COLOR_BGR2RGB))
    axes[2].set_title('(3) Gradient orientation\n(hue = angle, at edge pixels)', fontsize=9); axes[2].axis('off')

    axes[3].imshow(acc, cmap='hot')
    axes[3].set_title('(4) Raw accumulator', fontsize=9); axes[3].axis('off')

    axes[4].imshow(smoothed, cmap='hot')
    if peaks:
        px, py, _ = peaks[0]
        axes[4].plot(px, py, 'c*', ms=14)
        axes[4].axhline(py, color='cyan', lw=0.6, alpha=0.6)
        axes[4].axvline(px, color='cyan', lw=0.6, alpha=0.6)
    axes[4].set_title('(5) Smoothed accumulator\nwith detected peak (\u2605)', fontsize=9); axes[4].axis('off')

    axes[5].imshow(cv2.cvtColor(overlay, cv2.COLOR_BGR2RGB))
    axes[5].set_title('(6) Detection overlay\n(green = shape, red = reference)', fontsize=9); axes[5].axis('off')

    plt.tight_layout()
    path = f'{OUTPUT_DIR}/fig_septagon_steps.png'
    plt.savefig(path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f'  Saved {path}')
    if peaks:
        px, py, pv = peaks[0]
        print(f'    Detected reference: ({px},{py}), template ref: ({xref},{yref}), votes={pv:.0f}')
    return path, peaks
# Figure 6 — Voting diagram (illustrative, with a small circle)
# ---------------------------------------------------------------------------

def make_figure6_voting():
    sz = 180
    template = np.zeros((sz, sz), dtype=np.uint8)
    cv2.circle(template, (90, 90), 50, 255, 2)

    _, (xref, yref) = build_r_table(template, n_bins=36)

    fig, axes = plt.subplots(1, 3, figsize=(12, 4))

    # (a) gradient arrows at edge pixels
    edges, angles, mags = compute_edges_and_gradients(template, 50, 150)
    ys, xs = np.where(edges > 0)
    ax = axes[0]
    ax.imshow(template, cmap='gray')
    step = max(1, len(xs) // 30)
    for x, y in zip(xs[::step], ys[::step]):
        phi = angles[y, x]
        ax.annotate('', xy=(x + 14*np.cos(phi), y + 14*np.sin(phi)),
            xytext=(x, y),
            arrowprops=dict(arrowstyle='->', color='#ff6600', lw=1.2))
    ax.plot(xref, yref, 'w+', ms=12, mew=2)
    ax.set_title('(a) Gradient arrows at\nedge pixels (→ outward)', fontsize=9)
    ax.axis('off')

    # (b) angle bins visualisation
    ax2 = axes[1]
    theta = np.linspace(0, 2*np.pi, 200)
    n_bins = 36
    cmap36 = plt.cm.hsv(np.linspace(0, 1, n_bins))
    for bi in range(n_bins):
        t0 = -np.pi + bi * (2*np.pi / n_bins)
        t1 = t0 + (2*np.pi / n_bins)
        t_range = np.linspace(t0, t1, 10)
        x_arc = 90 + 55 * np.cos(t_range)
        y_arc = 90 + 55 * np.sin(t_range)
        ax2.plot(x_arc, y_arc, color=cmap36[bi], lw=4, solid_capstyle='butt')
    ax2.plot(xref, yref, 'k+', ms=12, mew=2)
    ax2.set_xlim(20, 160); ax2.set_ylim(20, 160)
    ax2.set_aspect('equal')
    ax2.set_title('(b) Gradient-angle bins\n(colour = bin index)', fontsize=9)
    ax2.axis('off')

    # (c) single pixel voting
    ax3 = axes[2]
    acc_small = np.zeros((sz, sz), dtype=np.int32)
    r_table, _ = build_r_table(template, n_bins=36)
    bin_width  = 2*np.pi / 36
    # pick a handful of pixels and show their votes
    sample = list(zip(xs[::step], ys[::step]))[:8]
    vote_pts = []
    for x, y in sample:
        phi = angles[y, x]
        b   = int((phi + np.pi) / bin_width) % 36
        if b in r_table:
            for rx, ry in r_table[b]:
                xv, yv = x+rx, y+ry
                if 0<=xv<sz and 0<=yv<sz:
                    acc_small[yv, xv] += 1
                    vote_pts.append((xv, yv))

    ax3.imshow(acc_small, cmap='Blues')
    ax3.plot([p[0] for p in sample], [p[1] for p in sample],
             'r.', ms=6, label='Edge pixels')
    ax3.plot(xref, yref, 'y*', ms=14, label='Reference')
    ax3.set_title('(c) Votes from 8 edge pixels;\ntrue reference receives max', fontsize=9)
    ax3.legend(fontsize=7.5, loc='lower right')
    ax3.axis('off')

    plt.tight_layout()
    path = f'{OUTPUT_DIR}/fig6_voting.png'
    plt.savefig(path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f'  Saved {path}')
    return path


# =============================================================================
# MAIN
# =============================================================================

if __name__ == '__main__':
    from scipy.ndimage import maximum_filter   # confirm scipy available

    print('=' * 55)
    print('Generalized Hough Transform — Figure Generator')
    print('=' * 55)
    print(f'Active input image: {INPUT_IMAGE}')
    print()

    print('[1/7] Generating Figure 1: algorithm flowchart ...')
    make_figure1()

    print('[2/7] Generating Figure 2: R-table visualisation ...')
    make_figure2()

    print('[3/7] Generating Figure 3: step-by-step on noisy rectangle ...')
    path3, peaks3, shape3 = make_figure3_noisy_rect()
    if peaks3:
        px3, py3, pv3 = peaks3[0]
        print(f'       Detected reference at ({px3}, {py3}),  votes = {pv3:.0f}')
    else:
        print('       No peak found.')

    print('[4/7] Generating Figure 4: all dowels detection ...')
    path4, n_dowels, peaks4 = make_figure4_dowels()
    print(f'       {n_dowels} dowels detected')

    print('[5/7] Generating Figure 5: septagon irregular polygon ...')
    path5s, peaks5s = make_figure_septagon()

    print('[6/7] Generating Figure 6: rose robustness test ...')
    path5, peaks5, peaks5n = make_figure5_rose()
    if peaks5:
        print(f'       Clean: peak at ({peaks5[0][0]}, {peaks5[0][1]})')
    if peaks5n:
        print(f'       Noisy: peak at ({peaks5n[0][0]}, {peaks5n[0][1]})')

    print('[7/7] Generating Figure 7: voting mechanism diagram ...')
    make_figure6_voting()

    print()
    print(f'All figures saved to ./{OUTPUT_DIR}/')
    print()
    print('To run GHT on a specific image, change INPUT_IMAGE at the top of ght.py.')
    print('Available options: dowels, rose, noisy_rect, septagon')
