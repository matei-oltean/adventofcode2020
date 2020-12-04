#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

uint64_t sol1() {
    unordered_set<uint64_t> d;
    string line;
    while (getline(cin, line)) {
        auto num = stoull(line);
        if (d.count(2020-num)) {
            return num*(2020-num);
        }
        d.emplace(num);
    }
    return 0;
}

uint64_t sol2() {
    unordered_set<uint64_t> num;
    unordered_map<uint64_t, pair<uint64_t, uint64_t>> d;
    string line;
    while (getline(cin, line)) {
        auto a = stoull(line);
        if (d.count(2020-a)) {
            auto res = d.at(2020-a);
            return a*res.first*res.second;
        }
        for (auto k : num) {
            d.emplace(k+a, make_pair(k, a));
        }
        num.emplace(a);
    }
    return 0;
}

int main() {
    cout << sol2() << endl;
}