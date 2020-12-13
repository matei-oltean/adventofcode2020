#include <string>
#include <iostream>
#include <utils.h>

using namespace std;

// Returns k such that a*k = 1 (b)
uint64_t inv_mod(uint64_t a, uint64_t b) {
    int64_t r0 = a, r1 = b, u0 = 1, u1 = 0;
    while (r1) {
        int64_t q = r0/r1;
        int64_t r = r0 - r1 * q;
        int64_t u = u0 - u1 * q;
        u0 = u1, r0 = r1;
        u1 = u, r1 = r;
    }
    return u0 < 0 ? u0 + b : u0;
}

uint64_t sol1() {
    string line;
    int arrival = 0, diff = 0, min_id = -1;
    while (getline(cin, line)) {
        if (!arrival) {
            arrival = stoi(line);
            diff = arrival;
            continue;
        }
        auto ids = split(line, ',');
        for (string id : ids) {
            if (id == "x") {
                continue;
            }
            int int_id = stoi(id);
            int min_possible = int_id - (arrival % int_id);
            if (min_possible < diff) {
                diff = min_possible;
                min_id = int_id;
            }
        }
    }
    return min_id * diff;
}

uint64_t sol2() {
    string line;
    bool first = false;
    while (getline(cin, line)) {
        if (!first) {
            first = true;
            continue;
        }
        auto ids_old = split(line, ',');
        uint64_t n = 1;
        vector<pair<int, int> > ids;
        for (size_t j = 0; j < ids_old.size(); ++j) {
            if (ids_old[j] == "x") {
                continue;
            }
            int int_id = stoi(ids_old[j]);
            ids.push_back({ j, int_id });
            n *= int_id;
        }
        uint64_t sol = 0;
        for (auto pair : ids) {
            auto [j, id] = pair;
            uint64_t ni = n/id;
            sol += ni * inv_mod(ni, id) * (id - j);
        }
        return sol % n;
    }
    return 0;
}

int main() {
    cout << sol2() << endl;
}