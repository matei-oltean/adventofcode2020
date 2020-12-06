#include <string>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

void set_from_string(unordered_set<char>& set, const string& str) {
    for_each(str.begin(), str.end(), [&set] (char c) { set.emplace(c); });
}

uint64_t sol1() {
    uint64_t result = 0;
    string line;
    unordered_set<char> answers;
    while (getline(cin, line) || answers.size()) {
        if (line.empty()) {
            result += answers.size();
            answers.clear();
            continue;
        }
        set_from_string(answers, line);
    }
    return result;
}

uint64_t sol2() {
    uint64_t result = 0;
    string line;
    unordered_set<char> answers;
    bool first = true;
    while (getline(cin, line) || answers.size()) {
        if (line.empty()) {
            result += answers.size();
            answers.clear();
            first = true;
            continue;
        }
        if (first) {
            set_from_string(answers, line);
            first = false;
        } else {
            unordered_set<char> group, temp;
            set_from_string(group, line);
            for_each(answers.begin(), answers.end(),
                [&temp, &group](char c) {
                    if (group.count(c)) {
                        temp.emplace(c);
                    }
                });
            answers = temp;
        }
    }
    return result;
}

int main() {
    cout << sol2() << endl;
}