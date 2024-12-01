#include <iostream>
#include <vector>
#include <stdexcept>
#include "funciones.h"

int main() {
    try {
        using namespace mynamespace;

        // Leer el número de colonia
        int n;
        std::cin >> n;
        if (n <= 0) {
            throw std::invalid_argument("El número de colonias debe ser mayor a 0.");
        }

        // Matriz de distancias (grafo para TSP y Kruskal)
        std::vector<std::vector<int>> graph(n, std::vector<int>(n));

        // Leer la matriz de distancias
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> graph[i][j];
                if (i == j && graph[i][j] != 0) {
                    throw std::invalid_argument("Las distancias entre una ciudad y sí misma deben ser 0.");
                }
                if (graph[i][j] < 0) {
                    throw std::invalid_argument("Las distancias entre colonias no pueden ser negativas.");
                }
            }
        }

        // Matriz de capacidades (grafo para Ford-Fulkerson)
        std::vector<std::vector<int>> capacity(n, std::vector<int>(n));

        // Leer la matriz de capacidades
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> capacity[i][j];
                if (capacity[i][j] < 0) {
                    throw std::invalid_argument("Las capacidades de flujo no pueden ser negativas.");
                }
            }
        }

        // Leer las coordenadas de las centrales
        std::vector<std::pair<int, int>> centrals;
        for (int i = 0; i < n; ++i) {
            char openParen, comma, closeParen;
            int x, y;
            std::cin >> openParen >> x >> comma >> y >> closeParen;
            if (openParen != '(' || comma != ',' || closeParen != ')') {
                throw std::invalid_argument("Formato inválido para las coordenadas de las centrales.");
            }
            centrals.emplace_back(x, y);
        }

        // Leer las coordenadas de la nueva contratación
        int newX, newY;
        char openParen, comma, closeParen;
        std::cin >> openParen >> newX >> comma >> newY >> closeParen;
        if (openParen != '(' || comma != ',' || closeParen != ')') {
            throw std::invalid_argument("Formato inválido para las coordenadas de la nueva contratación.");
        }

        // 1. Kruskal - Forma de cablear con fibra
        try {
            std::vector<std::tuple<int, int, int>> edges;
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (graph[i][j] > 0) {
                        edges.emplace_back(i, j, graph[i][j]);
                    }
                }
            }

            auto mst = kruskal(edges, n);

            std::cout << "1. Árbol de Expansión Mínima (Kruskal):\n";
            for (const auto& edge : mst) {
                std::cout << "(" << char('A' + edge.first) << ", " << char('A' + edge.second) << ")\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error en Kruskal: " << e.what() << "\n";
        }

        // 2. Traveling Salesman - Ruta más corta
        try {
            auto [cost, path] = traveling_salesman(graph);
            std::cout << "2. Ruta más corta (TSP):\n";
            std::cout << "Costo mínimo: " << cost << "\n";
            std::cout << "Ruta: " << path << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en TSP: " << e.what() << "\n";
        }

        // 3. Ford-Fulkerson - Máximo flujo
        try {
            int maxFlow = ford_fulkerson(capacity, 0, n - 1);
            std::cout << "3. Flujo máximo (Ford-Fulkerson): " << maxFlow << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en Ford-Fulkerson: " << e.what() << "\n";
        }

        // 4. Búsqueda lineal - Central más cercana
        try {
            auto nearest = nearest_central(newX, newY, centrals);
            std::cout << "4. Central más cercana:\n";
            std::cout << "(" << nearest.first << ", " << nearest.second << ")\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en búsqueda lineal: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error general: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
