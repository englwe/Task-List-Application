#include "TaskList.h"

TaskList::TaskList()
{
	List = {};
}

TaskList::~TaskList()
{
	for (auto it = List.begin(); it != List.end(); it++) {
		delete *it; 
	}
}

void TaskList::DisplayAllTasks()
{
	std::string green = "\033[42m";
	std::string red = "\033[41m";
	std::string ResetColour = "\033[0m";

	std::string str1;
	std::string str2;
	std::string str3;

	std::stringstream ss;
	std::string name;
	std::string dueDate;
	int idx;

	if (IsListEmpty())
	{
		std::cout << "The task list is empty. Please add a task" << std::endl;
	}

	for (int i = 0; i < List.size(); i++)
	{
		name = List.at(i)->GetTaskName();
		dueDate = List.at(i)->GetDueDate();
		str2 = List.at(i)->CheckCompleted() ? "Yes" : "No";
		str3 = List.at(i)->CheckCompleted() ? green : red;
		idx = i + 1;

		ss << str3 << idx << ") " << "Name: " << name << " Due Date: " << dueDate << " Completed: " << str2 << ResetColour << std::endl;
		str1 = ss.str();

		std::cout << str1 << std::endl;

		ss.str("");
		ss.clear();
	}
}

void TaskList::AddTask()
{
	std::string Name;
	std::string DueDate;
	std::cout << "Please enter the task name: ";
	std::getline(std::cin, Name);
date:
	std::cout << "Please enter the due date (dd/MM/yyyy): ";
	std::getline(std::cin, DueDate);

	if (!CheckDate(DueDate))
	{
		std::cout << "Date format error" << std::endl;
		goto date;
	}

	Task* NewTask = new Task(Name, DueDate);
	List.emplace_back(NewTask);
}

void TaskList::DeleteTask()
{
	if (IsListEmpty())
	{
		std::cout << "The task list is empty" << std::endl;
		return;
	}

	std::string sInput;
	bool bErr = false;
	std::cout << "Please select a task to delete" << std::endl;
	DisplayAllTasks();
	std::getline(std::cin, sInput);
	if (IsDigits(sInput))
	{
		int number = std::stoi(sInput);
		if (number < 1 || number > List.size())
			bErr = true;
		if (!bErr)
		{
			List.erase(List.begin() + (number - 1));
		}
	}
	else
	{
		std::cout << "Invalid input" << std::endl;
	}

	if (bErr)
	{
		std::cout << "Error" << std::endl;
	}

}

void TaskList::CheckDueDate()
{
	if (IsListEmpty())
	{
		std::cout << "The task list is empty" << std::endl;
		return;
	}

	for (auto it = List.begin(); it != List.end(); it++)
	{
		auto task = *it;
		if (task->m_Date.CheckDueDate())
		{
			std::string name = task->GetTaskName();
			std::string due = task->GetDueDate();
			std::string str1;
			std::stringstream ss;

			ss << "Task: " << name << " is already due" << " Due date: " << due;
			str1 = ss.str();

			std::cout << str1 << std::endl;

			ss.str("");
			ss.clear();
		}
	}
}

bool TaskList::IsListEmpty()
{
	return List.empty();
}

void TaskList::MarkTaskComplete()
{
	if (IsListEmpty())
	{
		std::cout << "The task list is empty" << std::endl;
		return;
	}

	bool bErr = false;
	std::string sInput;

	std::cout << "Select a task" << std::endl;
	DisplayAllTasks();
	std::getline(std::cin, sInput);

	if (IsDigits(sInput))
	{
		int number = std::stoi(sInput);
		if (number < 1 || number > List.size())
			bErr = true;
		if (!bErr)
		{
			auto& task = List.at(number - 1);
			task->MarkAsCompleted();
		}
	}
	else
	{
		std::cout << "Invalid input" << std::endl;
	}

	if (bErr)
	{
		std::cout << "Error" << std::endl;
	}
}

void TaskList::SortDueDate()
{
	if (IsListEmpty())
	{
		std::cout << "The task list is empty" << std::endl;
		return;
	}

	std::vector<Task*> TempList;
	for (auto it = List.begin(); it != List.end(); it++)
	{
		auto task = *it;
		TempList.emplace_back(task->Clone());
	}

	std::sort(TempList.begin(), TempList.end(), [](const Task* a, const Task* b) {
		return a->m_Date < b->m_Date;  
		});

	for (auto it = TempList.begin(); it != TempList.end(); it++)
	{
		auto task = *it;
		std::cout << task->GetTaskName() << " " << task->GetDueDate() << std::endl;
		delete task;
	}
}