#include <string>
#include <iostream>
#include <utils.h>
#include <unordered_map>

using namespace std;

pair<int, unordered_map<int,int> > parse() {
    unordered_map<int, int> res;
    string line;
    getline(cin, line);
    auto parsed = split(line, ',');
    for (size_t i = 0; i < parsed.size() - 1; ++i) {
        res[stoi(parsed[i])] = i;
    }
    return make_pair(stoi(parsed.back()), res);
}

int n_nth_number(int n) {
    auto [last, memory] = parse();
    for (size_t i = memory.size(); i < n - 1; ++i) {
        int new_last = memory.count(last) ? i - memory[last] : 0;
        memory[last] = i;
        last = new_last;
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