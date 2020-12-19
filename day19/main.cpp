#include <string>
#include <iostream>
#include <regex>
#include <utils.h>
#include <unordered_map>
#include <vector>

using namespace std;

string find_condition(size_t index, const unordered_map<int, vector<vector<int>>>& conditions, unordered_map<int, string>& chars, bool bis) {
    if (chars.count(index)) {
        return chars[index];
    }
    if (bis && index == 8) {
        string res = '(' + find_condition(42, conditions, chars, bis) + ")+";
        chars[8] = res;
        return res;
    }

    if (bis && index == 11) {
        string first = find_condition(42, conditions, chars, bis);
        string second = find_condition(31, conditions, chars, bis);
        string res = "((" + first + second + ')';
        for (int j = 1; j < 6; ++j) {
            res += "|(";
            for (int k = 0; k <= j; ++k) {
                res += first;
            }
            for (int k = 0; k <= j; ++k) {
                res += second;
            }
            res += ')';
        }
        res += ')';
        chars[11] = res;
        return res;
    }

    string res = "";
    const auto& cond = conditions.at(index);
    if (cond.size() > 1) {
        res += '(';
    }
    for (size_t i = 0; i < cond.size(); ++i) {
        if (i) {
            res += '|';
        }
        res += '(';
        for (const auto& vc : cond[i]) {
            res += find_condition(vc, conditions, chars, bis);
        }
        res += ')';
    }
    if (cond.size() > 1) {
        res += ')';
    }
    chars[index] = res;
    return res;
}

uint64_t parse_and_find(bool bis) {
    string line;
    uint64_t res = 0;
    bool cond = true;
    unordered_map<int, vector<vector<int>>> conditions;
    unordered_map<int, string> chars;
    regex to_match;
    while (getline(cin, line)) {
        if (line.empty()) {
            cond = false;
            to_match = regex(find_condition(0, conditions, chars, bis));
            continue;
        }
        if (cond) {
            const auto l = split(line, regex(":\\s"));
            int index = stoi(l.front());
            if (l.back().find_first_of('"') != string::npos) {
                chars[index] = split(l.back(), '"').front();
            } else {
                vector<vector<int>> this_cond;
                for (const auto& co : split(l.back(), regex("\\s\\|\\s"))) {
                    vector<int> new_cond;
                    for (const auto& a : split(co, ' ')) {
                        new_cond.push_back(stoi(a));
                    }
                    this_cond.push_back(new_cond);
                }
                conditions[index] = this_cond;
            }
        } else if (regex_match(line, to_match)) {
            ++res;
        }
    }
    return res;
}

uint64_t sol1() {
    return parse_and_find(false);
}

uint64_t sol2() {
    return parse_and_find(true);
}

int main() {
    cout << sol2() << endl;
}