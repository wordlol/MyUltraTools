#pragma once

//@startuml
//left to right direction
//
//actor "Покупатель" as Customer
//actor "Администратор" as Admin
//
//rectangle "Интернет-магазин" {
//    usecase "Просмотр товаров" as UC1
//        usecase "Добавление в корзину" as UC2
//        usecase "Оформление заказа" as UC3
//        usecase "Управление товарами" as UC4
//        usecase "Просмотр отчётов" as UC5
//        usecase "Авторизация" as UC6
//}
//
//Customer-- > UC1
//Customer-- > UC2
//Customer-- > UC3
//Admin-- > UC4
//Admin-- > UC5
//UC3 .. > UC6 : << include >>
//UC4 .. > UC6 : << include >>
//@enduml


//@startuml
//| Покупатель |
//start
//    :Выбирает товары;
//: Нажимает "Оформить заказ";
//
//| Система |
//    :Проверяет наличие товаров;
//if (Все доступны ? ) then(да)
//    :Резервирует товары;
//: Рассчитывает стоимость;
//| Покупатель |
//    :Оплачивает заказ;
//| Система |
//if (Оплата успешна ? ) then(да)
//    :Формирует заказ;
//: Уведомляет склад;
//| Покупатель |
//    :Получает подтверждение;
//stop
//else (нет)
//    : Отменяет резервирование;
//| Покупатель |
//    :Получает отказ;
//stop
//endif
//else (нет)
//| Покупатель |
//    :Уведомление о недоступности;
//stop
//endif
//@enduml


// Контроллер для варианта использования "Оформление заказа"
//class OrderController {
//    bool authorize(const std::string& token) { /* ... */ return true; }
//    bool checkStock(const std::vector<int>& productIds) { /* ... */ return true; }
//    double calculateTotal(const std::vector<pair<int, int>>& items) { /* ... */ return 0.0; }
//    bool chargePayment(double amount) { /* ... */ return true; }
//    void sendConfirmation() { /* ... */ }
//public:
//    bool placeOrder(const std::string& token, const std::vector<pair<int, int>>& items) {
//        if (!authorize(token)) return false;
//        if (!checkStock( ... )) return false;
//        double total = calculateTotal(items);
//        if (!chargePayment(total)) return false;
//        sendConfirmation();
//        return true;
//    }
//};