#pragma once
#include "OOP2.h"
#include <set>
//6
//Прогнозирующие методологии разработки программного обеспечения.
//Основные принципы методологии RUP.

//Artifact.h
class Artifact {
    std::string name_;
    std::string type_;
    StatusTask status_;
public:
    Artifact(const std::string& name, const std::string& type) : name_(name), type_(type), status_(StatusTask::TODO) {}
    void complete() { status_ = StatusTask::DONE; }
    bool isDone() const { return status_ == StatusTask::DONE; }
    std::string getName() const { return name_; }
};

//Risk.h
class Risk {
    std::string desc_, level_, state_;
public:
    Risk(const std::string& d, const std::string& lvl) : desc_(d), level_(lvl), state_("Open") {}
    void mitigate() { state_ = "Mitigated"; }
    void close() { state_ = "Closed"; }
    std::string getState() const { return state_; }
};

//Iteration.h
class Iteration {
    int number;
    std::vector<Artifact> artifacts;
public:
    Iteration(int num) : number(num) {}

    int ArtifactCount() { return artifacts.size(); }
    void addArtifact(std::shared_ptr<Artifact> artifact) { artifacts.push_back(*artifact); }
    const std::vector<Artifact>& getArtifacts() const { return artifacts; }
};

//Phase_.h
class Phase_ {
    std::string name_;
    int countIterations_;
    std::string milestone_;
    std::vector<Iteration> iterations_;

    static std::map<std::string, std::vector<std::string>> requiredArtifacts;
public:
    Phase_(const std::string& name, int count, const std::string& milestone);

    void addIteration(const Iteration& iter);
    bool isMilestoneAchieved() const;
    int getCurrentIterationNumber() const { return iterations_.size(); }
    std::string getName() const { return name_; }
};
//Phase_.cpp
std::map<std::string, std::vector<std::string>> Phase_::requiredArtifacts = {
    {"Inception", {"Vision", "Business Case"}},
    {"Elaboration", {"Software Architecture Document", "Risk List"}},
    {"Construction", {"Source Code", "Test Plan"}},
    {"Transition", {"User Manual", "Release Notes"}}
};
Phase_::Phase_(const std::string& name, int count, const std::string& milestone) : name_(name), countIterations_(count), milestone_(milestone) {}
void Phase_::addIteration(const Iteration& iter) {
    if (iterations_.size() >= countIterations_) throw std::runtime_error("Phase already has maximum iterations");
    iterations_.push_back(iter);
}
bool Phase_::isMilestoneAchieved() const {
    if (requiredArtifacts.find(name_) == requiredArtifacts.end()) return true;
    const auto& required = requiredArtifacts.at(name_);
    std::set<std::string> existing;
    for (const auto& iter : iterations_) {
        for (const auto& art : iter.getArtifacts()) {
            existing.insert(art.getName());
        }
    }
    for (const auto& req : required) {
        if (existing.find(req) == existing.end()) return false;
    }
    return true;
}

//RUPProject.h
class RUPProject {
    std::vector<Phase_> phases;
    std::vector<Risk> risks;
    int currentPhaseIndex = 0;
    int currentIterationIndex = 0;
public:
    RUPProject() = default;
    void addPhase(const Phase_& phase);
    void addRisk(const Risk& risk);
    void startNextIteration();
    bool isFinished() const;
    Phase_* getCurrentPhase();
    int getCurrentIterationIndex() const { return currentIterationIndex; }
};
//RUPProject.cpp
void RUPProject::addPhase(const Phase_& phases_) { phases.push_back(phases_); }
void RUPProject::addRisk(const Risk& risks_) { risks.push_back(risks_); }
void RUPProject::startNextIteration() {
    if (phases.empty()) throw std::runtime_error("No phases in project");
    if (isFinished()) throw std::runtime_error("Project already finished");

    Phase_& currentPhase = phases[currentPhaseIndex];

    // Завершаем текущую итерацию (увеличиваем счётчик)
    currentIterationIndex++;

    // Если это была последняя итерация фазы, проверяем веху
    if (currentIterationIndex >= currentPhase.getCurrentIterationNumber()) {
        if (!currentPhase.isMilestoneAchieved()) {
            throw std::runtime_error("Milestone not achieved! Cannot proceed to next phase.");
        }
        // Переход к следующей фазе
        currentPhaseIndex++;
        currentIterationIndex = 0;
    }
}
bool RUPProject::isFinished() const {
    return currentPhaseIndex >= phases.size();
}
Phase_* RUPProject::getCurrentPhase() {
    if (isFinished()) return nullptr;
    return &phases[currentPhaseIndex];
}


