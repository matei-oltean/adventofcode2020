#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <unordered_set>

using namespace std;

uint64_t parse(vector<int>& vec, bool fill = false) {
    deque<int> preamble;
    string line;
    int p = 0;
    while (getline(cin, line)) {
        int curr = stoi(line);
        if (fill) {
            vec.push_back(curr);
        }
        if (p < 25) {
            preamble.push_back(curr);
            ++p;
            continue;
        }
        bool found = false;
        unordered_set<int> p;
        for (int n : preamble) {
            if (curr - n != n && p.count(curr - n)) {
                found = true;
                break;
            }
            p.emplace(n);
        }
        if (!found) {
            return curr;
        }
        preamble.push_back(curr);
        preamble.pop_front();
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
    while (i < v.size() && j < v.size()) {
        while (sum < invalid) {
            sum += v[++j];
        }
        while (sum > invalid) {
            sum -= v[i++];
        }
        if (sum == invalid) {
            int high = v[i], low = v[i];
            for (; i <= j; ++i) {
                high = max(high, v[i]);
                low = min(low, v[i]);
            }
            return high + low;
        }
    }
    return 0;
}

int main() {
    cout << sol2() << endl;
}