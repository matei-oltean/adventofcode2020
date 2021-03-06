#pragma once

#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <functional>

std::vector<std::string> split(const std::string& str, const char sep) {
    std::vector<std::string> buf;
    size_t start = 0, end = 0;
    while (end != std::string::npos) {
        end = str.find_first_of(sep, start);
        if (end - start) {
            buf.push_back(str.substr(start, end - start));
        }
        start = end + 1;
    }
    return buf;
}

std::vector<std::string> split(const std::string& str, const std::regex& sep) {
    std::vector<std::string> buf;
    std::sregex_token_iterator it(str.begin(), str.end(), sep, -1);
    std::sregex_token_iterator end;
    while (it != end) {
        std::string found = *(it++);
        if (!found.empty()) {
            buf.push_back(found);
        }
    }
    return buf;
}

/*
    Usage:
    run_and_time([]{ cout << sol2() << endl; });
*/
void run_and_time(const std::function<void()>& lambda) {
    auto m_StartTime = std::chrono::system_clock::now();
    lambda();
    auto m_EndTime = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(m_EndTime - m_StartTime).count() << std::endl;

}