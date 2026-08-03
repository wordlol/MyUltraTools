#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <locale>

using namespace std;

// Категории сопровождения
enum class Category { Corrective, Adaptive, Perfective, Preventive };

// Приоритет запроса
enum class Priority { Low, Medium, High, Critical };

// Запрос на сопровождение
class MaintenanceRequest {
public:
    int id;
    string description;
    Category category;
    Priority priority;
    time_t creationDate;
    bool resolved = false;

    MaintenanceRequest(int i, const string& desc, Category cat, Priority pri)
        : id(i), description(desc), category(cat), priority(pri), creationDate(time(nullptr)) {
    }

    string categoryToString() const {
        switch (category) {
        case Category::Corrective: return "Корректирующее";
        case Category::Adaptive: return "Адаптивное";
        case Category::Perfective: return "Совершенствующее";
        case Category::Preventive: return "Профилактическое";
        default: return "Неизвестно";
        }
    }
};

// Процесс сопровождения
class MaintenanceProcess {
    vector<shared_ptr<MaintenanceRequest>> requests;
    int nextId = 1;
public:
    // Приём и регистрация запроса
    shared_ptr<MaintenanceRequest> registerRequest(const string& desc, Category cat, Priority pri) {
        auto req = make_shared<MaintenanceRequest>(nextId++, desc, cat, pri);
        requests.push_back(req);
        cout << "[Регистрация] Запрос #" << req->id << " (" << req->categoryToString() << "): " << desc << endl;
        return req;
    }

    // Анализ воздействия (упрощённый)
    void analyzeImpact(shared_ptr<MaintenanceRequest> req) {
        cout << "[Анализ] Оценка влияния запроса #" << req->id << endl;
        // В реальности: проверка затронутых модулей, оценка трудозатрат
        if (req->priority >= Priority::High) {
            cout << "  -> Требуется срочное вмешательство!\n";
        }
    }

    // Разработка и тестирование изменений (имитация)
    void implement(shared_ptr<MaintenanceRequest> req) {
        cout << "[Разработка] Внесение изменений для запроса #" << req->id << endl;
        cout << "[Тестирование] Проверка исправления..." << endl;
        req->resolved = true;
    }

    // Развёртывание
    void deploy(shared_ptr<MaintenanceRequest> req) {
        cout << "[Развёртывание] Поставка исправления для запроса #" << req->id << " в эксплуатацию\n";
    }

    // Полный цикл обработки запроса
    void processRequest(shared_ptr<MaintenanceRequest> req) {
        cout << "\n=== Обработка запроса #" << req->id << " ===" << endl;
        analyzeImpact(req);
        implement(req);
        if (req->resolved) deploy(req);
        else cout << "Ошибка: запрос не решён.\n";
    }

    // Отчётность
    void printSummary() const {
        cout << "\n=== Статистика запросов ===" << endl;
        int total = requests.size(), resolved = 0;
        for (auto& r : requests) if (r->resolved) ++resolved;
        cout << "Всего: " << total << ", решено: " << resolved << ", ожидают: " << total - resolved << endl;
    }
};

// Демонстрация
void R33() {
    setlocale(LC_ALL, "");

    MaintenanceProcess service;

    // Регистрация запросов разных категорий
    auto req1 = service.registerRequest("Ошибка в расчёте налогов", Category::Corrective, Priority::Critical);
    auto req2 = service.registerRequest("Переход на новую версию СУБД", Category::Adaptive, Priority::High);
    auto req3 = service.registerRequest("Ускорить формирование отчёта", Category::Perfective, Priority::Medium);
    auto req4 = service.registerRequest("Рефакторинг старого модуля", Category::Preventive, Priority::Low);

    // Обработка запросов (имитация)
    service.processRequest(req1);
    service.processRequest(req2);
    // req3 и req4 останутся без обработки для демонстрации статуса

    service.printSummary();


}