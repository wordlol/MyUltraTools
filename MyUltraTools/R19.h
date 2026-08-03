#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <stdexcept>
#include <locale>

using namespace std;

// Кортеж — просто вектор строк
using Tuple = vector<string>;

// Схема отношения: имена атрибутов и позиция первичного ключа (индексы атрибутов)
class RelationSchema {
public:
    vector<string> attributes;      // имена всех атрибутов
    set<size_t> primaryKey;         // индексы атрибутов, входящих в первичный ключ (составной)
    RelationSchema(const vector<string>& attrs, const set<size_t>& pk)
        : attributes(attrs), primaryKey(pk) {
        // проверка, что индексы pk корректны
        for (size_t idx : pk) {
            if (idx >= attrs.size()) throw invalid_argument("Индекс первичного ключа за пределами");
        }
    }
};

// Отношение (таблица) с поддержкой первичного ключа и индекса (вторичного ключа)
class Relation {
    RelationSchema schema_;
    set<Tuple> tuples_;                             // основное хранилище (без дублей)
    set<vector<string>> primaryIndex_;              // множество значений первичного ключа для быстрой проверки
    unordered_map<string, vector<Tuple>> secondaryIndex_; // вторичный индекс по одному атрибуту (например, по ФИО)
    size_t secondaryAttrIndex_;                     // индекс атрибута для вторичного индекса
public:
    Relation(const RelationSchema& schema, size_t secondaryAttr = 0)
        : schema_(schema), secondaryAttrIndex_(secondaryAttr) {
    }

    // Вставка кортежа с проверкой уникальности первичного ключа
    bool insert(const Tuple& t) {
        if (t.size() != schema_.attributes.size())
            throw invalid_argument("Неверное количество атрибутов");

        // Собираем значение первичного ключа
        vector<string> pkValue;
        for (size_t idx : schema_.primaryKey) {
            pkValue.push_back(t[idx]);
        }

        // Проверка уникальности
        if (primaryIndex_.find(pkValue) != primaryIndex_.end()) {
            cout << "Ошибка: нарушение уникальности первичного ключа.\n";
            return false;
        }

        // Вставка
        tuples_.insert(t);
        primaryIndex_.insert(pkValue);

        // Обновляем вторичный индекс (если задан)
        string secondaryValue = t[secondaryAttrIndex_];
        secondaryIndex_[secondaryValue].push_back(t);

        return true;
    }

    // Поиск по вторичному ключу (не уникальный)
    vector<Tuple> findBySecondary(const string& value) const {
        auto it = secondaryIndex_.find(value);
        if (it != secondaryIndex_.end())
            return it->second;
        return {};
    }

    // Вывод всей таблицы
    void print() const {
        // Заголовки
        for (auto& attr : schema_.attributes) cout << attr << "\t";
        cout << "\n---------------------------------\n";
        for (auto& t : tuples_) {
            for (auto& val : t) cout << val << "\t";
            cout << "\n";
        }
    }
};


void R19()
{
    setlocale(LC_ALL, "");

    // Создаём схему: Студенты(StudentID, ФИО, Группа)
    // Первичный ключ: StudentID (индекс 0)
    // Вторичный индекс по ФИО (индекс 1) для быстрого поиска
    RelationSchema schema({ "StudentID", "ФИО", "Группа" }, { 0 });
    Relation students(schema, 1); // вторичный индекс по атрибуту 1 (ФИО)

    // Вставка
    students.insert({ "101", "Иванов И.И.", "ИТ-2021" });
    students.insert({ "102", "Петров П.П.", "ИТ-2021" });
    students.insert({ "103", "Сидоров С.С.", "ИТ-2022" });

    // Попытка вставить дубликат первичного ключа
    students.insert({ "101", "Дубль", "ИТ-2020" }); // Ошибка

    cout << "\nВсе студенты:\n";
    students.print();

    // Поиск по вторичному ключу (ФИО)
    string searchName = "Петров П.П.";
    auto found = students.findBySecondary(searchName);
    if (!found.empty()) {
        cout << "\nНайден по вторичному ключу '" << searchName << "':\n";
        for (auto& t : found) {
            for (auto& val : t) cout << val << " ";
            cout << "\n";
        }
    }
}
