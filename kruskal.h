#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>

// --- Edge Structure ---
struct Edge {
    int u, v, weight;
    // Operator overload for sorting edges by weight
    bool operator<(const Edge& other) const;
};

// --- Disjoint Set Union (DSU) Structure ---
struct DSU {
    std::vector<int> parent;
    std::vector<int> size; // <--- ADDED: To track tree size

    // Constructor
    DSU(int n);

    // Find representative with path compression
    int find(int i);

    // Unite two sets using Union by Size. Returns true if successful.
    bool join(int i, int j);
};

// --- Kruskal's Function Declaration ---
std::vector<Edge> run_kruskal(std::vector<Edge>& edges, int num_nodes);

#endif // KRUSKAL_H