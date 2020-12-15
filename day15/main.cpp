#include <string>
#include <iostream>
#include <utils.h>
#include <vector>

using namespace std;

pair<int, int> parse(vector<int>& memory) {
    string line;
    getline(cin, line);
    const auto parsed = split(line, ',');
    for (size_t i = 0; i < parsed.size() - 1; ++i) {
        memory[stoi(parsed[i])] = i;
    }
    return make_pair(stoi(parsed.back()), parsed.size() - 1);
}

int n_nth_number(size_t n) {
    vector<int> memory(n, -1);
    auto [last, initial_size] = parse(memory);
    for (size_t i = initial_size; i < n - 1; ++i) {
        const int new_last = memory[last] == -1 ? 0 : i - memory[last];
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