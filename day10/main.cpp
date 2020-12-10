#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> parse_and_sort() {
    vector<int> sorted_array;
    string line;
    while (getline(cin, line)) {
        sorted_array.push_back(stoi(line));
    }
    sort(sorted_array.begin(), sorted_array.end());
    return sorted_array;
}

uint64_t sol1() {
    auto v = parse_and_sort();
    v.push_back(v.back() + 3);
    int prec = 0;
    int diffs[3] = { 0, 0, 0 };
    for (int i : v) {
        if (i - prec > 3) {
            break;
        }
        diffs[i - prec - 1] += 1;
        prec = i;
    }
    return diffs[0] * diffs[2];
}

uint64_t num_of_ways(const vector<int>&v, unordered_map<int, uint64_t>& ways, int i) {
    if (i == v.size() - 1) {
        return 1;
    }
    if (ways.count(i)) {
        return ways.at(i);
    }
    uint64_t res = 0;
    int curr = v[i];
    for (int j = i + 1; j < v.size(); ++j) {
        if (v[j] - curr > 3) {
            break;
        }
        res += num_of_ways(v, ways, j);
    }
    ways.emplace(i, res);
    return res;
}

uint64_t sol2() {
    auto v = parse_and_sort();
    v.push_back(v.back() + 3);
    v.insert(v.begin(), 0);
    unordered_map<int, uint64_t> ways;
    return num_of_ways(v, ways, 0);
}

int main() {
    cout << sol2() << endl;
}