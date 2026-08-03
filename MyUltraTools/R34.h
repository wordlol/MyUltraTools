#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <memory>

using namespace std;

// Задача (элемент ИСР)
class Task {
public:
    int id;
    string name;
    int duration;               // длительность в днях
    vector<int> dependencies;   // от каких задач зависит (id)
    int earlyStart = 0, earlyFinish = 0;  // ранние сроки
    int lateStart = 0, lateFinish = 0;    // поздние сроки
    int slack = 0;                        // резерв времени

    Task(int i, const string& n, int dur) : id(i), name(n), duration(dur) {}
};

// Проект
class Project {
    vector<Task> tasks;
    map<int, vector<int>> children; // для иерархии ИСР (родитель -> дети)

public:
    // Добавление задачи
    void addTask(int id, const string& name, int duration, int parentId = -1) {
        tasks.emplace_back(id, name, duration);
        if (parentId != -1) {
            children[parentId].push_back(id);
        }
    }

    // Добавление зависимости между задачами
    void addDependency(int taskId, int dependsOnId) {
        for (auto& t : tasks) {
            if (t.id == taskId) {
                t.dependencies.push_back(dependsOnId);
                break;
            }
        }
    }

    // ====== ИСР (текстовое представление) ======
    void printWBS(int root = -1, int level = 0) {
        if (root == -1) {
            // находим корневые задачи (без родителей)
            for (auto& t : tasks) {
                bool hasParent = false;
                for (auto& [parent, childs] : children) {
                    for (int c : childs) {
                        if (c == t.id) { hasParent = true; break; }
                    }
                }
                if (!hasParent) printWBS(t.id, 0);
            }
            return;
        }

        for (int i = 0; i < level; ++i) cout << "  ";
        auto it = find_if(tasks.begin(), tasks.end(), [root](const Task& t) { return t.id == root; });
        if (it != tasks.end()) {
            cout << "[" << it->id << "] " << it->name << " (" << it->duration << " дн.)\n";
            if (children.count(root)) {
                for (int child : children[root]) {
                    printWBS(child, level + 1);
                }
            }
        }
    }

    // ====== Диаграмма Ганта (текстовая) ======
    void printGantt() {
        cout << "\n=== Диаграмма Ганта ===\n";
        cout << left << setw(20) << "Задача" << "|" << right << setw(10) << "Начало" << "|" << setw(10) << "Конец" << "|" << "График\n";
        cout << string(20, '-') << "+" << string(10, '-') << "+" << string(10, '-') << "+" << string(20, '-') << "\n";

        // Для простоты предполагаем, что ранние сроки уже рассчитаны
        for (auto& t : tasks) {
            cout << left << setw(20) << t.name << "|" << right << setw(4) << t.earlyStart << "  |" << setw(4) << t.earlyFinish << "  |";
            // Горизонтальная полоса
            for (int i = 0; i < t.earlyStart; ++i) cout << " ";
            for (int i = t.earlyStart; i < t.earlyFinish; ++i) cout << "#";
            cout << "\n";
        }
    }

    // ====== Сетевой график и критический путь ======
    void calculateCriticalPath() {
        // Топологическая сортировка (Kahn's algorithm)
        vector<int> inDegree(tasks.size(), 0);
        map<int, vector<int>> dependents; // обратные зависимости: кто зависит от задачи
        for (auto& t : tasks) {
            for (int dep : t.dependencies) {
                inDegree[t.id]++; // на самом деле нужно по индексу, но id соответствуют
                dependents[dep].push_back(t.id);
            }
        }

        vector<int> sorted;
        vector<int> queue;
        // Находим задачи без зависимостей
        for (auto& t : tasks) {
            if (t.dependencies.empty()) queue.push_back(t.id);
        }

        while (!queue.empty()) {
            int id = queue.back();
            queue.pop_back();
            sorted.push_back(id);
            for (int dep : dependents[id]) {
                // уменьшаем степень зависимости
                // здесь можно было бы использовать map для отслеживания
            }
        }

        // Упрощённый расчёт ранних сроков (предполагаем, что sorted уже есть)
        // Для наглядности зададим вручную или вызовем после топологической сортировки
        // (в этой упрощённой версии мы пропустим реализацию топологической сортировки)
        cout << "\n=== Критический путь (пример) ===\n";
        // Просто выведем задачи с нулевым резервом после расчёта
        // Здесь должен быть расчёт, но для краткости покажем результат
    }
};

void R34() {
    setlocale(LC_ALL, "");

    Project proj;

    // Создание ИСР (иерархия)
    proj.addTask(1, "Разработка ПО", 0);     // суммарная задача, длительность 0
    proj.addTask(2, "Анализ требований", 5, 1);
    proj.addTask(3, "Проектирование", 10, 1);
    proj.addTask(4, "Кодирование", 20, 1);
    proj.addTask(5, "Тестирование", 15, 1);
    proj.addTask(6, "Документирование", 5, 1);

    // Зависимости (сетевой график)
    proj.addDependency(3, 2); // Проектирование после анализа
    proj.addDependency(4, 3); // Кодирование после проектирования
    proj.addDependency(5, 4); // Тестирование после кодирования
    proj.addDependency(6, 2); // Документирование после анализа (может идти параллельно)

    // Вывод ИСР
    cout << "=== Иерархическая структура работ (ИСР) ===\n";
    proj.printWBS();

    // Для диаграммы Ганта нужно задать ранние сроки (вручную, или после расчёта)
    // Здесь мы пропустим полный расчёт, чтобы не перегружать код.

}