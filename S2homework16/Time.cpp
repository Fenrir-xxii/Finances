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