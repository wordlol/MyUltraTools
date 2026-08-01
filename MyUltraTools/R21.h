#pragma once
/*
 * 21. Нормализация баз данных. Нормальные формы (1НФ, 2НФ, 3НФ, БКНФ).
 * Денормализация.
 *
 * Рассмотрим пример отношения "Экзамены":
 * Исходная таблица (ненорализованная):
 * (StudentID, StudentName, Group, Subjects) – Subjects может быть списком.
 *
 * 1НФ: все атрибуты атомарны. Убираем повторяющиеся группы.
 * (StudentID, StudentName, Group, Subject, Grade)
 *
 * 2НФ: каждый неключевой атрибут полностью зависит от первичного ключа.
 * Первичный ключ (StudentID, Subject). Атрибут StudentName зависит только от StudentID
 * (частичная зависимость), Group – тоже. Выносим их в отдельную таблицу.
 *
 * 3НФ: нет транзитивных зависимостей. Например, если Group -> Faculty (факультет),
 * то Faculty зависит от Group, а Group от StudentID. Выносим Faculty в справочник групп.
 *
 * БКНФ (BCNF): каждый детерминант является потенциальным ключом.
 * Ужесточение 3НФ для случаев пересекающихся потенциальных ключей.
 *
 * Денормализация – намеренное приведение к более низкой нормальной форме
 * для повышения производительности чтения (join дороги).
 * Пример: хранить StudentName прямо в таблице оценок, чтобы избежать join.
 *
 * Сложность нормализации: обычно полиномиальная (поиск замыканий атрибутов).
 * Здесь мы просто моделируем структуры на C++.
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <locale>
#include <stdexcept>

using namespace std;

// ---- 1. Ненормализованное представление (не 1НФ) ----
struct UnnormalizedExam {
    int studentID;
    string studentName;
    string group;
    vector<pair<string, int>> subjects; // список пар (предмет, оценка)
};

// ---- 2. Отношение в 1НФ (атомарные атрибуты) ----
struct Exam1NF {
    int studentID;
    string studentName;
    string group;
    string subject;
    int grade;
};

// ---- 3. Отношения в 2НФ (устранена частичная зависимость) ----
struct Student {
    int studentID;   // primary key
    string studentName;
    string group;
};

struct Exam2NF {
    int studentID;   // foreign key + часть составного ключа
    string subject;  // вторая часть составного ключа
    int grade;
};

// ---- 4. Отношения в 3НФ (устранена транзитивная зависимость) ----
struct Group {
    string groupName; // primary key
    string faculty;
};

struct Student3NF {
    int studentID;    // primary key
    string studentName;
    string group;     // foreign key -> Group
};

struct Exam3NF {
    int studentID;    // foreign key
    string subject;
    int grade;
    // primary key (studentID, subject)
};

// ---- Демонстрация денормализации (обратно к 2НФ для ускорения чтения) ----
struct DenormalizedExam {
    int studentID;
    string studentName; // дублирование данных ради производительности
    string group;
    string subject;
    int grade;
};

// Функция преобразования 1НФ -> 2НФ
pair<vector<Student>, vector<Exam2NF>> decomposeTo2NF(const vector<Exam1NF>& exams) {
    map<int, Student> studentsMap;
    vector<Exam2NF> exams2NF;

    for (auto& e : exams) {
        // Добавляем студента (если ещё нет)
        if (studentsMap.find(e.studentID) == studentsMap.end()) {
            studentsMap[e.studentID] = { e.studentID, e.studentName, e.group };
        }
        exams2NF.push_back({ e.studentID, e.subject, e.grade });
    }

    vector<Student> students;
    for (auto& p : studentsMap) students.push_back(p.second);
    return { students, exams2NF };
}

void R21()
{
    setlocale(LC_ALL, "");

    // Исходные данные (ненормализованные)
    vector<UnnormalizedExam> raw = {
        {1, "Иванов", "ИТ-2021", {{"Математика",5}, {"Физика",4}}},
        {2, "Петров", "ИТ-2021", {{"Математика",3}, {"Информатика",5}}}
    };
    cout << "Ненормализованные данные:\n";
    for (auto& r : raw) {
        cout << r.studentID << " " << r.studentName << " " << r.group << " -> ";
        for (auto& s : r.subjects) cout << s.first << ":" << s.second << " ";
        cout << endl;
    }

    // Преобразование в 1НФ (простое раскрытие списков)
    vector<Exam1NF> exams1NF;
    for (auto& r : raw) {
        for (auto& s : r.subjects) {
            exams1NF.push_back({ r.studentID, r.studentName, r.group, s.first, s.second });
        }
    }
    cout << "\n1НФ (атомарные атрибуты):\n";
    for (auto& e : exams1NF) {
        cout << e.studentID << " " << e.studentName << " " << e.group << " "
            << e.subject << " " << e.grade << endl;
    }

    // Декомпозиция в 2НФ
    auto [students, exams2NF] = decomposeTo2NF(exams1NF);
    cout << "\n2НФ (таблица Students):\n";
    for (auto& s : students) cout << s.studentID << " " << s.studentName << " " << s.group << endl;
    cout << "2НФ (таблица Exams):\n";
    for (auto& e : exams2NF) cout << e.studentID << " " << e.subject << " " << e.grade << endl;

    // Пример денормализации: соединяем обратно для быстрого отчёта
    cout << "\nДенормализованная таблица (быстрый доступ):\n";
    for (auto& e : exams2NF) {
        auto it = find_if(students.begin(), students.end(),
            [&](const Student& s) { return s.studentID == e.studentID; });
        if (it != students.end()) {
            cout << it->studentID << " " << it->studentName << " " << it->group << " "
                << e.subject << " " << e.grade << endl;
        }
    }
}
