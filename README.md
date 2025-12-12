# ⚡ Parallel Network Builder using MST

![Language](https://img.shields.io/badge/Language-C++20-blue.svg)
![Library](https://img.shields.io/badge/Library-OpenMP-green.svg)
![Status](https://img.shields.io/badge/Status-Completed-success.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

<br />

> **A High-Performance Graph Optimization System**
>
> Accelerating Minimum Spanning Tree (MST) construction using the **Parallel Filter-Kruskal Algorithm**.

---

## 📖 About The Project

This project implements a parallelized solution for constructing **Minimum Spanning Trees (MST)** on massive dense graphs (10M+ edges).

Traditional serial algorithms like Kruskal's ($O(E \log E)$) become bottlenecks when dealing with large-scale infrastructure networks. By utilizing **OpenMP** and a **Domain Decomposition Strategy**, this project distributes the heavy sorting workload across multiple processor cores, achieving significant speedups over sequential implementations.

### ✨ Key Features
* **Parallel Filtering:** Implements the "Filter-Kruskal" strategy to discard 99% of redundant edges locally in parallel.
* **Optimized DSU:** Uses Disjoint Set Union with *Path Compression* and *Union by Size* for $O(\alpha(N))$ efficiency.
* **Memory Efficient:** Strategic pre-allocation to prevent heap fragmentation during parallel execution.
* **Automated Benchmarking:** Includes a built-in benchmark suite to test scalability across 1, 2, 4, 6, and 12 threads.

---

## 👥 Team Members

**Computer and Control Dept | Port Said University**

* 👨‍💻 **Mohamed Mousad**
* 👨‍💻 **Mohamed Eltabey**
* 👨‍💻 **Mohamed Khaled**
* 👨‍💻 **Ahmed Bassem**
* 👨‍💻 **Zeyad Khaled**

---

## 🚀 Performance Results

We tested the system on a Dense Random Graph with **10,000 Nodes** and **10,000,000 Edges**.

| Threads | Execution Time | Speedup | Efficiency |
| :--- | :--- | :--- | :--- |
| **1 (Serial)** | 3.30s | 1.00x | 100% |
| **2** | 1.74s | 1.90x | 95.0% |
| **4** | 0.92s | 3.58x | 89.5% |
| **6 (Physical)** | 0.65s | 5.07x | 84.5% |
| **12 (Logical)**| **0.57s** | **5.75x** | 47.9% |

> **Result:** We achieved a maximum speedup of **5.75x**, effectively utilizing the physical cores of the test machine.

---

## 🛠️ Getting Started

### Prerequisites
* **C++ Compiler:** GCC (`g++`) or MSVC with OpenMP support.
* **Python (Optional):** Required only if you want to generate the scalability graphs.

### Compilation

You can compile the project using `g++` directly from the terminal:

```bash
# Compile with OpenMP flag
g++ main.cpp kruskal.cpp -o mst_app -fopenmp -O3

```

### Running the Benchmark

Run the executable to start the automatic benchmark suite. It will test various thread counts and save the results to a CSV file.

```bash
# Windows
./mst_app.exe

# Linux / macOS
./mst_app
```

-----

## 📂 Project Structure

```text
├── 📄 main.cpp          # Benchmark engine & Entry point
├── 📄 kruskal.cpp       # Implementation of MST logic
├── 📄 kruskal.h         # Header file (API definitions)
├── 📄 generate_graphs.py # Python script to plot results
├── 📊 benchmark_results.csv # Output data (Generated after run)
└── 🖼️ graph_speedup.png     # Speedup Graph (Generated after run)
```

-----

## 🧠 Algorithm: Filter-Kruskal

The parallel strategy follows a **Map-Reduce** pattern:

1.  **Partitioning:** The massive list of edges is split into chunks.
2.  **Local Filter (Map):** Each thread sorts its chunk and runs a local Kruskal algorithm. This removes edges that form cycles within the chunk, reducing the dataset size by \~99%.
3.  **Global Merge (Reduce):** The few surviving edges from all threads are merged safely.
4.  **Final MST:** A final quick serial pass connects the remaining components.

-----

## 📊 Visualization

To generate the performance graphs included in our report:

1.  Run the C++ application (it generates `benchmark_results.csv`).
2.  Run the Python script:
    ```bash
    python generate_graphs.py
    ```

-----

## 📜 License

Distributed under the MIT License. See `LICENSE` for more information.
