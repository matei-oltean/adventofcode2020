#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int> > steps {
    { 1, 1 },
    { 1, 3 },
    { 1, 5 },
    { 1, 7 },
    { 2, 1 },
};

uint64_t sol1() {
    uint64_t res = 0;
    auto index = 0;
    string line;
    while (getline(cin, line)) {
        if (line.at(index) == '#') {
            res += 1;
        }
        index = (index + 1) % line.size();
    }
    return res;
}

uint64_t sol2() {
    auto depth = 0;
    string line;
    vector<int> trees;
    for (size_t i = 0; i < steps.size(); ++i) {
        trees.push_back(0);
    }
    while (getline(cin, line)) {
        for (size_t i = 0; i < steps.size(); ++i) {
            auto xy = steps.at(i);
            if (depth % xy.first) {
                continue;
            }
            if (line.at((xy.second * depth / xy.first) % line.size()) == '#') {
                ++trees.at(i);
            }
        }
        ++depth;
    }
    uint64_t res = 1;
    for_each(trees.begin(), trees.end(), [&res](auto t) { res *= t; });
    return res;
}

int main() {
    cout << sol2() << endl;
}