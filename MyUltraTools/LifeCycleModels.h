#pragma once
#include <iostream>
#include <vector>
#include <memory>

// Base
class Phase
{
public:
	Phase(std::string name, int id) {
		NamePhase = name;
		Id = id;
	};
	~Phase() {};

	std::string GetName()
	{
		return NamePhase;
	}
	int GetID()
	{
		return Id;
	}
private:
	std::string NamePhase;
	int Id;
};
class LifecycleModel
{
public:
	LifecycleModel() {};
	~LifecycleModel() {};
	void AddPhase(std::string name, int id)
	{
		ListPhase.push_back(Phase(name, id));
	}
	Phase* GetPhase(int id)
	{
		for (int i = 0; i < ListPhase.size(); i++)
		{
			if (ListPhase[i].GetID() == id)
			{
				return &ListPhase[i];
			}
		}
		return nullptr;
	}

	virtual bool canTransition(int id, int idNext) = 0;

protected:
	std::vector<Phase> ListPhase;
};

//Models
class WaterFall : public LifecycleModel
{
public:
	WaterFall() {}
	bool canTransition(int id, int idNext) override
	{
		return (idNext == id + 1);
	}
};
class Iterative : public LifecycleModel
{
public:
	Iterative() {}
	bool canTransition(int id, int idNext) override
	{
		return (idNext == id + 1) || (idNext == id - 1);
	}
};

//Proj
class Project
{
public:
	Project(std::unique_ptr<LifecycleModel> model, std::vector<std::string> names) : Model(std::move(model))
	{
		CountPhase = names.size();
		for (int i = 0; i < CountPhase; i++)
			Model->AddPhase(names[i], i);
	};

	bool NextPhase(int id, int idNext)
	{
		return Model->canTransition(id, idNext);
	}
	std::string GetNamePhase(int id)
	{
		return Model->GetPhase(id)->GetName();
	}
	int GetEndPhase(int id)
	{
		return CountPhase - 1;
	}

private:
	int CountPhase;
	std::unique_ptr<LifecycleModel> Model;
};

//Controller
template <typename T>
void RealizeLifeCycle( std::vector<std::string> Lifecycle)
{
	setlocale(0, "Russian");
	Project Proj = { std::make_unique<T>(), Lifecycle };
	int id = 0;
	int NextId;

	while (true)
	{
		system("cls");
		std::cout << "Фаза сейчас: " << id << " " << Proj.GetNamePhase(id) << std::endl;
		std::cout << "Выбери следующий элемент: ";
		std::cin >> NextId;
		system("cls");
		if (Proj.NextPhase(id, NextId))
		{
			id = NextId;
			std::cout << "Фаза сейчас: " << id << " " << Proj.GetNamePhase(id) << std::endl;
			std::cout << "Переход на фазу : " << NextId << std::endl;
		}
		else
		{
			std::cout << "Фаза сейчас: " << id << std::endl;
			std::cout << "Переход на фазу: Не возможен!" << std::endl;
		}
		if (id == Proj.GetEndPhase(id))
		{
			system("cls");
			std::cout << "Фаза сейчас: " << id << " " << Proj.GetNamePhase(id) << std::endl;
			std::cout << "Это артефакт!!!" << std::endl;
			std::cin.ignore(); std::cin.get();
			break;
		}
		std::cout << "Пропустить...";
		std::cin.ignore(); std::cin.get();

	}
}
