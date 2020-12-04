#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

const unordered_set<string> mandatory_keys { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

uint64_t sol1() {
    auto result = 0;
    string line;
    unordered_set<string> fields;
    while (getline(cin, line)) {
        if (line.empty()) {
            auto valid = true;
            for (auto key: mandatory_keys) {
                if (!fields.count(key)) {
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


int main() {
    cout << sol1() << endl;
}