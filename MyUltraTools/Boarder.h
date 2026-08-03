#pragma once
#include "LifeCycleModels.h"
//2
//Методологии гибкой разработки программного обеспечения.Понятие о
//Agile, Scrum и Kanban.


//Base
enum StatusTask
{
	TODO,
	INPROGRESS,
	DONE
};

class Task
{
public:
	Task(int id, std::string name, StatusTask status) : Id(id), Name(name), Status(status) {};

	int GetId()
	{
		return Id;
	}
	std::string GetName()
	{
		return Name;
	}
	StatusTask GetStatus()
	{
		return Status;
	}
	void SetStatus(StatusTask status)
	{
		Status = status;
	}
private:
	int Id;
	std::string Name;
	StatusTask Status;
};
class BackLog
{
public:
	BackLog() {};

	void SetLogData(std::vector<Task> task)
	{
		Tasks = task;
	}
	void AddTask(Task newTask)
	{
		Tasks.push_back(newTask);
	}
	Task* GetTask(int id)
	{
		for (int i = 0; i < Tasks.size(); i++)
		{
			if (Tasks[i].GetId() == id)
				return &Tasks[i];
		}
		return nullptr;
	}

	std::vector<Task>* GetListTask()
	{
		return &Tasks;
	}
private:
	std::vector<Task> Tasks;
};
class Sprint
{
public:
	Sprint() {};

	Task* GetTask(int id)
	{
		for (int i = 0; i < TaskInSprint.size(); i++)
		{
			if (TaskInSprint[i].GetId() == id)
			{
				return &TaskInSprint[i];
			}
		}
		return nullptr;
	}
	bool AddTaskToSprint(Task newTask)
	{
		if (Active)
			return false;
		else
		{
			TaskInSprint.push_back(newTask);
			return true;
		}
	}
	void StartSprint(int lastTime)
	{
		if (Active == false)
		{
			Time = 0;
			LastTime = lastTime;
			Active = true;
		}
	}
	void UpdateTime()
	{
		if (Active)
		{
			Time += 1;
			if (Time == LastTime)
			{
				Active = false;
			}
		}
	}
	bool IsActive()
	{
		return Active;
	}
private:
	int  Time;
	int  LastTime;
	bool Active = false;
	std::vector<Task> TaskInSprint;
};

//Abstract Class
class IBoard
{
public:
	IBoard() {};

	virtual bool canMoveTask(Task& task, StatusTask status) = 0;

	void SetBackLog(std::vector<std::string> ListTask)
	{
		std::vector<Task> Tasks;
		for (int i = 0; i < ListTask.size(); i++)
		{
			Tasks.push_back(Task(i, ListTask[i], StatusTask::TODO));
		}
		Backlog.SetLogData(Tasks);
	}
	void Report(std::vector<Task>& ListTask)
	{
		for (int i = 0; i < ListTask.size(); i++)
		{
			std::cout << "Задание: " << ListTask[i].GetName() << ": " << ListTask[i].GetStatus() << std::endl;
		}
	}
	BackLog* GetBackLog()
	{
		return &Backlog;
	}
	void MoveTask(Task& task, StatusTask status)
	{
		task.SetStatus(status);
	}

	virtual Sprint* GetSprint() { return nullptr; }
protected:
	BackLog Backlog;
};

//Model
class Scrum : public IBoard
{
public:
	Scrum() {};
	bool canMoveTask(Task& task, StatusTask newStatus) override {
		if (!sprint.IsActive()) return false;
		if (sprint.GetTask(task.GetId()) == nullptr) return false;

		StatusTask cur = task.GetStatus();
		if (cur == TODO && newStatus == INPROGRESS) return true;
		if (cur == INPROGRESS && newStatus == DONE) return true;
		return false;
	}
	Sprint* GetSprint() override
	{
		return &sprint;
	}
private:
	Sprint sprint;
};
class Kanban : public IBoard
{
public:
	Kanban(int wip = 3) : Wip(wip) {}
	bool canMoveTask(Task& task, StatusTask newStatus) override {
		StatusTask cur = task.GetStatus();
		// разрешённые переходы (можно оставить возвраты, если хочешь показать гибкость)
		if (cur == TODO && newStatus == INPROGRESS) { /* ok */ }
		else if (cur == INPROGRESS && newStatus == DONE) { /* ok */ }
		else if (cur == INPROGRESS && newStatus == TODO) { /* ok */ }
		else if (cur == DONE && newStatus == INPROGRESS) { /* ok */ }
		else return false;

		// Проверка WIP только при переходе В INPROGRESS
		if (newStatus == INPROGRESS) {
			int inProgress = 0;
			for (auto& t : *Backlog.GetListTask())   // разыменовываем указатель
				if (t.GetStatus() == INPROGRESS) ++inProgress;
			if (inProgress >= Wip) return false;
		}
		return true;
	}
private:
	int Wip;
};

