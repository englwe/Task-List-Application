#include "Utils.h"

bool IsDigits(std::string in)
{
	for (char c : in)
	{
		if (!std::isdigit(c)) return false;
	}
	return true;
}

std::string GetToken(std::string* str, char delimiter)
{
	int n = str->find(delimiter);
	std::string token = str->substr(0, n);
	*str = (*str).substr(n + 1);
	return token;
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