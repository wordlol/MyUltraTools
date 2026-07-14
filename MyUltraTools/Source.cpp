#include "LifeCycleModels.h"

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
	BackLog(){};

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
			if (ListTask[i].GetStatus() == StatusTask::DONE)
				std::cout << "Задание: " << ListTask[i].GetName() << ": DONE" << std::endl;
		}
		std::cin.ignore(); std::cin.get();
		system("cls");
	}
	BackLog* GetBackLog()
	{
		return &Backlog;
	}
	void MoveTask(Task& task, StatusTask status)
	{
		task.SetStatus(status);
	}

protected:
	BackLog Backlog;
};

//Model
class Scrum : public IBoard
{
public:
	Scrum() {};
	bool canMoveTask(Task& task, StatusTask status) override 
	{
		if (sprint.IsActive())
		{
			return false;
		}
		if (!sprint.GetTask(task.GetId()))
		{
			return false;
		}

		if (task.GetStatus() == StatusTask::TODO && status == StatusTask::INPROGRESS)
		{
			return true;
		}
		else if (task.GetStatus() == StatusTask::INPROGRESS && status == StatusTask::DONE)
		{
			return true;
		}

		return false;
	}
	Sprint* GetSprint()
	{
		return &sprint;
	}
private:
	Sprint sprint;
};
class Kanban : public IBoard
{
public:
	Kanban(int wip) : Wip(wip){};
	bool canMoveTask(Task& task, StatusTask status) override
	{
		if (task.GetStatus() == StatusTask::INPROGRESS && inProgress < Wip)
		{
			inProgress += 1;
		}
		else
		{
			return false;
		}

		if (task.GetStatus() == StatusTask::INPROGRESS && status == StatusTask::TODO)
		{
			return true;
		}
		else if (task.GetStatus() == StatusTask::TODO && status == StatusTask::INPROGRESS)
		{
			return true;
		}
		else if (task.GetStatus() == StatusTask::INPROGRESS && status == StatusTask::DONE)
		{
			return true;
		}
		else if (task.GetStatus() == StatusTask::DONE && status == StatusTask::INPROGRESS)
		{
			return true;
		}

		return false;
	}
private:
	int Wip;
	int inProgress;
};

//Controller
class ControlMenu
{
public:







private:

};


int main()
{


}