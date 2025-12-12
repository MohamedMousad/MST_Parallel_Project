#include <iostream>
#include <vector>
#include <iomanip>
#include <omp.h>
#include "kruskal.h" // header of the algorithm we will use

// --- ANSI COLORS ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Configuration
#define EDGE_COUNT 10000000
#define NODE_COUNT 10000

using namespace std;

int main() {
    int N = NODE_COUNT;
    int Total_Edges = EDGE_COUNT;

    int max_threads = omp_get_max_threads();

    cout << BOLD << CYAN << "=================================================\n";
    cout << "   PROJECT: Parallel Network Builder using MST \n";
    cout << "=================================================\n" << RESET;
    cout << "Nodes: " << N << " | Edges: " << Total_Edges << " | Threads: " << max_threads << "\n\n";

    // --- STEP 1: Data Generation ---
    cout << YELLOW << "[1/3] Generating Graph..." << RESET << flush;
    vector<Edge> all_edges;
    all_edges.reserve(Total_Edges);
    srand(42);

    for (int i = 0; i < N - 1; i++)
        all_edges.push_back({i, i + 1, (rand() % 100) + 1});

    while (all_edges.size() < Total_Edges) {
        int u = rand() % N; int v = rand() % N;
        if (u != v) all_edges.push_back({u, v, (rand() % 100) + 1});
    }
    cout << GREEN << " Done.\n" << RESET;

    // --- STEP 2: Serial Benchmark ---
    cout << YELLOW << "[2/3] Running Serial Benchmark..." << RESET << flush;
    double start_serial = omp_get_wtime();

    vector<Edge> serial_copy = all_edges;
    run_kruskal(serial_copy, N); // Calling function from kruskal.cpp

    double end_serial = omp_get_wtime();
    double serial_time = end_serial - start_serial;
    cout << GREEN << " Done (" << fixed << setprecision(4) << serial_time << "s).\n" << RESET;

    // --- STEP 3: Parallel Execution ---
    cout << BLUE << "[3/3] Executing Enhanced Parallel Kruskal..." << RESET << flush;
    double start_parallel = omp_get_wtime();

    vector<Edge> final_mst_candidates;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        int chunk_size = Total_Edges / num_threads;
        int start = thread_id * chunk_size;
        int end = (thread_id == num_threads - 1) ? Total_Edges : start + chunk_size;

        vector<Edge> local_edges;
        local_edges.reserve(chunk_size);
        for(int i = start; i < end; i++) {
            local_edges.push_back(all_edges[i]);
        }

        // Calling function from kruskal.cpp
        vector<Edge> local_result = run_kruskal(local_edges, N);

        #pragma omp critical
        {
            final_mst_candidates.insert(final_mst_candidates.end(),
                                        local_result.begin(), local_result.end());
        }
    }

    // Final Global Filter
    vector<Edge> final_mst = run_kruskal(final_mst_candidates, N);

    double end_parallel = omp_get_wtime();
    double parallel_time = end_parallel - start_parallel;
    cout << GREEN << " Done.\n" << RESET;

    // --- FINAL REPORT ---
    {
        double speedup = serial_time / parallel_time;
        double efficiency = (speedup / max_threads) * 100.0;
        long long total_weight = 0;
        for (const auto& e : final_mst) total_weight += e.weight;

        cout << "\n" << BOLD << CYAN << "=================================================\n";
        cout << "               FINAL RESULTS REPORT              \n";
        cout << "=================================================\n" << RESET;
        cout << left << setw(25) << "Final MST Edges" << ": " << final_mst.size() << " (Target: " << N-1 << ")\n";
        cout << left << setw(25) << "Total Cost" << ": " << total_weight << "\n";
        cout << "-------------------------------------------------\n";
        cout << left << setw(25) << "Serial Time" << ": " << RED << serial_time << "s" << RESET << "\n";
        cout << left << setw(25) << "Parallel Time" << ": " << GREEN << parallel_time << "s" << RESET << "\n";
        cout << "-------------------------------------------------\n";
        cout << left << setw(25) << "SPEEDUP" << ": " << BOLD << YELLOW << speedup << "x" << RESET << "\n";
        cout << left << setw(25) << "EFFICIENCY" << ": " << efficiency << "%\n";
        cout << BOLD << CYAN << "=================================================\n" << RESET;
    }

    return 0;
}