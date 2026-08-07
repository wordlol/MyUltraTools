#pragma once
/*
 * 14. Поиск кратчайших путей в графе.
 * Формальная постановка: для взвешенного графа найти кратчайшие пути
 * от одной вершины до всех (Дейкстра) или между всеми парами вершин (Флойд).
 *
 * Алгоритм Дейкстры (для графов без отрицательных рёбер):
 *   - Использует жадную стратегию с приоритетной очередью.
 *   - На каждом шаге выбирает непосещённую вершину с минимальным расстоянием,
 *     релаксирует рёбра из неё.
 *   - Сложность: O((V+E) log V) с двоичной кучей.
 *
 * Алгоритм Флойда-Уоршелла (для любых взвешенных графов, в том числе с
 *   отрицательными рёбрами, но без отрицательных циклов):
 *   - Динамическое программирование: постепенно разрешаем использовать
 *     промежуточные вершины.
 *   - Сложность: O(V^3), память O(V^2).
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
#include <locale>
using namespace std;

const int INF = numeric_limits<int>::max();

// --- Алгоритм Дейкстры ---
// Возвращает вектор расстояний от start до всех вершин.
vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int start) {
    size_t n = graph.size();
    vector<int> dist(n, INF);
    dist[start] = 0;

    // Очередь с приоритетом: (расстояние, вершина)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue; // устаревшая запись

        for (auto& [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({ dist[v], v });
            }
        }
    }
    return dist;
}

// --- Алгоритм Флойда-Уоршелла ---
// Принимает матрицу смежности (веса рёбер), модифицирует её в матрицу кратчайших путей.
// Если ребро отсутствует, вес должен быть INF.
void floydWarshall(vector<vector<int>>& dist) {
    size_t n = dist.size();
    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}
Ы
void R14()
{
    setlocale(LC_ALL, "");
    // Граф для Дейкстры: 5 вершин (0..4)
    vector<vector<pair<int, int>>> graph(5);
    graph[0] = { {1,10}, {3,5} };
    graph[1] = { {2,1}, {3,2} };
    graph[2] = { {4,4} };
    graph[3] = { {1,3}, {2,9}, {4,2} };
    graph[4] = { {0,7}, {2,6} };

    auto distD = dijkstra(graph, 0);
    cout << "Дейкстра от вершины 0:\n";
    for (size_t i = 0; i < distD.size(); ++i)
    {
        cout << "  до " << i << ": ";
        if (distD[i] == INF) cout << "?";
        else cout << distD[i];
        cout << "\n";
    }


    // Матрица для Флойда (4 вершины)
    vector<vector<int>> mat = {
        {0,   5,   INF, 10},
        {INF, 0,   3,   INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };
    floydWarshall(mat);
    cout << "\nФлойд (матрица кратчайших путей):\n";
    for (auto& row : mat) {
        for (int val : row) {
            if (val == INF) cout << setw(4) << "?";
            else cout << setw(4) << val;
        }
        cout << "\n";
    }
}
