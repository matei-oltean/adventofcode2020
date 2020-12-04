#pragma once

#include <string>
#include <vector>

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