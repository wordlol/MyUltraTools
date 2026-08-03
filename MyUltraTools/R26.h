#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <variant>
#include <stdexcept>
#include <locale>

//4. Ключевые отличия(резюме)
//Характеристика	Реляционные СУБД	NoSQL СУБД
//Модель данных	Таблицы, строки, столбцы, фиксированная схема	Документы, ключ - значение, графы, колонки; гибкая схема
//Язык запросов	Стандартный SQL(DDL, DML, DCL, TCL)	Специфичные API(MQL, Cypher, Redis commands)
//Транзакции	ACID(атомарность, согласованность, изоляция, долговечность)	BASE(обычно согласованность в конечном счёте)
//Масштабирование	В основном вертикальное	Горизонтальное(шардинг, кластеры)
//JOIN	Эффективные средства соединения таблиц	Редко поддерживается, часто денормализация
//Примеры	PostgreSQL, MySQL, SQL Server	MongoDB, Redis, Cassandra, Neo4j

using namespace std;

// Тип для одного поля документа (может быть int, string или вложенный map)
using FieldValue = variant<int, string, map<string, string>>;

// Документ – это словарь строковых ключей с произвольными значениями
using Document = map<string, FieldValue>;

// --- Эмуляция реляционного подхода ---
class RelationalDB {
    struct User {
        int id;
        string name;
        string email;
    };
    vector<User> users;
public:
    void addUser(int id, const string& name, const string& email) {
        if (name.empty() || email.empty())
            throw invalid_argument("Поля name и email обязательны");
        users.push_back({ id, name, email });
    }

    User* findUserByEmail(const string& email) {
        for (auto& u : users) {
            if (u.email == email) return &u;
        }
        return nullptr;
    }
};

// --- Эмуляция документного NoSQL подхода ---
class DocumentDB {
    vector<Document> docs;
public:
    void addDocument(const Document& doc) {
        docs.push_back(doc);
    }

    // Поиск по ключу и значению (только для string/int)
    Document* findDocument(const string& key, const FieldValue& value) {
        for (auto& doc : docs) {
            auto it = doc.find(key);
            if (it != doc.end() && it->second == value) return &doc;
        }
        return nullptr;
    }
};

void R26()
{
    setlocale(LC_ALL, "");

    // Реляционный пример
    RelationalDB rdb;
    try {
        rdb.addUser(1, "Иванов", "ivanov@example.com");
        auto user = rdb.findUserByEmail("ivanov@example.com");
        if (user) cout << "Найден: " << user->name << ", " << user->email << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка реляционной БД: " << e.what() << endl;
    }

    // Документный пример
    DocumentDB ndb;
    Document doc1 = {
        {"_id", 1},
        {"name", "Иванов"s},
        {"email", "ivanov@example.com"s},
        {"preferences", map<string, string>{{"theme", "dark"}, {"lang", "ru"}}}
    };
    ndb.addDocument(doc1);

    // Поиск по полю "email"
    auto found = ndb.findDocument("email", "ivanov@example.com"s);
    if (found) {
        cout << "Найден документ:\n";
        for (auto& [key, val] : *found) {
            cout << "  " << key << ": ";
            if (holds_alternative<int>(val)) cout << get<int>(val);
            else if (holds_alternative<string>(val)) cout << get<string>(val);
            else if (holds_alternative<map<string, string>>(val)) {
                cout << "{ ";
                for (auto& [k, v] : get<map<string, string>>(val)) cout << k << ": " << v << " ";
                cout << "}";
            }
            cout << endl;
        }
    }
}


//java script
//// Коллекция users (без жёсткой схемы)
//db.users.insertOne({
//    _id: 1,
//    name : "Иванов",
//    email : "ivanov@example.com",
//    preferences : { theme: "dark" } // произвольное вложенное поле
//    });
//
//// Запрос без JOIN, вложенные документы
//db.orders.aggregate([
//{
//$lookup: {
//from: "users",
//localField : "user_id",
//foreignField : "_id",
//as : "user"
//    }
//},
//{ $match: { amount: { $gt: 100 } } }
//]);