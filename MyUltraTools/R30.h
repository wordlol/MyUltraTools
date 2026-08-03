#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <locale>

using namespace std;

// Тип стрелки
enum class ArrowType { Input, Output, Control, Mechanism };

// Класс стрелки
class Arrow {
    string name;
    ArrowType type;
    weak_ptr<class ActivityBox> source;   // откуда (может быть внешним, тогда nullptr)
    weak_ptr<ActivityBox> target;         // куда
public:
    Arrow(const string& n, ArrowType t) : name(n), type(t) {}
    string getName() const { return name; }
    ArrowType getType() const { return type; }

    void setSource(shared_ptr<ActivityBox> box) { source = box; }
    void setTarget(shared_ptr<ActivityBox> box) { target = box; }
};

// Класс функционального блока
class ActivityBox {
    string name;
    string description;
    // Стрелки по сторонам
    vector<shared_ptr<Arrow>> inputs;      // слева
    vector<shared_ptr<Arrow>> outputs;     // справа
    vector<shared_ptr<Arrow>> controls;    // сверху
    vector<shared_ptr<Arrow>> mechanisms;  // снизу
public:
    ActivityBox(const string& n, const string& desc = "") : name(n), description(desc) {}
    string getName() const { return name; }

    void addInput(shared_ptr<Arrow> arrow) { inputs.push_back(arrow); arrow->setTarget(nullptr); } // входящая стрелка идёт от внешнего источника
    void addOutput(shared_ptr<Arrow> arrow) { outputs.push_back(arrow); arrow->setSource(nullptr); }
    void addControl(shared_ptr<Arrow> arrow) { controls.push_back(arrow); }
    void addMechanism(shared_ptr<Arrow> arrow) { mechanisms.push_back(arrow); }

    // Вывод информации о блоке
    void print() const {
        cout << "???????????????????????????????????????\n";
        cout << "? Блок: " << name;
        if (!description.empty()) cout << " (" << description << ")";
        cout << "\n";
        cout << "???????????????????????????????????????\n";
        cout << "? Входы: ";
        for (auto& a : inputs) cout << a->getName() << " ";
        cout << "\n? Выходы: ";
        for (auto& a : outputs) cout << a->getName() << " ";
        cout << "\n? Управление: ";
        for (auto& a : controls) cout << a->getName() << " ";
        cout << "\n? Механизмы: ";
        for (auto& a : mechanisms) cout << a->getName() << " ";
        cout << "\n???????????????????????????????????????\n";
    }
};

// Контекстная диаграмма (A-0) и декомпозиция
class IDEF0Diagram {
    shared_ptr<ActivityBox> contextBox; // A0
    vector<shared_ptr<ActivityBox>> decomposition; // дочерние блоки
    vector<shared_ptr<Arrow>> arrows;  // все стрелки
public:
    IDEF0Diagram(const string& systemName, const string& description) {
        contextBox = make_shared<ActivityBox>(systemName, description);
    }

    // Получить контекстный блок
    shared_ptr<ActivityBox> getContext() const { return contextBox; }

    // Добавить дочерний блок (декомпозиция контекста)
    void addChildBox(shared_ptr<ActivityBox> box) {
        decomposition.push_back(box);
    }

    // Создать стрелку
    shared_ptr<Arrow> createArrow(const string& name, ArrowType type) {
        auto arrow = make_shared<Arrow>(name, type);
        arrows.push_back(arrow);
        return arrow;
    }

    // Вывод всей модели
    void printModel() const {
        cout << "\n=== МОДЕЛЬ IDEF0 ===\n";
        cout << "Контекстный уровень (A-0):\n";
        contextBox->print();

        if (!decomposition.empty()) {
            cout << "\nДекомпозиция (уровень A0):\n";
            for (auto& box : decomposition) {
                box->print();
            }
        }

        cout << "\nСписок стрелок:\n";
        for (auto& a : arrows) {
            cout << "  " << a->getName() << " (";
            switch (a->getType()) {
            case ArrowType::Input: cout << "Вход"; break;
            case ArrowType::Output: cout << "Выход"; break;
            case ArrowType::Control: cout << "Управление"; break;
            case ArrowType::Mechanism: cout << "Механизм"; break;
            }
            cout << ")\n";
        }
    }
};

// Демонстрация
void R30() {
    setlocale(LC_ALL, "");

    // Создаём контекстную диаграмму "Производство продукции"
    IDEF0Diagram diagram("Производство продукции", "A0: Выпуск готовых изделий");
    auto context = diagram.getContext();

    // Создаём внешние стрелки
    auto rawMaterial = diagram.createArrow("Сырьё", ArrowType::Input);
    auto finishedProduct = diagram.createArrow("Готовая продукция", ArrowType::Output);
    auto standards = diagram.createArrow("Стандарты качества", ArrowType::Control);
    auto equipment = diagram.createArrow("Оборудование", ArrowType::Mechanism);

    // Присоединяем к контекстному блоку
    context->addInput(rawMaterial);
    context->addOutput(finishedProduct);
    context->addControl(standards);
    context->addMechanism(equipment);

    // Декомпозиция: три подфункции
    auto box1 = make_shared<ActivityBox>("A1: Подготовка сырья");
    auto box2 = make_shared<ActivityBox>("A2: Обработка");
    auto box3 = make_shared<ActivityBox>("A3: Упаковка");

    // Стрелки между подфункциями (внутренние)
    auto preparedMaterial = diagram.createArrow("Подготовленное сырьё", ArrowType::Input);
    auto processedItem = diagram.createArrow("Обработанный полуфабрикат", ArrowType::Input);

    // Настройка связей (упрощённо, без строгих правил IDEF0)
    box1->addInput(rawMaterial);           // сырьё входит в A1
    box1->addOutput(preparedMaterial);    // из A1 выходит подготовленное
    box2->addInput(preparedMaterial);     // входит в A2
    box2->addOutput(processedItem);
    box3->addInput(processedItem);
    box3->addOutput(finishedProduct);

    diagram.addChildBox(box1);
    diagram.addChildBox(box2);
    diagram.addChildBox(box3);

    // Выводим модель
    diagram.printModel();

}