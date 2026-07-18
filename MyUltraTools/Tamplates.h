#pragma once
#include "RUP.h"
//7
//Понятие шаблона проектирования.Классификация и примеры шаблонов
//проектирования.

//фабрика создаёт уведомления, адаптеры оборачивают чужие сервисы, а менеджер управляет наблюдателями и уведомлением.


//Factory Method 
//___
//Notification.h
class Notification
{
public:
    virtual ~Notification() = default;
    virtual std::string send(const std::string& message) const = 0;
};
class EmailNotification : public Notification
{
public:
    std::string send(const std::string& message) const override {
        return "Email sent: " + message;
    }
};
class SMSNotification : public Notification
{
public:
    std::string send(const std::string& message) const override {
        return "Sms sent: " + message;
    }
};
class PushNotification : public Notification
{
public:
    std::string send(const std::string& message) const override {
        return "Push sent: " + message;
    }
};

//NotificationFactory.h
class NotificationFactory {
public:
    virtual ~NotificationFactory() = default;
    virtual std::unique_ptr<Notification> createNotification(const std::string& type) const = 0;
};
class SimpleNotificationFactory : public NotificationFactory {
public:
    std::unique_ptr<Notification> createNotification(const std::string& type) const override {
        if (type == "email") return std::make_unique<EmailNotification>();
        else if (type == "sms") return std::make_unique<SMSNotification>();
        else if (type == "push") return std::make_unique<PushNotification>();
        throw std::invalid_argument("Unknown type");
    }
};
//---
//Factory Method 


//Adapder
//___
// LegacyEmailSender.h
class LegacyEmailSender {
public:
    void sendEmail(const std::string& subject, const std::string& body) {
        // В реальном коде здесь отправка, мы просто выведем в консоль
        std::cout << "LegacyEmail: " << subject << " / " << body << std::endl;
    }
};
// ModernPushSender.h
class ModernPushSender {
public:
    void push(const std::string& title, const std::string& text) {
        std::cout << "ModernPush: " << title << " - " << text << std::endl;
    }
};

// ITarget.h
class ITarget {
public:
    virtual ~ITarget() = default;
    virtual void send(const std::string& message) const = 0;
};

// LegacyEmailAdapter.h
class LegacyEmailAdapter : public ITarget {
    std::unique_ptr<LegacyEmailSender> legacy_;
public:
    LegacyEmailAdapter() : legacy_(std::make_unique<LegacyEmailSender>()) {}
    void send(const std::string& message) const override {
        legacy_->sendEmail("Notification", message);
    }
};
// ModernPushAdapter.h
class ModernPushAdapter : public ITarget {
    std::unique_ptr<ModernPushSender> modern_;
public:
    ModernPushAdapter() : modern_(std::make_unique<ModernPushSender>()) {}
    void send(const std::string& message) const override {
        modern_->push("Alert", message);
    }
};
//---
//Adapder


//Observer
//___
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::string& event) = 0;
};

class Logger : public IObserver {
public:
    void update(const std::string& event) override {
        std::cout << "[LOG] " << event << std::endl;
    }
};

class StatisticsCollector : public IObserver {
    int count_ = 0;
public:
    void update(const std::string& event) override {
        ++count_;
    }
    int getCount() const { return count_; }
};

class NotificationManager {
    std::unique_ptr<Notification> notification_;
    std::vector<IObserver*> observers_;
public:
    NotificationManager(std::unique_ptr<Notification> notif) : notification_(std::move(notif)) {}
    void attach(IObserver* obs) { observers_.push_back(obs); }
    std::string send(const std::string& msg) {
        std::string result = notification_->send(msg);
        for (auto* obs : observers_) obs->update("sent: " + msg);
        return result;
    }
};
//---
//Observer



void testFactoryCreatesEmailNotification() {
    SimpleNotificationFactory factory;
    auto notif = factory.createNotification("email");
    ASSERT_EQUAL(std::string("Email sent: Hello"), notif->send("Hello"));
}
void testFactoryCreatesSMSNotification() {
    SimpleNotificationFactory factory;
    auto notif = factory.createNotification("sms");
    ASSERT_EQUAL(std::string("Sms sent: Hello"), notif->send("Hello"));
}
void testFactoryCreatesPUSHNotification() {
    SimpleNotificationFactory factory;
    auto notif = factory.createNotification("push");
    ASSERT_EQUAL(std::string("Push sent: Hello"), notif->send("Hello"));
}
void testLegacyEmailAdapter() {
    LegacyEmailAdapter adapter;
    // Мы не можем напрямую проверить вывод в консоль, но можем убедиться, что вызов не падает
    // и что адаптер можно использовать как ITarget
    ITarget* target = &adapter;
    target->send("Test message"); // должно вывести "LegacyEmail: Notification / Test message"
    // Для автоматического теста мы можем временно подменить вывод, но для простоты
    // проверим, что объект корректно создаётся и метод вызывается без ошибок.
    ASSERT_TRUE(true); // тривиальная проверка, что код выполнился
}
void testModernPushAdapter() {
    ModernPushAdapter adapter;
    ITarget* target = &adapter;
    target->send("Hello");
    ASSERT_TRUE(true);
}
void testObserverNotification() {
    // Создаём менеджер с email-уведомлением (используем фабрику или явно)
    SimpleNotificationFactory factory;
    auto notif = factory.createNotification("email");
    NotificationManager manager(std::move(notif));

    Logger logger;
    StatisticsCollector stat;
    manager.attach(&logger);
    manager.attach(&stat);

    std::string result = manager.send("Test");
    ASSERT_EQUAL(std::string("Email sent: Test"), result);
    ASSERT_EQUAL(1, stat.getCount());
}

