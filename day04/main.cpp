#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <regex>
#include <algorithm>
#include <./utils.h>

using namespace std;

const unordered_map<string, regex> mandatory_keys {
    { "byr", regex("^19[2-9][0-9]|200[0-2]$") },
    { "iyr", regex("^201[0-9]|2020$") },
    { "eyr", regex("^202[0-9]|2030$") },
    { "hgt", regex("^((1[5-8][0-9]|19[0-3])cm)|((59|6[0-9]|7[0-6])in)$") },
    { "hcl", regex("^#[0-9a-f]{6}$") },
    { "ecl", regex("^(amb|blu|brn|gry|grn|hzl|oth)$") },
    { "pid", regex("^[0-9]{9}$") },
};

uint64_t sol1() {
    auto result = 0;
    string line;
    unordered_set<string> fields;
    while (getline(cin, line)) {
        if (line.empty()) {
            if (all_of(mandatory_keys.begin(), mandatory_keys.end(),
                [&fields](const auto& key) { return fields.count(key.first); })) {
                ++result;
            }
            fields.clear();
            continue;
        }
        auto key_values = split(line, ' ');
        for_each(key_values.begin(), key_values.end(),
            [&fields](const auto& kv) {
                auto semi_colon_pos = kv.find_first_of(':');
                auto key = kv.substr(0, semi_colon_pos);
                fields.emplace(key);
            }
        );
    }
    return result;
}

uint64_t sol2() {
    auto result = 0;
    string line;
    unordered_map<string, string> fields;
    while (getline(cin, line)) {
        if (line.empty()) {
            if (all_of(mandatory_keys.begin(), mandatory_keys.end(),
                [&fields](const auto& key) { return fields.count(key.first) && regex_match(fields.at(key.first), key.second); })) {
                ++result;
            }
            fields.clear();
            continue;
        }
        auto key_values = split(line, ' ');
        for_each(key_values.begin(), key_values.end(),
            [&fields](const auto& kv) {
                auto semi_colon_pos = kv.find_first_of(':');
                auto key = kv.substr(0, semi_colon_pos);
                auto value = kv.substr(semi_colon_pos + 1, string::npos);
                fields.emplace(key, value);
            }
        );
    }
    return result;
}


int main() {
    cout << sol2() << endl;
}