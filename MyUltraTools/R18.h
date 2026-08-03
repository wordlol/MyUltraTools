#pragma once
/*
 * 18. Отношение, атрибут, домен, кортеж в реляционной модели.
 * Связь с теоретико-множественной моделью.
 *
 * Отношение – это подмножество декартова произведения доменов.
 * Атрибут – именованная роль элемента домена в отношении.
 * Домен – множество допустимых значений атрибута.
 * Кортеж – элемент отношения, упорядоченный набор значений атрибутов.
 *
 * Здесь реализованы:
 * - Domain<T> – обёртка над std::set<T> с проверкой принадлежности.
 * - Attribute – имя + указатель на домен (типизированный или универсальный).
 * - Tuple – упорядоченный набор значений (vector<string> для простоты).
 * - Relation – множество кортежей + схема (имена атрибутов и домены).
 *
 * Показаны операции над отношениями как над множествами:
 * объединение, пересечение, разность, декартово произведение.
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include <cassert>
#include <locale>

using namespace std;

// ----- ДОМЕН -----
template <typename T>
class Domain {
    set<T> values_;
public:
    Domain(initializer_list<T> init) : values_(init) {}
    bool contains(const T& val) const { return values_.find(val) != values_.end(); }
    const set<T>& values() const { return values_; }
};

// ----- АТРИБУТ (универсальный, храним значения как строки для простоты) -----
class Attribute {
    string name_;
    shared_ptr<Domain<string>> domain_;  // домен как множество строк
public:
    Attribute(const string& name, shared_ptr<Domain<string>> dom)
        : name_(name), domain_(dom) {
    }
    const string& name() const { return name_; }
    bool isValid(const string& val) const { return domain_->contains(val); }
};

// ----- КОРТЕЖ -----
class Tuple {
    vector<string> data_;
public:
    Tuple(initializer_list<string> vals) : data_(vals) {}
    const string& operator[](size_t i) const { return data_[i]; }
    size_t size() const { return data_.size(); }
    bool operator==(const Tuple& other) const { return data_ == other.data_; }
    bool operator<(const Tuple& other) const { return data_ < other.data_; } // для std::set
};

// ----- ОТНОШЕНИЕ -----
class Relation {
    string name_;
    vector<Attribute> schema_;          // имена и домены атрибутов
    set<Tuple> tuples_;                // множество кортежей (основа – множество!)
public:
    Relation(const string& name, const vector<Attribute>& schema)
        : name_(name), schema_(schema) {
    }

    // Вставка кортежа с проверкой доменов
    bool insert(const Tuple& t) {
        if (t.size() != schema_.size()) return false;
        for (size_t i = 0; i < t.size(); ++i) {
            if (!schema_[i].isValid(t[i])) return false; // нарушение домена
        }
        return tuples_.insert(t).second;
    }

    const set<Tuple>& tuples() const { return tuples_; }
    const vector<Attribute>& schema() const { return schema_; }
    const string& name() const { return name_; }

    // ----- ОПЕРАЦИИ РЕЛЯЦИОННОЙ АЛГЕБРЫ КАК НАД МНОЖЕСТВАМИ -----

    // Объединение (требует совместимости схем)
    static Relation union_(const Relation& a, const Relation& b) {
        assert(a.schema_.size() == b.schema_.size()); // упрощённая проверка
        Relation result("union", a.schema_);
        result.tuples_ = a.tuples_;
        for (auto& t : b.tuples_) result.tuples_.insert(t);
        return result;
    }

    // Пересечение
    static Relation intersect(const Relation& a, const Relation& b) {
        assert(a.schema_.size() == b.schema_.size());
        Relation result("intersect", a.schema_);
        for (auto& t : a.tuples_) {
            if (b.tuples_.find(t) != b.tuples_.end())
                result.tuples_.insert(t);
        }
        return result;
    }

    // Разность (a \ b)
    static Relation difference(const Relation& a, const Relation& b) {
        assert(a.schema_.size() == b.schema_.size());
        Relation result("difference", a.schema_);
        for (auto& t : a.tuples_) {
            if (b.tuples_.find(t) == b.tuples_.end())
                result.tuples_.insert(t);
        }
        return result;
    }

    // Декартово произведение (атрибуты переименовываем для уникальности)
    static Relation cartesianProduct(const Relation& a, const Relation& b) {
        vector<Attribute> newSchema;
        for (auto& attr : a.schema_)
            newSchema.push_back(Attribute(a.name() + "." + attr.name(), nullptr)); // домен опускаем для простоты
        for (auto& attr : b.schema_)
            newSchema.push_back(Attribute(b.name() + "." + attr.name(), nullptr));
        Relation result("product", newSchema);
        for (auto& ta : a.tuples_) {
            for (auto& tb : b.tuples_) {
                std::vector<std::string> vals;
                vals.insert(vals.end(), vals.begin(), vals.end());
                vals.insert(vals.end(), vals.begin(), vals.end());
                result.insert(ta); // теперь insert проверит домены
            }
        }
        return result;
    }

    void print() const {
        cout << "Отношение " << name_ << " (";
        for (size_t i = 0; i < schema_.size(); ++i) {
            if (i) cout << ", ";
            cout << schema_[i].name();
        }
        cout << ")\n";
        for (auto& t : tuples_) {
            cout << "  (";
            for (size_t i = 0; i < t.size(); ++i) {
                if (i) cout << ", ";
                cout << t[i];
            }
            cout << ")\n";
        }
    }
};

void R17()
{
    setlocale(LC_ALL, "");

    // Домены
    auto domColor = make_shared<Domain<string>>(initializer_list<string>{"Red", "Green", "Blue"});
    auto domSize = make_shared<Domain<string>>(initializer_list<string>{"S", "M", "L"});

    // Схемы
    vector<Attribute> schema1 = { Attribute("Цвет", domColor), Attribute("Размер", domSize) };
    vector<Attribute> schema2 = schema1; // одинаковые для операций

    Relation r1("R1", schema1);
    Relation r2("R2", schema2);

    r1.insert({ "Red", "M" });
    r1.insert({ "Blue", "L" });
    r2.insert({ "Red", "M" });
    r2.insert({ "Green", "S" });

    r1.print();
    r2.print();

    auto un = Relation::union_(r1, r2);
    un.print();

    auto inter = Relation::intersect(r1, r2);
    inter.print();

    auto diff = Relation::difference(r1, r2);
    diff.print();

    // Декартово произведение с самим собой для демонстрации
    auto prod = Relation::cartesianProduct(r1, r2);
    prod.print();

}
