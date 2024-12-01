/*
 * SonarQube, open source software quality management tool.
 * Copyright (C)
 */

#include "funciones.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <stdexcept>
#include <iostream>

namespace mynamespace {

std::vector<std::pair<int, int>> kruskal(const std::vector<std::tuple<int, int, int>>& edges, int nodes) {
    std::vector<int> parent(nodes);
    std::vector<int> rank(nodes, 0);
    std::vector<std::pair<int, int>> mst;

    for (int i = 0; i < nodes; ++i) {
        parent[i] = i;
    }

    auto find = [&](int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    };

    auto unionSets = [&](int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                ++rank[rootU];
            }
            return true;
        }
        return false;
    };

    std::vector<std::tuple<int, int, int>> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(),
              [](const auto& a, const auto& b) { return std::get<2>(a) < std::get<2>(b); });

    for (const auto& [u, v, weight] : sortedEdges) {
        if (unionSets(u, v)) {
            mst.emplace_back(u, v);
        }
    }

    return mst;
}

std::pair<int, std::string> traveling_salesman(const std::vector<std::vector<int>>& distances) {
    int n = distances.size();
    std::vector<int> path(n);
    for (int i = 0; i < n; ++i) path[i] = i;

    int minCost = std::numeric_limits<int>::max();
    std::string bestPath;

    do {
        int cost = 0;
        for (int i = 0; i < n - 1; ++i) {
            cost += distances[path[i]][path[i + 1]];
        }
        cost += distances[path[n - 1]][path[0]];

        if (cost < minCost) {
            minCost = cost;
            bestPath.clear();
            for (int city : path) {
                bestPath += char('A' + city);
                bestPath += " ";
            }
            bestPath += char('A' + path[0]);
        }
    } while (std::next_permutation(path.begin(), path.end()));

    return {minCost, bestPath};
}

int ford_fulkerson(const std::vector<std::vector<int>>& capacity, int source, int sink) {
    int n = capacity.size();
    std::vector<std::vector<int>> flow(n, std::vector<int>(n, 0));
    std::vector<int> parent(n);
    int maxFlow = 0;

    auto bfs = [&]() {
        std::fill(parent.begin(), parent.end(), -1);
        std::queue<int> q;
        q.push(source);
        parent[source] = source;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; ++v) {
                if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                    parent[v] = u;
                    if (v == sink) return true;
                    q.push(v);
                }
            }
        }
        return false;
    };

    while (bfs()) {
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, capacity[u][v] - flow[u][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += pathFlow;
            flow[v][u] -= pathFlow;
        }
        maxFlow += pathFlow;
    }

    return maxFlow;
}

std::pair<int, int> nearest_central(int x, int y, const std::vector<std::pair<int, int>>& centrals) {
    if (centrals.empty()) {
        throw std::invalid_argument("La lista de centrales no puede estar vacía.");
    }

    std::pair<int, int> nearest = centrals[0];
    double minDist = std::hypot(nearest.first - x, nearest.second - y);

    for (const auto& central : centrals) {
        double dist = std::hypot(central.first - x, central.second - y);
        if (dist < minDist) {
            minDist = dist;
            nearest = central;
        }
    }

    return nearest;
}

} // namespace mynamespace
