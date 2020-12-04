#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <regex>

using namespace std;

const unordered_map<string, function<bool(string)> > mandatory_keys {
    { "byr", [](auto a) {
        regex r ("^[1-2][0-9]{3}$");
        if (!regex_match(a, r))
            return false;
        auto num = stoull(a);
        return (1920 <= num) && (num <= 2002);
     }
    },
    { "iyr", [](auto a) {
        regex r ("^[1-2][0-9]{3}$");
        if (!regex_match(a, r))
            return false;
        auto num = stoull(a);
        return (2010 <= num) && (num <= 2020);
     }
    },
    { "eyr", [](auto a) {
        regex r ("^[1-2][0-9]{3}$");
        if (!regex_match(a, r))
            return false;
        auto num = stoull(a);
        return (2020 <= num) && (num <= 2030);
     }
    },
    { "hgt", [](auto a) {
        regex r ("^[1-9][0-9]*(cm|in)$");
        if (!regex_match(a, r))
            return false;
        auto h = a.substr(0, a.length() - 2);
        auto height = stoull(h);
        if (a.at(a.length() - 1) == 'n')
            return (59 <= height) && (height <= 76);
        return (150 <= height) && (height <= 193);
     }
    },
    { "hcl", [](auto a) {
        regex r ("^#[0-9a-f]{6}$");
        return regex_match(a, r);
     }
    },
    { "ecl", [](auto a) {
        regex r ("^(amb|blu|brn|gry|grn|hzl|oth)$");
        return regex_match(a, r);
     }
    },
    { "pid", [](auto a) {
        regex r ("^[0-9]{9}$");
        return regex_match(a, r);
     }
    }
};

uint64_t sol1() {
    auto result = 0;
    string line;
    unordered_set<string> fields;
    while (getline(cin, line)) {
        if (line.empty()) {
            auto valid = true;
            for (auto key: mandatory_keys) {
                if (!fields.count(key.first)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                ++result;
            }
            fields.clear();
            continue;
        }
        size_t start = 0, end = 0;
        while (end != string::npos) {
            end = line.find_first_of(" ", start);
            auto key_value = line.substr(start, end - start);
            auto semi_colon_pos = key_value.find_first_of(":");
            auto key = key_value.substr(0, semi_colon_pos);
            fields.emplace(key);
            start = end + 1;
        }
    }
    return result;
}

uint64_t sol2() {
    auto result = 0;
    string line;
    unordered_map<string, string> fields;
    while (getline(cin, line)) {
        if (line.empty()) {
            auto valid = true;
            for (auto key: mandatory_keys) {
                if (!fields.count(key.first) || !key.second(fields.at(key.first))) {
                    valid = false;
                    break;
                }
            }
            result += valid;
            fields.clear();
            continue;
        }
        size_t start = 0, end = 0;
        while (end != string::npos) {
            end = line.find_first_of(" ", start);
            auto key_value = line.substr(start, end - start);
            auto semi_colon_pos = key_value.find_first_of(":");
            auto key = key_value.substr(0, semi_colon_pos);
            auto value = key_value.substr(semi_colon_pos + 1, string::npos);
            fields.emplace(key, value);
            start = end + 1;
        }
    }
    return result;
}


int main() {
    cout << sol2() << endl;
}