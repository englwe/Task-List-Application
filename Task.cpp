#include "Task.h"

Task::Task(std::string Name, std::string DueDate)
	: m_sName(Name),
	m_sDueDate(DueDate),
	m_Date(DueDate),
	m_bCompleted(false)
{

}

Task::~Task()
{

}

std::string Task::GetTaskName()
{
	return m_sName;
}

std::string Task::GetDueDate()
{
	return m_sDueDate;
}

bool Task::CheckCompleted()
{
	return m_bCompleted;
}

void Task::MarkAsCompleted()
{
	m_bCompleted = true;
}

Task* Task::Clone()
{
	Task* tObj = new Task(this->m_sName, this->m_sDueDate);
	tObj->m_bCompleted = this->m_bCompleted;
	//tObj->m_Date = this->m_Date;
	return tObj;
}