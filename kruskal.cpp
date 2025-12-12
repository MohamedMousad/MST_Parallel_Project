#include "kruskal.h"
#include <algorithm> // Required for std::sort
#include <utility>   // Required for std::swap

// --- Edge Implementation ---
bool Edge::operator<(const Edge& other) const {
    return weight < other.weight;
}

// --- DSU Implementation ---
DSU::DSU(int n) {
    parent.resize(n);
    size.resize(n, 1); // <--- ADDED: Initialize all sizes to 1
    for (int i = 0; i < n; i++) parent[i] = i;
}

int DSU::find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]); // Path compression
}

bool DSU::join(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);

    if (root_i != root_j) {
        if (size[root_i] < size[root_j])
            std::swap(root_i, root_j); // Ensure root_i is always the larger one

        parent[root_j] = root_i;
        size[root_i] += size[root_j]; // Update the size of the new root

        return true; // Connection successful
    }
    return false; // Already connected (cycle)
}

// --- Kruskal's Logic Implementation ---
std::vector<Edge> run_kruskal(std::vector<Edge>& edges, int num_nodes) {
    std::vector<Edge> mst;
    mst.reserve(num_nodes); // Pre-allocate memory for efficiency

    DSU dsu(num_nodes);

    // Sort edges by weight (the heavy lifting)
    std::sort(edges.begin(), edges.end());

    int edges_count = 0;
    for (const auto& edge : edges) {
        if (dsu.join(edge.u, edge.v)) {
            mst.push_back(edge);
            edges_count++;
            // Optimization: Stop once the tree is complete (N-1 edges)
            if (edges_count == num_nodes - 1) break;
        }
    }
    return mst;
}