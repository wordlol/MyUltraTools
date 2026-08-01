#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//3. Сравнительный анализ(таблица)
//Характеристика	SOA	Microservices
//Размер сервисов	Крупные(бизнес - функции)	Мелкие(одна задача)
//Интеграция	Часто через ESB, SOAP / WSDL	Легковесная(REST, gRPC, события)
//Данные	Могут разделяться(общая БД)	Каждый сервис владеет своей БД
//Управление	Централизованное	Децентрализованное
//Развёртывание	Обычно монолитное	Независимое развёртывание
//Связанность	Высокая(сервис знает о других)	Низкая(независимые контракты)

// SOA: один крупный сервис управляет всем
class OrderService {
public:
    void processOrder(const string& orderId) {
        cout << "[SOA] Создание заказа " << orderId << endl;
        reserveInventory(orderId);
        processPayment(orderId);
        sendNotification(orderId, "Заказ создан");
    }
private:
    // В SOA все функции внутри одного сервиса (или через ESB)
    void reserveInventory(const string& orderId) {
        cout << "  Резервирование товара для " << orderId << endl;
    }
    void processPayment(const string& orderId) {
        cout << "  Обработка платежа для " << orderId << endl;
    }
    void sendNotification(const string& orderId, const string& msg) {
        cout << "  Уведомление: " << msg << " по заказу " << orderId << endl;
    }
};

// Пример использования
void SOA() {
    cout << "=== Демонстрация SOA ===" << endl;
    OrderService service;
    service.processOrder("Order-001");
}


#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <queue>
#include <functional>
using namespace std;

// Асинхронная шина сообщений (упрощённый брокер)
class MessageBus {
    unordered_map<string, vector<function<void(const string&)>>> subscribers;
public:
    void subscribe(const string& event, function<void(const string&)> handler) {
        subscribers[event].push_back(handler);
    }
    void publish(const string& event, const string& data) {
        for (auto& handler : subscribers[event])
            handler(data);
    }
};

// Микросервис заказов
class OrderMicroservice {
    shared_ptr<MessageBus> bus;
public:
    OrderMicroservice(shared_ptr<MessageBus> bus) : bus(bus) {
        bus->subscribe("order.created", [this](const string& orderId) {
            cout << "[OrderService] Создан заказ: " << orderId << endl;
            });
    }
    void createOrder(const string& orderId) {
        cout << "[OrderService] Инициирую создание заказа " << orderId << endl;
        bus->publish("order.created", orderId); // асинхронное уведомление
    }
};

// Микросервис платежей
class PaymentMicroservice {
    shared_ptr<MessageBus> bus;
public:
    PaymentMicroservice(shared_ptr<MessageBus> bus) : bus(bus) {
        bus->subscribe("order.created", [this](const string& orderId) {
            cout << "[PaymentService] Обрабатываю платеж для " << orderId << endl;
            this->bus->publish("payment.completed", orderId);  // используем поле класса
            });
    }
};

// Микросервис уведомлений
class NotificationMicroservice {
    shared_ptr<MessageBus> bus;
public:
    NotificationMicroservice(shared_ptr<MessageBus> bus) : bus(bus) {
        bus->subscribe("payment.completed", [this](const string& orderId) {
            cout << "[NotificationService] Уведомление: заказ " << orderId << " оплачен." << endl;
            });
    }
};
void Microservice() {
    cout << "\n=== Демонстрация Microservices ===" << endl;
    auto bus = make_shared<MessageBus>();

    OrderMicroservice orderService(bus);
    PaymentMicroservice paymentService(bus);
    NotificationMicroservice notificationService(bus);

    // Создаём заказ – каждый сервис реагирует независимо
    orderService.createOrder("Order-002");

}