void testArtifactCreation() {
    Artifact a("Vision", "Document");
    ASSERT_EQUAL(false, a.isDone());
    a.complete();
    ASSERT_EQUAL(true, a.isDone());
}
void testRiskMitigation() {
    Risk r("Architecture risk", "High");
    ASSERT_EQUAL(std::string("Open"), r.getState());
    r.mitigate();
    ASSERT_EQUAL(std::string("Mitigated"), r.getState());
}
void testIterationAddArtifact() {
    Iteration iter(1);
    auto art = std::make_shared<Artifact>("TestPlan", "Plan");
    iter.addArtifact(art);
    ASSERT_EQUAL(1, iter.ArtifactCount());
}
void testPhaseMilestoneNotAchieved() {
    Phase_ inception("Inception", 1, "Lifecycle Objectives");
    Iteration iter(1);
    iter.addArtifact(std::make_shared<Artifact>("Vision", "Document"));
    // Бизнес-кейс не добавлен, веха не достигнута
    inception.addIteration(iter);
    ASSERT_EQUAL(false, inception.isMilestoneAchieved());
}
void testPhaseMilestoneAchieved() {
    Phase_ inception("Inception", 1, "Lifecycle Objectives");
    Iteration iter(1);
    iter.addArtifact(std::make_shared<Artifact>("Vision", "Document"));
    iter.addArtifact(std::make_shared<Artifact>("Business Case", "Document"));
    inception.addIteration(iter);
    ASSERT_EQUAL(true, inception.isMilestoneAchieved());
}
void testRUPProjectCompleteSuccess() {
    RUPProject proj;

    // Создаём фазы и заполняем итерации с артефактами
    Phase_ inception("Inception", 1, "Lifecycle Objectives");
    Iteration i1(1);
    i1.addArtifact(std::make_shared<Artifact>("Vision", "Document"));
    i1.addArtifact(std::make_shared<Artifact>("Business Case", "Document"));
    inception.addIteration(i1);
    proj.addPhase(inception);

    Phase_ elaboration("Elaboration", 1, "Lifecycle Architecture");
    Iteration e1(2);
    e1.addArtifact(std::make_shared<Artifact>("Software Architecture Document", "Document"));
    e1.addArtifact(std::make_shared<Artifact>("Risk List", "Document"));
    elaboration.addIteration(e1);
    proj.addPhase(elaboration);

    Phase_ construction("Construction", 1, "Initial Operational Capability");
    Iteration c1(3);
    c1.addArtifact(std::make_shared<Artifact>("Source Code", "Code"));
    c1.addArtifact(std::make_shared<Artifact>("Test Plan", "Plan"));
    construction.addIteration(c1);
    proj.addPhase(construction);

    Phase_ transition("Transition", 1, "Product Release");
    Iteration t1(4);
    t1.addArtifact(std::make_shared<Artifact>("User Manual", "Document"));
    t1.addArtifact(std::make_shared<Artifact>("Release Notes", "Document"));
    transition.addIteration(t1);
    proj.addPhase(transition);

    // Запускаем итерации
    ASSERT_EQUAL(false, proj.isFinished());
    // Inception (1 итерация)
    proj.startNextIteration(); // должна пройти проверку вехи и перейти к Elaboration
    ASSERT_EQUAL(false, proj.isFinished());
    // Elaboration
    proj.startNextIteration();
    ASSERT_EQUAL(false, proj.isFinished());
    // Construction
    proj.startNextIteration();
    ASSERT_EQUAL(false, proj.isFinished());
    // Transition
    proj.startNextIteration();
    ASSERT_EQUAL(true, proj.isFinished());
}
void testRUPProjectMilestoneFail() {
    RUPProject proj;
    Phase_ inception("Inception", 1, "Lifecycle Objectives");
    Iteration i1(1);
    // Нет артефакта Business Case
    i1.addArtifact(std::make_shared<Artifact>("Vision", "Document"));
    inception.addIteration(i1);
    proj.addPhase(inception);

    ASSERT_THROWS(proj.startNextIteration()); // должно выбросить исключение
}

//4 фазы(Inception, Elaboration, Construction, Transition) с заданными итерациями.
//
//Прогнозируемость – число итераций и обязательные артефакты зафиксированы заранее, переход к следующей фазе невозможен без достижения вехи.
//
//Управление рисками – добавление, снижение, закрытие.
//
//Контрольные точки(milestones) – проверка по обязательным артефактам.
//
//Исключительные ситуации – невозможность завершить фазу без вехи.
