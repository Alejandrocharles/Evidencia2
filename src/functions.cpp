#include "functions.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <stdexcept>
#include <limits>

namespace network_utils {

std::vector<std::tuple<int, int, int>> buildEdges(const std::vector<std::vector<int>>& matrix) {
    // Código de la función
}

std::vector<std::pair<int, int>> findMinimalSpanningTree(const std::vector<std::tuple<int, int, int>>& edges, int nodes) {
    std::vector<int> parent(nodes), rank(nodes, 0);
    std::vector<std::pair<int, int>> mst;
    for (int i = 0; i < nodes; ++i) parent[i] = i;

    std::function<int(int)> findRoot = [&](int node) -> int {
        return node == parent[node] ? node : parent[node] = findRoot(parent[node]);
    };

    auto unionSets = [&](int u, int v) -> bool {
        int rootU = findRoot(u), rootV = findRoot(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else parent[rootV] = rootU, ++rank[rootU];
            return true;
        }
        return false;
    };

    auto sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    for (const auto& [u, v, w] : sortedEdges) {
        if (unionSets(u, v)) mst.emplace_back(u, v);
    }
    return mst;
}

std::pair<int, std::string> shortestRoute(const std::vector<std::vector<int>>& matrix) {
    // Código de la función
}

int calculateMaxFlow(const std::vector<std::vector<int>>& capacity, int source, int sink) {
    // Código de la función
}

std::pair<int, int> findNearestCentral(int x, int y, const std::vector<std::pair<int, int>>& centrals) {
    // Código de la función
}

} // namespace network_utils
#include "functions.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <stdexcept>
#include <limits>

namespace network_utils {

std::vector<std::tuple<int, int, int>> buildEdges(const std::vector<std::vector<int>>& matrix) {
    // Código de la función
}

std::vector<std::pair<int, int>> findMinimalSpanningTree(const std::vector<std::tuple<int, int, int>>& edges, int nodes) {
    std::vector<int> parent(nodes), rank(nodes, 0);
    std::vector<std::pair<int, int>> mst;
    for (int i = 0; i < nodes; ++i) parent[i] = i;

    std::function<int(int)> findRoot = [&](int node) -> int {
        return node == parent[node] ? node : parent[node] = findRoot(parent[node]);
    };

    auto unionSets = [&](int u, int v) -> bool {
        int rootU = findRoot(u), rootV = findRoot(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else parent[rootV] = rootU, ++rank[rootU];
            return true;
        }
        return false;
    };

    auto sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    for (const auto& [u, v, w] : sortedEdges) {
        if (unionSets(u, v)) mst.emplace_back(u, v);
    }
    return mst;
}

std::pair<int, std::string> shortestRoute(const std::vector<std::vector<int>>& matrix) {
    // Código de la función
}

int calculateMaxFlow(const std::vector<std::vector<int>>& capacity, int source, int sink) {
    // Código de la función
}

std::pair<int, int> findNearestCentral(int x, int y, const std::vector<std::pair<int, int>>& centrals) {
    // Código de la función
}

} // namespace network_utils
