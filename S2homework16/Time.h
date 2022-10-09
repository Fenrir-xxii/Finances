#pragma once
#include <chrono>
#include <string>

std::chrono::system_clock::time_point fromString(const std::string& dateStr, const std::string& format);
std::string timeToString(std::chrono::system_clock::time_point tp);
int getLastDayOfMonth(int month, int year);