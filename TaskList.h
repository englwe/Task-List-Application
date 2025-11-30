#pragma once
#ifndef TASKLIST_H
#define TASKLIST_H
#include "Utils.h"
#include "Task.h"



class TaskList {
public:
	TaskList();
	~TaskList();
	// Implementation
public:
	void DisplayAllTasks();
	void AddTask();
	void DeleteTask();
	bool IsListEmpty();
	void MarkTaskComplete();
	void CheckDueDate();
	void SortDueDate();
	// Attributes
private:
	std::vector<Task*> List;
};
#endif