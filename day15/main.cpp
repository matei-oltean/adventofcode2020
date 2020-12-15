#include <string>
#include <iostream>
#include <utils.h>
#include <unordered_map>
#include <regex>

using namespace std;

pair<int, unordered_map<int, pair<int, int> > > parse() {
    unordered_map<int, pair<int, int> > res;
    string line;
    getline(cin, line);
    auto parsed = split(line, ',');
    for (size_t i = 0; i < parsed.size(); ++i) {
        res[stoi(parsed[i])] = make_pair(i, i);
    }
    return make_pair(stoi(parsed.back()), res);
}

int n_nth_number(int n) {
    auto [last, memory] = parse();
    for (size_t i = memory.size(); i < n; ++i) {
        auto& [f, l] = memory[last];
        last = l - f;
        if (memory.count(last)) {
            auto [ff, ll] = memory[last];
            memory[last] = make_pair(ll, i);
        } else {
            memory[last] = make_pair(i, i);
        }
    }
    return last;
}

uint64_t sol1() {
    return n_nth_number(2020);
}

uint64_t sol2() {
    return n_nth_number(30000000);
}

int main() {
    cout << sol2() << endl;
}