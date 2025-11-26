#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <thread>
#include <sstream>
#include <string>

struct Date {
	int year;
	int month;
	int day;

	Date(int d = 1, int m = 1, int y = 2000)
	{
		year = y;
		month = m;
		day = d;
	}
};

struct Task {
	std::string m_Name;
	std::string m_DueDate;
	Date m_Due;
	bool m_Completed;
	
	Task(std::string Name, std::string Date, bool com) : m_Name(Name), m_DueDate(Date), m_Completed(com) {};

};

// main
std::vector<Task> TaskList;
bool bQuit;

// Task functions
void DisplayAllTasks();
void DeleteTask();
void AddTask();
void CheckDueDate();
void MarkTaskComplete();
void ParseDate(Date* stDate, std::string dueDate);

// Input
char cInput;
std::string sInput;

// Functions
bool IsDigits(std::string in);
std::string GetToken(std::string* str, char delimiter);
bool CheckDate(std::string DueDate);
