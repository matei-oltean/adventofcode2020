#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

uint64_t parse(vector<int>& vec, bool fill = false) {
    deque<int> preamble;
    string line;
    while (getline(cin, line)) {
        int curr = stoi(line);
        if (fill) {
            vec.push_back(curr);
        }
        if (preamble.size() == 25) {
            unordered_set<int> p;
            if (none_of(preamble.begin(), preamble.end(), [&p, &curr](int n) {
                if (curr - n != n && p.count(curr - n)) {
                    return true;
                }
                p.emplace(n);
                return false; })) {
                return curr;
            }
            preamble.pop_front();
        }
        preamble.push_back(curr);
    }
    return 0;
}

uint64_t sol1() {
    vector<int> v;
    return parse(v);
}

uint64_t sol2() {
    vector<int> v;
    int invalid = parse(v, true);
    int i = 0, j = 0;
    int sum = v[i];
    while (sum != invalid) {
        while (sum < invalid) {
            sum += v[++j];
        }
        while (sum > invalid) {
            sum -= v[i++];
        }
    }
    int high = v[i], low = v[i];
    for (; i <= j; ++i) {
        high = max(high, v[i]);
        low = min(low, v[i]);
    }
    return high + low;
}

int main() {
    cout << sol2() << endl;
}