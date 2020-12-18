#include <string>
#include <iostream>

using namespace std;

inline uint64_t get_res(uint64_t x, uint64_t y, char op) {
    return op == '+' ? x + y : x * y;
}

pair<uint64_t, size_t> compute(const string& s, size_t i) {
    uint64_t res = 0;
    char op = '+';
    while (i < s.size()) {
        if (s[i] == ' ') {
            ++i;
            continue;
        }
        if (s[i] == '*' || s[i] == '+') {
            op = s[i++];
            continue;
        }
        if (s[i] == ')') {
            return { res, i + 1 };
        }
        if (s[i] == '(') {
            const auto& [r, ii] = compute(s, i + 1);
            i = ii;
            res = get_res(res, r, op);
            continue;
        }
        res = get_res(res, (int)(s[i++] - '0'), op);
    }
    return { res, string::npos };
}

pair<uint64_t, size_t> compute_bis(const string& s, size_t i) {
    uint64_t res = 0;
    while (i < s.size()) {
        if (s[i] == ' ' || s[i] == '+') {
            ++i;
            continue;
        }
        if (s[i] == '*') {
            const auto& [r, ii] = compute_bis(s, i + 1);
            return { res * r, ii };
        }
        if (s[i] == ')') {
            return { res, i + 1 };
        }
        if (s[i] == '(') {
            const auto& [r, ii] = compute_bis(s, i + 1);
            i = ii;
            res += r;
            continue;
        }
        res += (int)(s[i++] - '0');
    }
    return { res, string::npos };
}

uint64_t sol1() {
    string line;
    uint64_t sum = 0;
    while (getline(cin, line)) {
        sum += compute(line, 0).first;
    }
    return sum;
}

uint64_t sol2() {
    string line;
    uint64_t sum = 0;
    while (getline(cin, line)) {
        sum += compute_bis(line, 0).first;
    }
    return sum;
}

int main() {
    cout << sol2() << endl;
}