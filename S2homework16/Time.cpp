#include "Time.h"

std::chrono::system_clock::time_point fromString(const std::string& dateStr, const std::string& format) {
    std::stringstream ss{ dateStr };
    std::chrono::system_clock::time_point tp;
    ss >> std::chrono::parse(format, tp);
    if (ss.fail()) {
        throw "Can`t parse date";
    }
    return tp;
}

std::string timeToString(std::chrono::system_clock::time_point tp) {

    std::stringstream ss;
    ss << format("{:%d.%m.%Y}", tp);
    return ss.str();
}

int getLastDayOfMonth(int month, int year) {
    if (month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12)
        return 31;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0)
                    return 29;
                return 28;
            }
            return 29;
        }
        return 28;
    }
}