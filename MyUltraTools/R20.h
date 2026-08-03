#pragma once
/*
 * 20. Реляционная алгебра: проекция (?), декартово произведение (?),
 *     естественное соединение (?).
 * Формально:
 *  - Проекция: выбор подмножества атрибутов, удаление дубликатов.
 *  - Декартово произведение: каждая строка первой таблицы комбинируется
 *    с каждой строкой второй.
 *  - Естественное соединение: декартово произведение + отбор по равенству
 *    одноимённых атрибутов + удаление повторяющихся столбцов.
 *
 * Сложность (без индексов):
 *  - Проекция: O(n * k + n log n), где n = |R|, k – число сохраняемых атрибутов.
 *  - Декартово произведение: O(|R| * |S|) время и память.
 *  - Соединение: в худшем O(|R| * |S|) (вложенные циклы).
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <locale>

using namespace std;

using Tuple = vector<string>;

struct Relation {
    vector<string> schema;   // имена атрибутов
    set<Tuple> tuples;       // строки (дубликаты не допускаются)
};

// Вспомогательный вывод таблицы
void printRelation(const Relation& r) {
    for (auto& attr : r.schema) cout << attr << "\t";
    cout << "\n";
    for (auto& t : r.tuples) {
        for (auto& val : t) cout << val << "\t";
        cout << "\n";
    }
    cout << endl;
}

// ------------------------------------------------------------
// 1. ПРОЕКЦИЯ (?)
// attrIndices – номера сохраняемых столбцов
Relation projection(const Relation& r, const vector<size_t>& attrIndices) {
    Relation res;
    for (size_t idx : attrIndices) {
        if (idx >= r.schema.size()) throw invalid_argument("Неверный индекс атрибута");
        res.schema.push_back(r.schema[idx]);
    }
    for (auto& t : r.tuples) {
        Tuple newTuple;
        for (size_t idx : attrIndices) newTuple.push_back(t[idx]);
        res.tuples.insert(move(newTuple));   // set удаляет дубликаты
    }
    return res;
}

// ------------------------------------------------------------
// 2. ДЕКАРТОВО ПРОИЗВЕДЕНИЕ (?)
// Имена атрибутов делаем уникальными, добавляя префикс имени таблицы
Relation cartesianProduct(const Relation& a, const string& aName,
    const Relation& b, const string& bName) {
    Relation res;
    for (auto& attr : a.schema) res.schema.push_back(aName + "." + attr);
    for (auto& attr : b.schema) res.schema.push_back(bName + "." + attr);

    for (auto& ta : a.tuples) {
        for (auto& tb : b.tuples) {
            Tuple newTuple = ta;
            newTuple.insert(newTuple.end(), tb.begin(), tb.end());
            res.tuples.insert(move(newTuple));
        }
    }
    return res;
}

// ------------------------------------------------------------
// 3. ЕСТЕСТВЕННОЕ СОЕДИНЕНИЕ (?)
// Ищет общие имена атрибутов, сравнивает их значения, строит результат
Relation naturalJoin(const Relation& a, const Relation& b) {
    // находим общие атрибуты (пары индексов)
    vector<pair<size_t, size_t>> common;
    vector<size_t> a_noncommon, b_noncommon;

    for (size_t i = 0; i < a.schema.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < b.schema.size(); ++j) {
            if (a.schema[i] == b.schema[j]) {
                common.emplace_back(i, j);
                found = true;
                break;
            }
        }
        if (!found) a_noncommon.push_back(i);
    }
    for (size_t j = 0; j < b.schema.size(); ++j) {
        bool found = false;
        for (size_t i = 0; i < a.schema.size(); ++i) {
            if (a.schema[i] == b.schema[j]) { found = true; break; }
        }
        if (!found) b_noncommon.push_back(j);
    }

    // схема результата: общие атрибуты + остальные из a + остальные из b
    Relation res;
    for (auto& p : common) res.schema.push_back(a.schema[p.first]);
    for (size_t i : a_noncommon) res.schema.push_back(a.schema[i]);
    for (size_t j : b_noncommon) res.schema.push_back(b.schema[j]);

    // соединение
    for (auto& ta : a.tuples) {
        for (auto& tb : b.tuples) {
            bool match = true;
            for (auto& p : common) {
                if (ta[p.first] != tb[p.second]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                Tuple newTuple;
                for (auto& p : common) newTuple.push_back(ta[p.first]);
                for (size_t i : a_noncommon) newTuple.push_back(ta[i]);
                for (size_t j : b_noncommon) newTuple.push_back(tb[j]);
                res.tuples.insert(move(newTuple));
            }
        }
    }
    return res;
}

void R20()
{
    setlocale(LC_ALL, "");

    // Таблица R (Студенты)
    Relation R;
    R.schema = { "StudentID", "Name", "Group" };
    R.tuples = {
        {"101", "Иванов", "ИТ-2021"},
        {"102", "Петров", "ИТ-2021"},
        {"103", "Сидоров", "ИТ-2022"}
    };

    // Таблица S (Оценки)
    Relation S;
    S.schema = { "StudentID", "Subject", "Grade" };
    S.tuples = {
        {"101", "Математика", "5"},
        {"101", "Физика", "4"},
        {"102", "Математика", "3"}
    };

    cout << "R:\n"; printRelation(R);
    cout << "S:\n"; printRelation(S);

    // Проекция
    auto proj = projection(R, { 1, 2 }); // Name, Group
    cout << "Проекция R на Name,Group:\n"; printRelation(proj);

    // Декартово произведение
    auto prod = cartesianProduct(R, "R", S, "S");
    cout << "R ? S (первые 5 строк):\n";
    int cnt = 0;
    for (auto& t : prod.tuples) {
        for (auto& val : t) cout << val << " ";
        cout << "\n";
        if (++cnt >= 5) { cout << "... (всего " << prod.tuples.size() << ")\n"; break; }
    }

    // Естественное соединение
    auto join = naturalJoin(R, S);
    cout << "\nR ? S:\n"; printRelation(join);

}
