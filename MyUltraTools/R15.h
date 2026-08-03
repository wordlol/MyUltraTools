#pragma once
/*
 * 15. Построение минимального остовного дерева (MST).
 * Задача: для связного взвешенного неориентированного графа найти дерево,
 * которое соединяет все вершины и имеет минимальную сумму весов рёбер.
 *
 * Алгоритм Прима:
 *   - Начинаем с произвольной вершины, постепенно добавляем рёбра минимального
 *     веса, соединяющие уже построенное дерево с новой вершиной.
 *   - Используем приоритетную очередь (мин-куча).
 *   - Сложность: O((V+E) log V) с двоичной кучей.
 *
 * Алгоритм Крускала:
 *   - Сортируем все рёбра по весу, идём по возрастанию и добавляем ребро,
 *     если оно не создаёт цикл (проверка системой непересекающихся множеств DSU).
 *   - Сложность: O(E log E) или O(E log V) (из-за сортировки и операций DSU).
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <locale>
using namespace std;

// Структура ребра
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// --- Система непересекающихся множеств (DSU) для Крускала ---
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) ++rank[px];
        return true;
    }
};

// --- Алгоритм Прима ---
// Возвращает список рёбер MST и общий вес.
// graph представлен списком смежности: vector<vector<pair<int,int>>>,
// где graph[u] = { {v, weight}, ... }
pair<vector<Edge>, int> primMST(const vector<vector<pair<int, int>>>& graph) {
    size_t n = graph.size();
    vector<bool> visited(n, false);
    vector<Edge> mst;
    int totalWeight = 0;

    // Элемент очереди: (вес, (вершина, родитель))
    using Element = pair<int, pair<int, int>>;
    priority_queue<Element, vector<Element>, greater<Element>> pq;
    pq.push({ 0, {0, -1} });  // начальная вершина 0, родитель -1

    while (!pq.empty()) {
        Element top = pq.top();
        pq.pop();
        int w = top.first;
        int u = top.second.first;
        int parent = top.second.second;

        if (visited[u]) continue;
        visited[u] = true;
        totalWeight += w;
        if (parent != -1) {
            mst.push_back({ parent, u, w });
        }

        for (size_t i = 0; i < graph[u].size(); ++i) {
            int v = graph[u][i].first;
            int weight = graph[u][i].second;
            if (!visited[v]) {
                pq.push({ weight, {v, u} });
            }
        }
    }
    return { mst, totalWeight };
}

// --- Алгоритм Крускала ---
// Принимает список всех рёбер и количество вершин.
pair<vector<Edge>, int> kruskalMST(vector<Edge> edges, int n) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    vector<Edge> mst;
    int totalWeight = 0;
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.weight;
            if (mst.size() == n - 1) break;
        }
    }
    return { mst, totalWeight };
}



void R15()
{
    setlocale(LC_ALL, "");

    // Граф для Прима (6 вершин)
    vector<vector<pair<int, int>>> graph(6);
    auto addEdge = [&](int u, int v, int w) {
        graph[u].push_back({ v, w });
        graph[v].push_back({ u, w });
        };
    addEdge(0, 1, 4);
    addEdge(0, 2, 4);
    addEdge(1, 2, 2);
    addEdge(1, 0, 4); // уже добавлено
    addEdge(2, 3, 3);
    addEdge(2, 5, 2);
    addEdge(2, 4, 4);
    addEdge(3, 4, 3);
    addEdge(5, 4, 3);

    auto [primEdges, primW] = primMST(graph);
    cout << "Алгоритм Прима:\n";
    cout << "Рёбра MST: ";
    for (auto& e : primEdges) cout << "(" << e.u << "," << e.v << ") ";
    cout << "\nОбщий вес: " << primW << endl;

    // Список рёбер для Крускала (тот же граф)
    vector<Edge> edges = {
        {0,1,4}, {0,2,4}, {1,2,2}, {2,3,3}, {2,5,2}, {2,4,4}, {3,4,3}, {5,4,3}
    };
    auto [kruskEdges, kruskW] = kruskalMST(edges, 6);
    cout << "\nАлгоритм Крускала:\n";
    cout << "Рёбра MST: ";
    for (auto& e : kruskEdges) cout << "(" << e.u << "," << e.v << ") ";
    cout << "\nОбщий вес: " << kruskW << endl;
}

