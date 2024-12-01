#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "funciones.h"
#include <fstream>
#include <cstdio> 

using namespace mynamespace;

// Test for Kruskal
TEST_CASE("kruskal: Generar Árbol de Expansión Mínima", "[kruskal]") {
    std::vector<std::tuple<int, int, int>> edges = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 4}
    };
    int nodes = 4;

    auto mst = kruskal(edges, nodes);

    REQUIRE(mst.size() == 3); // Deben haber N-1 aristas
    REQUIRE(mst == std::vector<std::pair<int, int>>{{1, 2}, {1, 3}, {0, 2}}); // Verifica aristas del MST
}

// Test for Traveling Salesman
TEST_CASE("traveling_salesman: Ruta más corta (TSP)", "[traveling_salesman]") {
    std::vector<std::vector<int>> distances = {
        {0, 16, 45, 32},
        {16, 0, 18, 21},
        {45, 18, 0, 7},
        {32, 21, 7, 0}
    };

    auto [cost, path] = traveling_salesman(distances);

    REQUIRE(cost == 66); // Costo esperado
    REQUIRE(path == "A B D C A "); // Ruta esperada
}

// Test for Ford-Fulkerson
TEST_CASE("ford_fulkerson: Flujo máximo", "[ford_fulkerson]") {
    std::vector<std::vector<int>> capacity = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };
    int source = 0, sink = 5;

    int maxFlow = ford_fulkerson(capacity, source, sink);

    REQUIRE(maxFlow == 23); // Flujo máximo esperado
}

// Test for Nearest Central
TEST_CASE("nearest_central: Encontrar central más cercana", "[nearest_central]") {
    std::vector<std::pair<int, int>> centrals = {
        {0, 0}, {2, 2}, {5, 5}, {10, 10}
    };
    int x = 3, y = 3;

    auto nearest = nearest_central(x, y, centrals);

    REQUIRE(nearest == std::make_pair(2, 2)); // Central más cercana esperada
}

TEST_CASE("nearest_central: Sin centrales", "[nearest_central]") {
    std::vector<std::pair<int, int>> centrals;
    int x = 3, y = 3;

    REQUIRE_THROWS_AS(nearest_central(x, y, centrals), std::invalid_argument); // Excepción esperada
}
