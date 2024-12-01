#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <utility>

namespace network_utils {

std::vector<std::tuple<int, int, int>> buildEdges(const std::vector<std::vector<int>>& matrix);
std::vector<std::pair<int, int>> findMinimalSpanningTree(const std::vector<std::tuple<int, int, int>>& edges, int nodes);
std::pair<int, std::string> shortestRoute(const std::vector<std::vector<int>>& matrix);
int calculateMaxFlow(const std::vector<std::vector<int>>& capacity, int source, int sink);
std::pair<int, int> findNearestCentral(int x, int y, const std::vector<std::pair<int, int>>& centrals);

} // namespace network_utils
