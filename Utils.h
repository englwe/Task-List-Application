#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <thread>
#include <sstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>

bool IsDigits(std::string in);
std::string GetToken(std::string* str, char delimiter);
bool CheckDate(std::string DateStr);
#endif