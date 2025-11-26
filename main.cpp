#include "main.h"

void main(void)
{
	bQuit = false;
	std::string menu = "1) Display all tasks\n2) Add a task\n3) Delete a task\n4) Mark task complete\n5) Check Due Tasks\nq) Quit";
	while (1)
	{	
		std::cout << "\nTask List Viewer" << std::endl;
		std::cout << menu << std::endl;
		std::cin >> cInput;
		std::cin.ignore(); // clear buffer
		switch (cInput)
		{
		case '1':
		{
			DisplayAllTasks();
		}
		break;
		case '2':
		{
			AddTask();
		}
		break;
		case '3':
		{
			DeleteTask();
		}
		break;
		case '4':
		{
			MarkTaskComplete();
		}
		break;
		case '5':
		{
			CheckDueDate();
		}
		break;
		case 'q':
		case 'Q':
		{
			bQuit = true;
			std::cout << "Quitting application..." << std::endl;
		}
		break;
		default:
		{
			std::cout << "Invalid input" << std::endl;
		}
		break;
		}
		if (bQuit)
			break;
	}
}

void DisplayAllTasks()
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

	if (TaskList.empty())
	{
		std::cout << "The task list is empty. Please add a task" << std::endl;
	}

	for(int i = 0; i < TaskList.size(); i++)
	{
		name = TaskList.at(i).m_Name;
		dueDate = TaskList.at(i).m_DueDate;
		str2 = TaskList.at(i).m_Completed ? "Yes" : "No";
		str3 = TaskList.at(i).m_Completed ? green : red;
		idx = i + 1;

		ss << str3 << idx << ") " << "Name: " << name << " Due Date: " << dueDate << " Completed: " << str2 << ResetColour << std::endl;
		str1 = ss.str();

		std::cout << str1 << std::endl;

		ss.str("");
		ss.clear();
	}
}

void AddTask()
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

	Date newDate;
	Task newTask(Name, DueDate, false);
	ParseDate(&newDate, DueDate);
	newTask.m_Due = newDate;
	TaskList.emplace_back(newTask);
}

void DeleteTask()
{
	bool bErr = false;

	if (TaskList.empty())
	{
		std::cout << "The task list is empty" << std::endl;
		return;
	}

	std::cout << "Please select a task to delete" << std::endl;
	DisplayAllTasks();
	std::getline(std::cin, sInput);
	if (IsDigits(sInput))
	{
		int number = std::stoi(sInput);
		if (number < 1 || number > TaskList.size())
			bErr = true;
		if (!bErr)
		{
			TaskList.erase(TaskList.begin() + (number - 1));
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

bool IsDigits(std::string in)
{
	for (char c : in) 
	{
		if (!std::isdigit(c)) return false;
	}
	return true;
}

void CheckDueDate()
{
	if (TaskList.empty())
	{
		std::cout << "The task list is empty" << std::endl;
		return;
	}

	auto now = std::chrono::system_clock::now();
	std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
	std::tm* localTime = std::localtime(&timeNow);
	Date Today(localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
	
	bool bRes = false;
	std::stringstream ss;
	std::string str;
	for (auto it = TaskList.begin(); it != TaskList.end(); it++)
	{
		if (it->m_Due.year < Today.year)
			bRes = true;
		else if(it->m_Due.year == Today.year)
		{
			if (it->m_Due.month < Today.month)
				bRes = true;
			else if (it->m_Due.month == Today.month)
			{
				if (it->m_Due.day <= Today.day)
					bRes = true;
			}
		}

		if (bRes)
		{
			bRes = false;
			ss << "Task " << it->m_Name << " is due";
			str = ss.str();
			std::cout << str << std::endl;
			ss.str("");
			ss.clear();
		}
	}
}

void MarkTaskComplete()
{
	if (TaskList.empty())
	{
		std::cout << "The task list is empty" << std::endl;
		return;
	}

	bool bErr = false;

	std::cout << "Select a task" << std::endl;
	DisplayAllTasks();
	std::getline(std::cin, sInput);
   
	if (IsDigits(sInput))
	{
		int number = std::stoi(sInput);
		if (number < 1 || number > TaskList.size())
			bErr = true;
		if (!bErr)
		{
			TaskList.at(number - 1).m_Completed = true;
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

std::string GetToken(std::string* str, char delimiter)
{
	int n = str->find(delimiter);
	std::string token = str->substr(0, n);
	*str = (*str).substr(n + 1);
	return token;
}

void ParseDate(Date* stDate, std::string dueDate)
{
	std::string ret;

	ret = GetToken(&dueDate, '/');
	stDate->day = std::stoi(ret);

	ret = GetToken(&dueDate, '/');
	stDate->month = std::stoi(ret);

	ret = GetToken(&dueDate, '/');
	stDate->year = std::stoi(ret);
}

bool CheckDate(std::string DueDate)
{
	std::string ret;
	bool bErr = true;
	
	for (int i = 0; i < 3; i++)
	{
		ret = GetToken(&DueDate, '/');
		if (!IsDigits(ret) || ret == "") 
			bErr = false;
		else
		{
			int num = std::stoi(ret);
			if (i == 0 && (num <= 0 || num > 31))
				bErr = false;
			else if (i == 1 && (num <= 0 || num > 12))
				bErr = false;
			else if (i == 2 && ret.size() != 4)
				bErr = false;
		}
	}
	
	return bErr;
}
