// test.cpp //
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
            throw std::invalid_argument("El número de colonias debe ser mayor que cero.");
        }

        // Crear la matriz de distancias entre las colonias
        std::vector<std::vector<int>> distanceMatrix(colonyCount, std::vector<int>(colonyCount));
        
        std::cout << "Introduzca las distancias entre las colonias:\n";
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

        // Crear la matriz de capacidades de los caminos
        std::vector<std::vector<int>> capacityMatrix(colonyCount, std::vector<int>(colonyCount));
        
        std::cout << "Introduzca las capacidades entre las colonias:\n";
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
        std::cout << "Introduzca las coordenadas de las centrales (formato: (x,y)):\n";
        for (int i = 0; i < colonyCount; ++i) {
            char lParen, comma, rParen;
            int x, y;
            std::cin >> lParen >> x >> comma >> y >> rParen;
            if (lParen != '(' || comma != ',' || rParen != ')') {
                throw std::invalid_argument("Formato incorrecto para las coordenadas.");
            }
            centralCoordinates.emplace_back(x, y);
        }

        // Coordenadas de un punto nuevo
        int newPointX, newPointY;
        std::cout << "Introduzca las coordenadas del nuevo punto (formato: (x,y)):\n";
        char lParen, comma, rParen;
        std::cin >> lParen >> newPointX >> comma >> newPointY >> rParen;
        if (lParen != '(' || comma != ',' || rParen != ')') {
            throw std::invalid_argument("Formato incorrecto para el nuevo punto.");
        }

        // Prueba de Kruskal
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

        // Prueba de TSP (Ruta más eficiente)
        try {
            auto [minCost, route] = shortestRoute(distanceMatrix);
            std::cout << "2. Ruta más eficiente (TSP):\n";
            std::cout << "Costo: " << minCost << "\nRuta: " << route << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en TSP: " << e.what() << "\n";
        }

        // Prueba de Ford-Fulkerson (Flujo máximo)
        try {
            int maxFlow = calculateMaxFlow(capacityMatrix, 0, colonyCount - 1);
            std::cout << "3. Flujo máximo: " << maxFlow << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en flujo máximo: " << e.what() << "\n";
        }

        // Buscar la central más cercana
        try {
            auto closestCentral = findNearestCentral(newPointX, newPointY, centralCoordinates);
            std::cout << "4. La central más cercana es: (" << closestCentral.first << ", " << closestCentral.second << ")\n";
        } catch (const std::exception& e) {
            std::cerr << "Error en la búsqueda: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error general: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
