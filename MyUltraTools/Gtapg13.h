#pragma once
/*
 * 13. Понятие и формальное определение графа.
 *     Представление графов в памяти. Обход в глубину (DFS) и в ширину (BFS).
 *
 * Граф G = (V, E) — множество вершин V и множество рёбер E (неупорядоченные пары для
 * неориентированного, упорядоченные для ориентированного).
 *
 * Два основных представления в памяти:
 * 1. Матрица смежности: память O(|V|^2), проверка ребра O(1), перебор соседей O(|V|).
 * 2. Списки смежности: память O(|V| + |E|), проверка ребра O(deg(v)), перебор соседей O(deg(v)).
 *    Для большинства графов (разреженных) списки смежности эффективнее.
 *
 * В этом примере используем списки смежности через vector<vector<int>>.
 * Реализуем DFS (рекурсивный) и BFS (итеративный с очередью).
 *
 * Сложность обходов: O(|V| + |E|) — посещаем каждую вершину и каждое ребро один раз.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
    int V; // количество вершин
    vector<vector<int>> adj; // список смежности

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    // Добавить неориентированное ребро
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ---------- ОБХОД В ГЛУБИНУ (DFS) ----------
    // Рекурсивный подход: идём вглубь по первому непосещённому соседу.
    // Использует стек вызовов (неявный стек).
    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS (рекурсивный) от вершины " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

private:
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

public:
    // ---------- ОБХОД В ШИРИНУ (BFS) ----------
    // Итеративный подход: используем очередь, сначала посещаем всех соседей, затем их соседей.
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS от вершины " << start << ": ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};


void R13()
{
    setlocale(LC_ALL, ""); // для кириллицы (Windows)

    Graph g(7); // граф с 7 вершинами (0..6)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "Структура графа:\n";
    cout << "    0\n";
    cout << "   / \\\n";
    cout << "  1   2\n";
    cout << " / \\ / \\\n";
    cout << "3   4 5  6\n\n";

    g.DFS(0); // Ожидаемый порядок (один из): 0 1 3 4 2 5 6
    g.BFS(0); // Ожидаемый порядок: 0 1 2 3 4 5 6

    cout << "\nВычислительная сложность обоих обходов: O(|V| + |E|)\n";
}
