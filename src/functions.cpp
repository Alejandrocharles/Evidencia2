#include "functions.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <stdexcept>
#include <limits>

namespace network_utils {

std::vector<std::tuple<int, int, int>> buildEdges(const std::vector<std::vector<int>>& matrix) {
    std::vector<std::tuple<int, int, int>> edges;
    int nodes = matrix.size();
    for (int i = 0; i < nodes; ++i) {
        for (int j = i + 1; j < nodes; ++j) {
            if (matrix[i][j] > 0) {
                edges.emplace_back(i, j, matrix[i][j]);
            }
        }
    }
    return edges;
}

std::vector<std::pair<int, int>> findMinimalSpanningTree(const std::vector<std::tuple<int, int, int>>& edges, int nodes) {
    std::vector<int> parent(nodes), rank(nodes, 0);
    std::vector<std::pair<int, int>> mst;
    for (int i = 0; i < nodes; ++i) parent[i] = i;

    auto findRoot = [&](int node) {
        return node == parent[node] ? node : parent[node] = findRoot(parent[node]);
    };

    auto unionSets = [&](int u, int v) {
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
    int n = matrix.size();
    std::vector<int> vertices;
    for (int i = 1; i < n; ++i) {
        vertices.push_back(i);
    }

    int minPathCost = std::numeric_limits<int>::max();
    std::string bestRoute;

    do {
        int currentPathCost = 0;
        int k = 0;
        std::string currentRoute = "A";

        for (int i = 0; i < vertices.size(); ++i) {
            currentPathCost += matrix[k][vertices[i]];
            currentRoute += " " + std::string(1, 'A' + vertices[i]);
            k = vertices[i];
        }
        currentPathCost += matrix[k][0];
        currentRoute += " A";

        if (currentPathCost < minPathCost) {
            minPathCost = currentPathCost;
            bestRoute = currentRoute;
        }
    } while (std::next_permutation(vertices.begin(), vertices.end()));

    return {minPathCost, bestRoute};
}

int calculateMaxFlow(const std::vector<std::vector<int>>& capacity, int source, int sink) {
    int n = capacity.size();
    std::vector<std::vector<int>> residualCapacity = capacity;
    std::vector<int> parent(n);
    int maxFlow = 0;

    auto bfs = [&]() -> bool {
        std::fill(parent.begin(), parent.end(), -1);
        parent[source] = source;
        std::queue<std::pair<int, int>> q;
        q.push({source, std::numeric_limits<int>::max()});

        while (!q.empty()) {
            int u = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int v = 0; v < n; ++v) {
                if (parent[v] == -1 && residualCapacity[u][v] > 0) {
                    parent[v] = u;
                    int newFlow = std::min(flow, residualCapacity[u][v]);
                    if (v == sink) {
                        return newFlow;
                    }
                    q.push({v, newFlow});
                }
            }
        }
        return 0;
    };

    int newFlow;
    while (newFlow = bfs()) {
        maxFlow += newFlow;
        int u = sink;
        while (u != source) {
            int v = parent[u];
            residualCapacity[v][u] -= newFlow;
            residualCapacity[u][v] += newFlow;
            u = v;
        }
    }
    return maxFlow;
}

std::pair<int, int> findNearestCentral(int x, int y, const std::vector<std::pair<int, int>>& centrals) {
    auto distance = [](int x1, int y1, int x2, int y2) {
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    };

    std::pair<int, int> nearestCentral = centrals.front();
    double minDistance = distance(x, y, nearestCentral.first, nearestCentral.second);

    for (const auto& central : centrals) {
        double d = distance(x, y, central.first, central.second);
        if (d < minDistance) {
            minDistance = d;
            nearestCentral = central;
        }
    }
    return nearestCentral;
}

} // namespace network_utils
