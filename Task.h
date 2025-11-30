#pragma once
#ifndef TASK_H
#define TASK_H

#include "Utils.h"
#include "Date.h"

class Task {
public:
	Task(std::string Name = "", std::string DueDate = "");
	~Task();

public:
	Date m_Date;

	// Implementation
public:
	std::string GetTaskName();
	std::string GetDueDate();
	bool CheckCompleted();
	void MarkAsCompleted();
	Task* Clone();

	// Attributes
private:
	std::string m_sName;
	std::string m_sDueDate;
	bool m_bCompleted;

};
#endif
