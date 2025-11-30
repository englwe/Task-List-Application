#include "Date.h"

Date::Date(std::string DateStr)
{
	m_sDate = DateStr;
	ParseDate(m_sDate);
}

Date::Date(int d, int m, int y)
{
	m_nDay = d;
	m_nMonth = m;
	m_nYear = y;
	m_sDate = std::to_string(d) + "/" + std::to_string(m) + "/" + std::to_string(y);
}

Date::~Date()
{

}

bool Date::CheckDueDate()
{
	// 
	//if (IsListEmpty())
	//{
	//	std::cout << "The task list is empty" << std::endl;
	//	return;
	//}

	auto now = std::chrono::system_clock::now();
	std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
	std::tm* localTime = std::localtime(&timeNow);

	Date Today(localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);

	bool bRes = false;
	std::stringstream ss;
	std::string str;

	if (m_nYear < Today.m_nYear)
		bRes = true;
	else if (m_nYear == Today.m_nYear)
	{
		if (m_nMonth < Today.m_nMonth)
			bRes = true;
		else if (m_nMonth == Today.m_nMonth)
		{
			if (m_nDay <= Today.m_nDay)
				bRes = true;
		}
	}

	return bRes;
}

void Date::ParseDate(std::string DateStr)
{
	std::string ret;
	std::string str = DateStr;

	ret = GetToken(&str, '/');
	m_nDay = std::stoi(ret);

	ret = GetToken(&str, '/');
	m_nMonth = std::stoi(ret);

	ret = GetToken(&str, '/');
	m_nYear = std::stoi(ret);

}

bool Date::operator<(const Date& other) const {
	if (m_nYear != other.m_nYear)
		return m_nYear < other.m_nYear;
	if (m_nMonth != other.m_nMonth)
		return m_nMonth < other.m_nMonth;
	return m_nDay < other.m_nDay;
}