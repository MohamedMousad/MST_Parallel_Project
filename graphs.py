import matplotlib.pyplot as plt

# --- YOUR BENCHMARK DATA ---
threads = [1, 2, 4, 6, 12]
times = [3.30, 1.74, 0.92, 0.65, 0.57]
speedup = [3.30/t for t in times]
ideal = [t for t in threads]

# --- GRAPH 1: Execution Time ---
plt.figure(figsize=(10, 6))
plt.plot(threads, times, marker='o', linestyle='-', color='#1f77b4', linewidth=2.5, label='Execution Time')
plt.axhline(y=3.30, color='r', linestyle='--', alpha=0.5, label='Serial Baseline (3.30s)')
plt.title('Execution Time vs Threads (10M Edges)', fontsize=14, fontweight='bold')
plt.xlabel('Number of Threads', fontsize=12)
plt.ylabel('Time (seconds)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.savefig('graph_time.png', dpi=300) # Saves high-quality image
print("Created graph_time.png")

# --- GRAPH 2: Speedup ---
plt.figure(figsize=(10, 6))
plt.plot(threads, ideal, linestyle='--', color='gray', alpha=0.7, label='Ideal Speedup (Linear)')
plt.plot(threads, speedup, marker='s', linestyle='-', color='#2ca02c', linewidth=2.5, label='Actual Speedup')
# Annotate the max speedup point
plt.annotate(f'Max: {speedup[-1]:.2f}x', 
             xy=(12, speedup[-1]), 
             xytext=(9, speedup[-1]-1),
             arrowprops=dict(facecolor='black', shrink=0.05))

plt.title('Parallel Speedup Analysis', fontsize=14, fontweight='bold')
plt.xlabel('Number of Threads', fontsize=12)
plt.ylabel('Speedup Factor (x)', fontsize=12)
plt.xticks(threads) # Show only relevant thread numbers
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.savefig('graph_speedup.png', dpi=300)
print("Created graph_speedup.png")