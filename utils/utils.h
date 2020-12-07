#pragma once

#include <string>
#include <vector>
#include <regex>


std::vector<std::string> split(const std::string& str, const char sep) {
    std::vector<std::string> buf;
    size_t start = 0, end = 0;
    while (end != std::string::npos) {
        end = str.find_first_of(sep, start);
        buf.push_back(str.substr(start, end - start));
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