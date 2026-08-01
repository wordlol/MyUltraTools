#pragma once
// Монолит: все в одной функции
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void R128() {
    vector<string> tasks;
    int choice;
    string task;

    while (true) {
        cout << "1. Добавить\n2. Удалить\n3. Показать\n4. Выход\n> ";
        cin >> choice;
        if (choice == 4) break;

        if (choice == 1) {
            cout << "Задача: ";
            cin.ignore();
            getline(cin, task);
            tasks.push_back(task);
        }
        else if (choice == 2) {
            int idx;
            cout << "Номер: ";
            cin >> idx;
            if (idx > 0 && idx <= tasks.size()) tasks.erase(tasks.begin() + idx - 1);
        }
        else if (choice == 3) {
            for (size_t i = 0; i < tasks.size(); ++i)
                cout << i + 1 << ". " << tasks[i] << endl;
        }
    }
}


#include <memory>
using namespace std;

// ------------------- Model -------------------
class TaskModel {
    vector<string> tasks;
public:
    void addTask(const string& task) { tasks.push_back(task); }
    bool removeTask(size_t index) {
        if (index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            return true;
        }
        return false;
    }
    const vector<string>& getTasks() const { return tasks; }
};

// ------------------- View -------------------
class TaskView {
public:
    void showMenu() const {
        cout << "\nМеню:\n1. Добавить\n2. Удалить\n3. Показать\n4. Выход\n> ";
    }

    void displayTasks(const vector<string>& tasks) const {
        cout << "\nСписок задач:\n";
        for (size_t i = 0; i < tasks.size(); ++i)
            cout << i + 1 << ". " << tasks[i] << endl;
        if (tasks.empty()) cout << "(пусто)\n";
    }

    string getInput(const string& prompt) const {
        cout << prompt;
        string input;
        getline(cin, input);
        return input;
    }

    int getChoice() const {
        int choice;
        cin >> choice;
        cin.ignore(); // очистка буфера
        return choice;
    }
};

// ------------------- Controller -------------------
class TaskController {
    TaskModel model;
    TaskView view;
public:
    void run() {
        int choice;
        do {
            view.showMenu();
            choice = view.getChoice();
            switch (choice) {
            case 1: {
                string task = view.getInput("Введите задачу: ");
                model.addTask(task);
                break;
            }
            case 2: {
                size_t index = stoi(view.getInput("Номер для удаления: "));
                if (!model.removeTask(index - 1))
                    cout << "Неверный номер.\n";
                break;
            }
            case 3:
                view.displayTasks(model.getTasks());
                break;
            case 4:
                cout << "Выход.\n";
                break;
            default:
                cout << "Неверный выбор.\n";
            }
        } while (choice != 4);
    }
};

// ------------------- main -------------------
void R228() {
    TaskController controller;
    controller.run();
}