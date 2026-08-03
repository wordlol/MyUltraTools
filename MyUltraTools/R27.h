#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <locale>

using namespace std;

// ------------------- Требование -------------------
enum class Priority { High, Medium, Low };
enum class ReqStatus { New, Approved, Implemented, Tested };

class Requirement {
public:
    int id;
    string description;
    Priority priority;
    ReqStatus status;

    Requirement(int i, const string& desc, Priority p = Priority::Medium)
        : id(i), description(desc), priority(p), status(ReqStatus::New) {
    }
};

// ------------------- Тестовый случай -------------------
class TestCase {
public:
    int id;
    string description;
    vector<string> steps;
    string expectedResult;
    int requirementId;   // связь с требованием (внешний ключ)

    TestCase(int i, const string& desc, int reqId)
        : id(i), description(desc), requirementId(reqId) {
    }
};

// ------------------- Менеджер требований и тестов -------------------
class RequirementManager {
    vector<Requirement> requirements;
    vector<TestCase> testCases;
    int nextReqId = 1;
    int nextTestId = 1;

public:
    // Добавление требования
    Requirement* addRequirement(const string& desc, Priority prio = Priority::Medium) {
        requirements.emplace_back(nextReqId, desc, prio);
        return &requirements.back();
    }

    // Генерация тестового случая на основе требования (имитация полуавтоматической генерации)
    TestCase* generateTestForRequirement(int reqId) {
        auto req = find_if(requirements.begin(), requirements.end(),
            [reqId](const Requirement& r) { return r.id == reqId; });
        if (req == requirements.end()) {
            cerr << "Требование с id " << reqId << " не найдено.\n";
            return nullptr;
        }
        // Формируем простой тест: проверяем, что требование реализовано
        string desc = "Тест для требования #" + to_string(reqId) + ": " + req->description;
        testCases.emplace_back(nextTestId, desc, reqId);
        TestCase* tc = &testCases.back();
        // Предзаполняем шаги и ожидаемый результат (в реальности - вручную или из шаблона)
        tc->steps.push_back("Шаг 1: Выполнить действие, связанное с требованием");
        tc->steps.push_back("Шаг 2: Проверить результат");
        tc->expectedResult = "Система выполняет " + req->description + " корректно";
        return tc;
    }

    // Проверка покрытия требований тестами (Traceability Matrix)
    void checkCoverage() const {
        cout << "\n=== Матрица покрытия требований тестами ===\n";
        cout << "ReqID\tОписание\t\tСтатус\t\tТестов (ID)\n";
        cout << "------------------------------------------------------------\n";

        for (auto& req : requirements) {
            cout << req.id << "\t" << req.description << "\t\t";
            // Вывод статуса
            switch (req.status) {
            case ReqStatus::New: cout << "Новое"; break;
            case ReqStatus::Approved: cout << "Утверждено"; break;
            case ReqStatus::Implemented: cout << "Реализовано"; break;
            case ReqStatus::Tested: cout << "Протестировано"; break;
            }
            cout << "\t\t";

            // Поиск тестов, связанных с этим требованием
            vector<int> testIds;
            for (auto& tc : testCases) {
                if (tc.requirementId == req.id) testIds.push_back(tc.id);
            }
            if (testIds.empty()) {
                cout << "НЕТ ТЕСТОВ!";
            }
            else {
                for (int tid : testIds) cout << tid << " ";
            }
            cout << "\n";
        }

        // Подсчёт непокрытых требований
        set<int> coveredReqIds;
        for (auto& tc : testCases) coveredReqIds.insert(tc.requirementId);
        int uncovered = 0;
        for (auto& req : requirements) {
            if (coveredReqIds.find(req.id) == coveredReqIds.end()) ++uncovered;
        }
        cout << "\nНепокрытых требований: " << uncovered << "/" << requirements.size() << "\n";
    }

    // Вывод всех тест-кейсов
    void printTestCases() const {
        cout << "\n=== Тестовые случаи ===\n";
        for (auto& tc : testCases) {
            cout << "ID: " << tc.id << " | Требование: " << tc.requirementId
                << "\nОписание: " << tc.description
                << "\nШаги:\n";
            for (auto& step : tc.steps) cout << "  - " << step << "\n";
            cout << "Ожидаемый результат: " << tc.expectedResult << "\n\n";
        }
    }
};

// ------------------- Демонстрация -------------------
void R27() {
    setlocale(LC_ALL, "");

    RequirementManager rm;

    // Создание требований
    auto r1 = rm.addRequirement("Регистрация пользователя", Priority::High);
    auto r2 = rm.addRequirement("Авторизация через email", Priority::High);
    auto r3 = rm.addRequirement("Сброс пароля", Priority::Medium);
    auto r4 = rm.addRequirement("Отображение профиля", Priority::Low);

    // Анализ: для r1 и r2 автоматически генерируем тесты (имитация процесса)
    rm.generateTestForRequirement(r1->id);
    rm.generateTestForRequirement(r2->id);
    // r3 и r4 остаются без тестов (пока)

    // Изменяем статус требований (имитация жизненного цикла)
    r1->status = ReqStatus::Approved;
    r2->status = ReqStatus::Implemented;
    r3->status = ReqStatus::New;
    r4->status = ReqStatus::New;

    // Выводим матрицу покрытия
    rm.checkCoverage();
    rm.printTestCases();

    // Демонстрация связи с тестированием:
    // Если требование не имеет тестов, его нельзя считать протестированным.
    // В реальном процессе это сигнал к написанию тестов.
}