//Controller
class ControlMenu
{
public:
	ControlMenu(std::unique_ptr<IBoard> model, std::vector<std::string> names) : Model(std::move(model))
	{
		for (int i = 0; i < names.size(); i++)
			Model->SetBackLog(names);
	};

	void MoveTask(Task& task, StatusTask stTask) {
		if (Model->canMoveTask(task, stTask)) {
			Model->MoveTask(task, stTask);
			std::cout << "Переход выполнен.\n";
		}
		else {
			std::cout << "Перемещение запрещено правилами доски.\n";
		}
	}

	BackLog* GetBacklog()
	{
		return Model->GetBackLog();
	}

	Sprint* GetSprintScram()
	{
		return Model->GetSprint();
	}

	int GetSizeBackLog()
	{
		return Model->GetBackLog()->GetListTask()->size();
	}

	void GetRetrospective()
	{
		return Model->Report(*Model->GetBackLog()->GetListTask());
	}
private:
	std::unique_ptr<IBoard> Model;
};

//Controller
template <typename T>
void RealizeBoard(std::vector<std::string> Name)
{
	setlocale(0, "Russian");
	ControlMenu Board = { std::make_unique<T>(), Name };
	int Commands;

	while (true)
	{
		Commands = 1;
		system("cls");
		if (Board.GetSprintScram() != nullptr)
			std::cout << "Ваша достака: Scram" << std::endl;
		else
			std::cout << "Ваша достака: Kanban" << std::endl;

		std::cout << "Команды: " << std::endl;
		std::cout << "[1] Посмотреть список задач/состояние" << std::endl;
		std::cout << "[2] Проверить спринт" << std::endl;
		std::cout << "[3] Переместить задание" << std::endl;
		std::cout << "[4] Выйти" << std::endl;
		std::cin >> Commands;
		system("cls");


		switch (Commands)
		{
		case 1:
		{
			std::cout << "Cписок задач: " << std::endl;
			Board.GetRetrospective();
			break;
		}
		case 2:
		{
			if (Board.GetSprintScram() != nullptr)
			{
				int SprintCommands;
				Sprint* TempSpring = Board.GetSprintScram();
				if (!TempSpring->IsActive())
				{
					std::cout << "Sprint неактивен" << std::endl;
					std::cout << "Доступные команды: " << std::endl;
					std::cout << "[1] Запустить спринт" << std::endl;
					std::cout << "[2] Добавить Task в спринт" << std::endl;
					std::cout << "[5] Обратно в меню" << std::endl;
					std::cin >> SprintCommands;
					system("cls");

					switch (SprintCommands)
					{
					case 1:
					{
						int time;
						std::cout << "Сколько будет длиться спринт: ";
						std::cin >> time;

						TempSpring->StartSprint(time);
						break;
					}
					case 2:
					{
						for (int i = 0; i < Board.GetSizeBackLog(); i++)
						{
							std::cout << "Какое задание добавить в спринт: " << std::endl;
							std::cout << "Введи 0 если не хочешь ничего добавлять" << std::endl;
							Board.GetRetrospective();
							int f = 0;
							std::cin >> f;
							if (f != 0)
								TempSpring->AddTaskToSprint(*Board.GetBacklog()->GetTask(f));
							else
								break;

							system("cls");
						}

						break;
					}
					case 5:
					{
						break;
					}
					}
				}
				else
				{

					std::cout << "Сейчас идет Sprint" << std::endl;
					std::cout << "Доступные команды: " << std::endl;
					std::cout << "[1] Обновить день" << std::endl;
					std::cout << "[2] Обратно в меню" << std::endl;
					std::cin >> SprintCommands;

					switch (SprintCommands)
					{
					case 1:
					{
						TempSpring->UpdateTime();
						break;
					}
					case 2:
					{
						break;
					}
					}
				}
			}
			else
				std::cout << "У вас достака: Kanban : действие невозможно" << std::endl;

			break;
		}
		case 3:
		{
			for (int i = 0; i < Board.GetSizeBackLog(); i++)
			{
				std::cout << "Какое задание переместить? (0 - выход):\n";
				Board.GetRetrospective();
				int f = 0;
				std::cin >> f;
				if (f == 0) break;

				std::cout << "На какой статус поменять:\n";
				std::cout << "[1]: TODO\n[2]: INPROGRESS\n[3]: DONE\n";
				int s; std::cin >> s;
				StatusTask newSt;
				if (s == 1) newSt = TODO;
				else if (s == 2) newSt = INPROGRESS;
				else if (s == 3) newSt = DONE;
				else { std::cout << "Неверный статус\n"; continue; }

				Board.MoveTask(*Board.GetBacklog()->GetTask(f), newSt);
				std::cin.ignore(); std::cin.get(); // пауза
				system("cls");
			}
			break;
		}
		}

		if (Commands == 4)
		{
			system("cls");
			break;
		}

		std::cin.ignore(); std::cin.get();
	}
}