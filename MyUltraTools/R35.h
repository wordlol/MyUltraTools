#pragma once
//@startuml
//left to right direction
//
//rectangle "Покупатель" as Customer
//rectangle "Складская система" as Warehouse
//rectangle "Система заказа товаров" as System
//
//Customer-- > System : Запрос на просмотр товаров, Заказ
//System-- > Customer : Список товаров, Подтверждение заказа
//System-- > Warehouse : Данные заказа
//Warehouse-- > System : Подтверждение наличия, Отгрузка
//@enduml
//
//
//@startuml
//left to right direction
//
//rectangle "Покупатель" as Customer
//rectangle "Складская система" as Warehouse
//
//rectangle "1. Обработать\nпросмотр товаров" as Proc1
//rectangle "2. Принять\nзаказ" as Proc2
//rectangle "3. Проверить\nналичие" as Proc3
//rectangle "4. Сформировать\nзаказ" as Proc4
//
//database "Товары" as Products
//database "Заказы" as Orders
//
//Customer-- > Proc1 : Запрос списка товаров
//Proc1-- > Customer : Список товаров
//Proc1-- > Products : Читать товары
//
//Customer-- > Proc2 : Заказ
//Proc2-- > Proc3 : Данные заказа
//Proc3-- > Products : Проверить остатки
//Products-- > Proc3 : Остатки
//Proc3-- > Proc4 : Подтверждённый заказ
//Proc4-- > Orders : Сохранить заказ
//Proc4-- > Warehouse : Уведомление о заказе
//Warehouse-- > Proc4 : Подтверждение отгрузки
//Proc4-- > Customer : Подтверждение заказа
//@enduml


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <locale>

using namespace std;

// Хранилище данных "Товары"
class ProductStore {
    map<int, pair<string, int>> products; // id -> (название, остаток)
public:
    void addProduct(int id, const string& name, int stock) {
        products[id] = { name, stock };
    }
    bool checkStock(int id, int quantity) const {
        auto it = products.find(id);
        return it != products.end() && it->second.second >= quantity;
    }
    string getProductList() const {
        string list;
        for (auto& [id, p] : products)
            list += to_string(id) + ": " + p.first + " (" + to_string(p.second) + ")\n";
        return list;
    }
};

// Хранилище данных "Заказы"
class OrderStore {
    struct Order {
        int id;
        vector<pair<int, int>> items; // (productId, quantity)
        bool confirmed = false;
    };
    vector<Order> orders;
    int nextId = 1;
public:
    int createOrder(const vector<pair<int, int>>& items) {
        orders.push_back({ nextId, items, false });
        return nextId++;
    }
    void confirmOrder(int id) {
        for (auto& o : orders) if (o.id == id) o.confirmed = true;
    }
};

// Внешняя сущность "Покупатель"
class Customer {
public:
    void viewProducts(const string& list) {
        cout << "[Покупатель] Просмотр товаров:\n" << list;
    }
    vector<pair<int, int>> makeOrder() {
        // В реальности ввод, здесь заглушка
        cout << "[Покупатель] Формирую заказ...\n";
        return { {1, 2}, {2, 1} };
    }
    void receiveConfirmation(int orderId) {
        cout << "[Покупатель] Получено подтверждение заказа #" << orderId << endl;
    }
};

// Внешняя сущность "Складская система"
class WarehouseSystem {
public:
    void notify(int orderId) {
        cout << "[Склад] Уведомление о заказе #" << orderId << endl;
    }
    bool confirmShipping() {
        cout << "[Склад] Подтверждение отгрузки...\n";
        return true;
    }
};

// Процесс 1: Обработать просмотр товаров
void processViewProducts(ProductStore& store, Customer& customer) {
    string list = store.getProductList();
    customer.viewProducts(list);
}

// Процесс 2+3+4: Принять заказ, проверить наличие, сформировать заказ
int processOrder(Customer& customer, ProductStore& store, OrderStore& orders, WarehouseSystem& warehouse) {
    auto items = customer.makeOrder();
    // Проверка наличия
    for (auto& [pid, qty] : items) {
        if (!store.checkStock(pid, qty)) {
            cout << "[Система] Недостаточно товара " << pid << endl;
            return -1;
        }
    }
    // Создание и сохранение заказа
    int orderId = orders.createOrder(items);
    orders.confirmOrder(orderId);
    // Уведомление склада
    warehouse.notify(orderId);
    warehouse.confirmShipping();
    // Подтверждение покупателю
    customer.receiveConfirmation(orderId);
    return orderId;
}

void R35() {
    setlocale(LC_ALL, "");

    // Инициализация
    ProductStore products;
    products.addProduct(1, "Ноутбук", 10);
    products.addProduct(2, "Мышь", 50);

    OrderStore orders;
    Customer customer;
    WarehouseSystem warehouse;

    // Поток: просмотр товаров (процесс 1)
    cout << "=== Процесс 1: Просмотр товаров ===" << endl;
    processViewProducts(products, customer);

    // Поток: оформление заказа (процессы 2-4)
    cout << "\n=== Процессы 2-4: Заказ ===" << endl;
    int orderId = processOrder(customer, products, orders, warehouse);
    if (orderId != -1) cout << "Заказ #" << orderId << " успешно оформлен.\n";

}