#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

enum class OrderStatus { New, Processing, Shipped, Delivered, Cancelled };

class Product {
    int id;
    string name;
    double price;
    int stock;
public:
    Product(int i, const string& n, double p, int s) : id(i), name(n), price(p), stock(s) {}
    bool isAvailable() const { return stock > 0; }
    // геттеры...
};

class OrderItem {
    shared_ptr<Product> product;
    int quantity;
    double price;
public:
    OrderItem(shared_ptr<Product> p, int qty) : product(p), quantity(qty), price(p->isAvailable() ? /*getPrice()*/ 0 : 0) {}
};

class Order {
    int id;
    vector<shared_ptr<OrderItem>> items;
    OrderStatus status = OrderStatus::New;
public:
    Order(int i) : id(i) {}
    void addItem(shared_ptr<OrderItem> item) { items.push_back(item); }
    double calculateTotal() const {
        double total = 0;
        for (auto& item : items) total += /*item->getPrice()*/ 0; // упрощение
        return total;
    }
};

class Customer {
    int id;
    string name, email;
    vector<shared_ptr<Order>> orders;
public:
    Customer(int i, const string& n, const string& e) : id(i), name(n), email(e) {}
    void placeOrder(shared_ptr<Order> order) { orders.push_back(order); }
};


//@startuml
//node "Client Browser" as browser
//
//node "DMZ" {
//    node "Load Balancer" as lb
//        node "Web Server 1" as web1
//        node "Web Server 2" as web2
//}
//
//node "Application Server" as app{
//    artifact "OrderService.jar"
//    artifact "PaymentService.jar"
//}
//
//node "Database Server" as db{
//    node "Primary DB" as db_primary
//    node "Replica DB" as db_replica
//}
//
//browser-- > lb : HTTPS
//lb-- > web1 : HTTP
//lb-- > web2 : HTTP
//web1-- > app : RMI / CORBA
//web2-- > app
//app-- > db_primary : JDBC(write)
//app-- > db_replica : JDBC(read)
//@enduml