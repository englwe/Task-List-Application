#pragma once
#ifndef DATE_H
#define DATE_H

#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"

class Date {
public:
	Date(std::string DateStr);
	Date(int day, int month, int year);
	~Date();

	// Implementation
public:
	bool CheckDueDate();
	void ParseDate(std::string DateStr);
	bool operator<(const Date& other) const;

	// Attributes
private:
	int m_nDay;
	int m_nMonth;
	int m_nYear;
	std::string m_sDate;
};

#endif
