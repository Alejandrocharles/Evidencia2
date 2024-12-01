#pragma once

#include <string>
#include <vector>
#include <utility>

namespace mynamespace {

/**
 * @brief Aplica el algoritmo de Kruskal para encontrar el Árbol de Expansión Mínima.
 * 
 * @param edges Vector de aristas representadas como {nodo1, nodo2, peso}.
 * @param nodes Número de nodos del grafo.
 * @return std::vector<std::pair<int, int>> Aristas del Árbol de Expansión Mínima.
 */
std::vector<std::pair<int, int>> kruskal(const std::vector<std::tuple<int, int, int>>& edges, int nodes);

/**
 * @brief Encuentra la ruta más corta para el problema del viajante (TSP) usando fuerza bruta.
 * 
 * @param distances Matriz de distancias entre las ciudades.
 * @return std::pair<int, std::string> Costo mínimo y ruta en formato "A B C".
 */
std::pair<int, std::string> traveling_salesman(const std::vector<std::vector<int>>& distances);

/**
 * @brief Calcula el flujo máximo entre dos nodos usando el algoritmo de Ford-Fulkerson.
 * 
 * @param capacity Matriz de capacidades del grafo.
 * @param source Nodo fuente.
 * @param sink Nodo sumidero.
 * @return int Flujo máximo calculado.
 */
int ford_fulkerson(const std::vector<std::vector<int>>& capacity, int source, int sink);

/**
 * @brief Encuentra la central más cercana a un punto (x, y) basado en distancias euclidianas.
 * 
 * @param x Coordenada x del punto.
 * @param y Coordenada y del punto.
 * @param centrals Vector de coordenadas de las centrales.
 * @return std::pair<int, int> Coordenadas de la central más cercana.
 */
std::pair<int, int> nearest_central(int x, int y, const std::vector<std::pair<int, int>>& centrals);

} // namespace mynamespace
