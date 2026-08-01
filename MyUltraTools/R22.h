#pragma once
/*
 * 22. Информационный объект (сущность), атрибут, виды связей.
 *
 * Информационный объект (Entity) – нечто, о чем мы храним данные (студент, курс, преподаватель).
 * Атрибут – свойство объекта (имя, возраст, название).
 * Связь (Relationship) – ассоциация между объектами.
 *
 * Виды связей:
 *   - "один-к-одному" (1:1): каждому экземпляру A соответствует ровно один B, и наоборот.
 *   - "один-ко-многим" (1:M): экземпляру A соответствует несколько B, но каждому B – только один A.
 *   - "многие-ко-многим" (M:N): экземпляру A может соответствовать несколько B, и наоборот.
 *
 * Реализация в реляционной модели:
 *   1:1 – либо объединяют в одну таблицу, либо первичный ключ одной таблицы одновременно внешний ключ в другой.
 *   1:M – в таблицу "многих" добавляют внешний ключ к "одному".
 *   M:N – создают промежуточную таблицу с двумя внешними ключами.
 *
 * Данный код моделирует сущности и связи на C++ для демонстрации концепций.
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <locale>

using namespace std;

// ------------------- Базовые классы -------------------

// Атрибут сущности
struct Attribute {
    string name;
    string type; // для простоты – "int", "string" и т.д.
    Attribute(const string& n, const string& t) : name(n), type(t) {}
};

// Информационный объект (сущность)
class Entity {
public:
    string name;
    vector<Attribute> attributes;
    // Словарь экземпляров: первичный ключ -> значения атрибутов в порядке attributes
    unordered_map<int, vector<string>> instances;
    int nextKey = 1;

    Entity(const string& n, const vector<Attribute>& attrs) : name(n), attributes(attrs) {}

    // Добавить экземпляр, возвращает присвоенный ключ
    int addInstance(const vector<string>& values) {
        if (values.size() != attributes.size())
            throw invalid_argument("Неверное количество значений");
        int key = nextKey++;
        instances[key] = values;
        return key;
    }

    // Получить значение атрибута по ключу
    string getValue(int key, const string& attrName) const {
        auto it = instances.find(key);
        if (it == instances.end()) throw runtime_error("Экземпляр не найден");
        for (size_t i = 0; i < attributes.size(); ++i) {
            if (attributes[i].name == attrName) return it->second[i];
        }
        throw runtime_error("Атрибут не найден");
    }

    // Вывести все экземпляры
    void print() const {
        cout << "[" << name << "]\n";
        for (auto& attr : attributes) cout << attr.name << "\t";
        cout << "\n";
        for (auto& [key, vals] : instances) {
            cout << key << ": ";
            for (auto& v : vals) cout << v << "\t";
            cout << "\n";
        }
    }
};

// Абстрактный класс связи
class Relationship {
protected:
    string name;
public:
    Relationship(const string& n) : name(n) {}
    virtual void print() const = 0;
    virtual ~Relationship() = default;
};

// Связь 1:1
// Хранит пары ключей (keyA, keyB)
class OneToOne : public Relationship {
    set<pair<int, int>> links;
public:
    OneToOne(const string& n) : Relationship(n) {}

    void link(int keyA, int keyB) {
        // проверка, что каждый ключ участвует не более чем в одной связи
        for (auto& [a, b] : links) {
            if (a == keyA || b == keyB)
                throw runtime_error("Нарушение 1:1");
        }
        links.insert({ keyA, keyB });
    }

    void print() const override {
        cout << "Связь '" << name << "' (1:1):\n";
        for (auto& [a, b] : links) cout << a << " <-> " << b << "\n";
    }
};

// Связь 1:M (One-to-Many)
class OneToMany : public Relationship {
    unordered_map<int, vector<int>> links; // один -> список многих
    set<int> manyKeys; // для проверки, что many-ключ связан только с одним
public:
    OneToMany(const string& n) : Relationship(n) {}

    void link(int oneKey, int manyKey) {
        if (manyKeys.count(manyKey))
            throw runtime_error("Нарушение 1:M: many-ключ уже связан");
        links[oneKey].push_back(manyKey);
        manyKeys.insert(manyKey);
    }

    void print() const override {
        cout << "Связь '" << name << "' (1:M):\n";
        for (auto& [one, manys] : links) {
            cout << one << " -> ";
            for (int m : manys) cout << m << " ";
            cout << "\n";
        }
    }
};

// Связь M:N
class ManyToMany : public Relationship {
    set<pair<int, int>> links;
public:
    ManyToMany(const string& n) : Relationship(n) {}

    void link(int keyA, int keyB) {
        links.insert({ keyA, keyB });
    }

    void print() const override {
        cout << "Связь '" << name << "' (M:N):\n";
        for (auto& [a, b] : links) cout << a << " <-> " << b << "\n";
    }
};

void R22()
{

    setlocale(LC_ALL, "");

    // Сущность "Студент"
    Entity student("Студент", { {"StudentID", "int"}, {"ФИО", "string"}, {"Группа", "string"} });
    int s1 = student.addInstance({ "1", "Иванов", "ИТ-2021" });
    int s2 = student.addInstance({ "2", "Петров", "ИТ-2021" });
    int s3 = student.addInstance({ "3", "Сидоров", "ИТ-2022" });
    student.print();

    // Сущность "Преподаватель"
    Entity teacher("Преподаватель", { {"TeacherID", "int"}, {"ФИО", "string"}, {"Кафедра", "string"} });
    int t1 = teacher.addInstance({ "101", "Попов", "Информатика" });
    int t2 = teacher.addInstance({ "102", "Смирнова", "Математика" });
    teacher.print();

    // Сущность "Курс"
    Entity course("Курс", { {"CourseID", "int"}, {"Название", "string"}, {"Часы", "int"} });
    int c1 = course.addInstance({ "201", "Алгоритмы", "72" });
    int c2 = course.addInstance({ "202", "Базы данных", "108" });
    course.print();

    // Связь 1:1 – зачётная книжка (один студент – одна книжка)
    OneToOne oto("Имеет_зачётку");
    oto.link(s1, 1001);
    oto.link(s2, 1002);
    oto.link(s3, 1003);
    oto.print();

    // Связь 1:M – преподаватель ведёт курсы (один преподаватель – много курсов)
    OneToMany otm("Ведёт");
    otm.link(t1, c1);
    otm.link(t1, c2);
    // otm.link(t2, c1); // нарушит 1:M, если раскомментировать – бросит исключение
    otm.print();

    // Связь M:N – студенты записаны на курсы
    ManyToMany mtm("Записан_на");
    mtm.link(s1, c1);
    mtm.link(s1, c2);
    mtm.link(s2, c1);
    mtm.link(s3, c2);
    mtm.print();

}

