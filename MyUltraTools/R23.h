#pragma once
/*
 * 23. Целостность БД, ограничения, транзакции.
 *
 * Типы ограничений:
 * 1. Доменная целостность      – значение атрибута принадлежит домену (тип, диапазон, формат).
 * 2. Ограничение на значение столбца (CHECK) – условие на значение (например, > 0).
 * 3. Сущностная целостность    – первичный ключ уникален и не NULL.
 * 4. Ссылочная целостность     – внешний ключ ссылается на существующий кортеж.
 *
 * Транзакция – набор операций, который либо выполняется полностью (COMMIT),
 * либо откатывается (ROLLBACK), сохраняя согласованность.
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <stdexcept>
#include <locale>

using namespace std;

// ====================== Класс Таблица ======================
class Table {
public:
    string name;
    vector<string> columns;
    set<string> pkColumns;                     // имена столбцов первичного ключа
    map<string, function<bool(const string&)>> checks;  // CHECK ограничения (столбец -> предикат)
    // Ссылочная целостность: столбец -> {ссылочная таблица, столбец в той таблице}
    map<string, pair<Table*, string>> foreignKeys;

    vector<map<string, string>> rows;          // строки (каждая строка – map столбец->значение)
    vector<map<string, string>> pendingRows;   // строки, добавленные в текущей транзакции (если активна)
    set<size_t> pendingDeletes;                // индексы удалённых (в транзакции) строк

    bool transactionActive = false;

    Table(const string& n, const vector<string>& cols, const set<string>& pk)
        : name(n), columns(cols), pkColumns(pk) {
    }

    // Проверка доменной целостности (упрощённо: значение не пустое)
    bool checkDomain(const string& value) const {
        return !value.empty();
    }

    // Проверка CHECK ограничений для одного столбца
    bool checkColumnConstraint(const string& col, const string& value) const {
        auto it = checks.find(col);
        if (it != checks.end()) {
            return it->second(value);
        }
        return true;
    }

    // Проверка ссылочной целостности
    bool checkForeignKey(const string& col, const string& value) const {
        auto it = foreignKeys.find(col);
        if (it == foreignKeys.end()) return true;
        Table* refTable = it->second.first;
        const string& refCol = it->second.second;
        // Ищем в целевой таблице строку с таким значением в refCol
        for (auto& row : refTable->rows) {
            if (row.at(refCol) == value) return true;
        }
        // Также проверяем в pendingRows, если активна транзакция
        for (auto& row : refTable->pendingRows) {
            if (row.at(refCol) == value) return true;
        }
        return false;
    }

    // Добавление CHECK ограничения
    void addCheck(const string& col, function<bool(const string&)> pred) {
        checks[col] = pred;
    }

    // Добавление внешнего ключа
    void addForeignKey(const string& col, Table* refTable, const string& refCol) {
        foreignKeys[col] = { refTable, refCol };
    }

    // Поиск строки по первичному ключу (возвращает индекс или -1)
    int findByPK(const map<string, string>& pkValues) const {
        for (size_t i = 0; i < rows.size(); ++i) {
            bool match = true;
            for (auto& pk : pkColumns) {
                if (rows[i].at(pk) != pkValues.at(pk)) {
                    match = false;
                    break;
                }
            }
            if (match) return i;
        }
        return -1;
    }

    // Вставка строки
    void insert(const map<string, string>& values) {
        // Проверка сущностной целостности: все столбцы PK должны быть заданы и не пустые
        for (auto& pk : pkColumns) {
            if (values.count(pk) == 0 || values.at(pk).empty())
                throw runtime_error("Нарушение сущностной целостности: PK не может быть NULL");
        }
        // Проверка доменной целостности
        for (auto& [col, val] : values) {
            if (!checkDomain(val))
                throw runtime_error("Доменная ошибка в столбце " + col);
            if (!checkColumnConstraint(col, val))
                throw runtime_error("CHECK ограничение нарушено для " + col);
        }
        // Проверка ссылочной целостности
        for (auto& [col, val] : values) {
            if (!checkForeignKey(col, val))
                throw runtime_error("Нарушение ссылочной целостности в " + col);
        }
        // Проверка уникальности PK среди существующих строк
        if (findByPK(values) != -1)
            throw runtime_error("Нарушение уникальности первичного ключа");

        if (transactionActive) {
            pendingRows.push_back(values);
        }
        else {
            rows.push_back(values);
        }
    }

    // Удаление строки по первичному ключу
    void remove(const map<string, string>& pkValues) {
        int idx = findByPK(pkValues);
        if (idx == -1) throw runtime_error("Строка не найдена");
        if (transactionActive) {
            pendingDeletes.insert(idx);
        }
        else {
            rows.erase(rows.begin() + idx);
        }
    }

    // Вывод таблицы
    void print() const {
        cout << "[" << name << "]\n";
        for (auto& col : columns) cout << col << "\t";
        cout << "\n";
        for (auto& row : rows) {
            for (auto& col : columns) cout << row.at(col) << "\t";
            cout << "\n";
        }
        cout << endl;
    }

    // ========== Транзакции ==========
    void beginTransaction() {
        if (transactionActive) throw runtime_error("Транзакция уже активна");
        transactionActive = true;
        pendingRows.clear();
        pendingDeletes.clear();
    }

    void commit() {
        if (!transactionActive) throw runtime_error("Нет активной транзакции");
        // Применяем удаления (в порядке убывания индексов, чтобы не сбить индексы)
        for (auto it = pendingDeletes.rbegin(); it != pendingDeletes.rend(); ++it) {
            rows.erase(rows.begin() + *it);
        }
        // Применяем вставки
        for (auto& row : pendingRows) {
            rows.push_back(row);
        }
        transactionActive = false;
        pendingRows.clear();
        pendingDeletes.clear();
    }

    void rollback() {
        if (!transactionActive) throw runtime_error("Нет активной транзакции");
        transactionActive = false;
        pendingRows.clear();
        pendingDeletes.clear();
    }
};

void R23()
{
    setlocale(LC_ALL, "");

    // 1. Создаём таблицу Студенты
    Table students("Студенты", { "StudentID", "ФИО", "Возраст", "Группа" }, { "StudentID" });
    // CHECK ограничение: возраст > 0 и < 100
    students.addCheck("Возраст", [](const string& v) {
        int age = stoi(v);
        return age > 0 && age < 100;
        });

    // Вставляем несколько студентов
    students.insert({ {"StudentID","1"}, {"ФИО","Иванов"}, {"Возраст","20"}, {"Группа","ИТ-21"} });
    students.insert({ {"StudentID","2"}, {"ФИО","Петров"}, {"Возраст","21"}, {"Группа","ИТ-21"} });
    students.print();

    // 2. Создаём таблицу Зачётки (ссылается на Студенты)
    Table recordBooks("Зачётки", { "RecordID", "StudentID", "ДатаВыдачи" }, { "RecordID" });
    recordBooks.addForeignKey("StudentID", &students, "StudentID");

    // Вставляем зачётку для существующего студента (1) – ок
    recordBooks.insert({ {"RecordID","1001"}, {"StudentID","1"}, {"ДатаВыдачи","2023-09-01"} });
    // Попытка вставить зачётку для несуществующего студента (99) – нарушение ссылочной целостности
    try {
        recordBooks.insert({ {"RecordID","1002"}, {"StudentID","99"}, {"ДатаВыдачи","2023-09-01"} });
    }
    catch (exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    // 3. Транзакция: добавляем студента и его зачётку атомарно
    cout << "\n=== Транзакция ===" << endl;
    students.beginTransaction();
    recordBooks.beginTransaction();

    students.insert({ {"StudentID","3"}, {"ФИО","Сидоров"}, {"Возраст","22"}, {"Группа","ИТ-22"} });
    recordBooks.insert({ {"RecordID","1003"}, {"StudentID","3"}, {"ДатаВыдачи","2023-09-05"} });

    // Пока транзакция не завершена, в основных данных изменений нет
    cout << "Студенты (до коммита):\n"; students.print();
    cout << "Зачётки (до коммита):\n"; recordBooks.print();

    // Фиксируем транзакцию
    students.commit();
    recordBooks.commit();

    cout << "После коммита:\n";
    students.print();
    recordBooks.print();

    // 4. Откат транзакции
    cout << "\n=== Откат транзакции ===" << endl;
    students.beginTransaction();
    students.insert({ {"StudentID","4"}, {"ФИО","Кузнецов"}, {"Возраст","25"}, {"Группа","ИТ-23"} });
    // Передумали – откатываем
    students.rollback();
    cout << "После отката:\n";
    students.print(); // Кузнецова нет
}
