#include <iostream>
#include <vector>
#include <stdexcept>
#include "functions.h"

int main() {
    try {
        using namespace network_utils;

        int colonyCount;
        std::cin >> colonyCount;
        if (colonyCount <= 0) {
            throw std::invalid_argument("La cantidad de colonias debe ser mayor que cero.");
        }

        // Crear la matriz de distancias
        std::vector<std::vector<int>> distanceMatrix(colonyCount, std::vector<int>(colonyCount));

        for (int i = 0; i < colonyCount; ++i) {
            for (int j = 0; j < colonyCount; ++j) {
                std::cin >> distanceMatrix[i][j];
                if (i == j && distanceMatrix[i][j] != 0) {
                    throw std::invalid_argument("La distancia entre una colonia y sí misma debe ser 0.");
                }
                if (distanceMatrix[i][j] < 0) {
                    throw std::invalid_argument("Las distancias no pueden ser negativas.");
                }
            }
        }

        // Crear la matriz de capacidades
        std::vector<std::vector<int>> capacityMatrix(colonyCount, std::vector<int>(colonyCount));

        for (int i = 0; i < colonyCount; ++i) {
            for (int j = 0; j < colonyCount; ++j) {
                std::cin >> capacityMatrix[i][j];
                if (capacityMatrix[i][j] < 0) {
                    throw std::invalid_argument("Las capacidades deben ser no negativas.");
                }
            }
        }

        // Coordenadas de las centrales
        std::vector<std::pair<int, int>> centralCoordinates;
        for (int i = 0; i < colonyCount; ++i) {
            char lParen, comma, rParen;
            int x, y;
            std::cin >> lParen >> x >> comma >> y >> rParen;
            if (lParen != '(' || comma != ',' || rParen != ')') {
                throw std::invalid_argument("Formato incorrecto para coordenadas.");
            }
            centralCoordinates.emplace_back(x, y);
        }

        // Leer coordenadas de un nuevo punto
        int newPointX, newPointY;
        std::cin >> lParen >> newPointX >> comma >> newPointY >> rParen;
        if (lParen != '(' || comma != ',' || rParen != ')') {
            throw std::invalid_argument("Formato incorrecto para el nuevo punto.");
        }

        // Kruskal
        try {
            auto edges = buildEdges(distanceMatrix);
            auto mst = findMinimalSpanningTree(edges, colonyCount);

            std::cout << "1. Árbol de expansión mínima:\n";
            for (const auto& edge : mst) {
                std::cout << "(" << char('A' + edge.first) << ", " << char('A' + edge.second) << ")\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error en Kruskal: " << e.what() << "\n";
        }

        // TSP
        try {
            auto [minCost, route] = shortestRoute(distanceMatrix);
            std::cout << "2. Ruta más eficiente (TSP):\n";
            std::cout << "Costo: " << minCost << "\nRuta: " << route << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en TSP: " << e.what() << "\n";
        }

        // Ford-Fulkerson
        try {
            int maxFlow = calculateMaxFlow(capacityMatrix, 0, colonyCount - 1);
            std::cout << "3. Flujo máximo: " << maxFlow << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en flujo máximo: " << e.what() << "\n";
        }

        // Central más cercana
        try {
            auto closestCentral = findNearestCentral(newPointX, newPointY, centralCoordinates);
            std::cout << "4. Central más cercana: (" << closestCentral.first << ", " << closestCentral.second << ")\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en la búsqueda: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error general: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
