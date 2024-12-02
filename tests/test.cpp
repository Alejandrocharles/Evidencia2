#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "functions.h"

using namespace network_utils;

TEST_CASE("Prueba de buildEdges", "[buildEdges]") {
    std::vector<std::vector<int>> matrix = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };
    auto edges = buildEdges(matrix);
    REQUIRE(edges.size() == 3);
    REQUIRE(edges[0] == std::make_tuple(0, 1, 1));
    REQUIRE(edges[1] == std::make_tuple(0, 2, 2));
    REQUIRE(edges[2] == std::make_tuple(1, 2, 3));
}

TEST_CASE("Prueba de findMinimalSpanningTree", "[findMinimalSpanningTree]") {
    std::vector<std::tuple<int, int, int>> edges = {
        {0, 1, 1},
        {0, 2, 2},
        {1, 2, 3}
    };
    auto mst = findMinimalSpanningTree(edges, 3);
    REQUIRE(mst.size() == 2);
    REQUIRE(mst[0] == std::make_pair(0, 1));
    REQUIRE(mst[1] == std::make_pair(0, 2));
}

TEST_CASE("Prueba de shortestRoute", "[shortestRoute]") {
    std::vector<std::vector<int>> matrix = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };
    auto [minCost, route] = shortestRoute(matrix);
    REQUIRE(minCost == 6);
    REQUIRE(route == "A B C A");
}

TEST_CASE("Prueba de calculateMaxFlow", "[calculateMaxFlow]") {
    std::vector<std::vector<int>> capacity = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };
    int maxFlow = calculateMaxFlow(capacity, 0, 5);
    REQUIRE(maxFlow == 23);
}

TEST_CASE("Prueba de findNearestCentral", "[findNearestCentral]") {
    std::vector<std::pair<int, int>> centrals = {
        {0, 0},
        {10, 10},
        {20, 20}
    };
    auto nearest = findNearestCentral(5, 5, centrals);
    REQUIRE(nearest == std::make_pair(0, 0));
}
