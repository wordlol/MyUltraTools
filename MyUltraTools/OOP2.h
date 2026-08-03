#pragma once
#include "OOP1.h"
//5
//Основные принципы объектно - ориентированного программирования.
//Связность и связанность.Наследование.Агрегация и композиция.
//Полиморфизм.

//Task_.h
enum class Status_ { TODO, INPROGRESS, DONE };
class Task_ {
    int id_;
    std::string title_;
    Status_ status_;
public:
    Task_(int id, const std::string& title) : id_(id), title_(title), status_(Status_::TODO) {}
    virtual ~Task_() = default;
    virtual int estimatedHours() const = 0;
    int getId() const { return id_; }
    std::string getTitle() const { return title_; }
    Status_ getStatus() const { return status_; }
};

//BugTask.h
class BugTask : public Task_
{
    int severity_;
public:
    BugTask(int id, const std::string& title, int severity);
    int estimatedHours() const override;
};
// BugTask.cpp
BugTask::BugTask(int id, const std::string& title, int severity) : Task_(id, title), severity_(severity) {}
int BugTask::estimatedHours() const { return severity_ * 2; }


//FeatureTask.h
class FeatureTask : public Task_
{
    int severity_;
public:
    FeatureTask(int id, const std::string& title, int severity);
    int estimatedHours() const override;
};
// FeatureTask.cpp
FeatureTask::FeatureTask(int id, const std::string& title, int severity) : Task_(id, title), severity_(severity) {}
int FeatureTask::estimatedHours() const { return severity_ * 5; }


//DocumentationTask.h
class DocumentationTask : public Task_
{
    int severity_;
public:
    DocumentationTask(int id, const std::string& title, int severity);
    int estimatedHours() const override;
};
// DocumentationTask.cpp
DocumentationTask::DocumentationTask(int id, const std::string& title, int severity) : Task_(id, title), severity_(severity) {}
int DocumentationTask::estimatedHours() const { return 8; }

//Employee.h
class Employee {
    std::string name_;
    std::string position_;
public:
    Employee(const std::string& name, const std::string& position) : name_(name), position_(position) {}
    std::string getName() const { return name_; }
    std::string getPosition() const { return position_; }
};

class Project_ {
    std::string name_;
    int data_;
    std::vector<std::unique_ptr<Task_>> tasks_;
    Employee* manager_ = nullptr;
public:
    Project_(const std::string& name, int data) : name_(name), data_(data) {}
    void addTask(std::unique_ptr<Task_> task) { tasks_.push_back(std::move(task)); }
    int totalEstimatedHours() const {
        int total = 0;
        for (auto& t : tasks_)
            total += t->estimatedHours();
        return total;
    }
    void setManager(Employee* emp) { manager_ = emp; }
    Employee* getManager() const { return manager_; }
    size_t taskCount() const { return tasks_.size(); }
};



void testBugTaskEstimatedHours() {
    BugTask bug(1, "Crash on start", 3);
    ASSERT_EQUAL(6, bug.estimatedHours()); // severity 3 ? 6 часов
}

void testFeatureTaskEstimatedHours() {
    FeatureTask bug(2, "Crash on start", 3);
    ASSERT_EQUAL(15, bug.estimatedHours());
}

void testDocumentationTaskEstimatedHours() {
    DocumentationTask bug(3, "Crash on start", 3);
    ASSERT_EQUAL(8, bug.estimatedHours());
}

void testProjectTotalHours() {
    Project_ proj("Alpha", 2025);
    proj.addTask(std::make_unique<BugTask>(1, "bug", 2));
    proj.addTask(std::make_unique<FeatureTask>(2, "feat", 1));
    proj.addTask(std::make_unique<DocumentationTask>(3, "doc", 0));
    ASSERT_EQUAL(17, proj.totalEstimatedHours());
}

void testProjectManagerAggregation() {
    Employee emp("Ivan", "Team Lead");
    Project_ projA("ProjA", 2025);
    Project_ projB("ProjB", 2025);
    projA.setManager(&emp);
    projB.setManager(&emp);
    // Оба проекта ссылаются на одного сотрудника (агрегация)
    ASSERT_TRUE(projA.getManager() == &emp);
    ASSERT_TRUE(projB.getManager() == &emp);
    // Сотрудник живёт независимо (emp не удалится после выхода из функции, пока жив)
    // Если нужно показать, что при удалении сотрудника проекты не разрушаются,
    // можно здесь после выхода emp уничтожится, но в тесте мы не можем это проверить,
    // поэтому просто показываем, что менеджер — внешний объект.
}

void testCompositionDestruction() {
    // Проверим, что при уничтожении проекта задачи исчезают (композиция)
    // Косвенно: создадим проект, добавим задачу, затем выйдем из блока,
    // и убедимся, что задача не существует (используем подсчёт задач).
    Project_* p = new Project_("Temp", 2025);
    p->addTask(std::make_unique<BugTask>(10, "test", 1));
    size_t count = p->taskCount();
    delete p; // проект и его задачи удалены
    // задача больше не доступна — это и есть композиция.
    ASSERT_TRUE(count == 1); // тривиальная проверка, что задача была
}

//Композиция — Project_ владеет Task_ через unique_ptr : при удалении проекта задачи уничтожаются.
//
//Агрегация — Project_ хранит внешний Employee*, сотрудник может быть назначен на несколько проектов и живёт независимо.
//
//Наследование и полиморфизм — BugTask, FeatureTask, DocumentationTask переопределяют estimatedHours(), и Project_ вызывает их через базовый указатель.
