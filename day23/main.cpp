#include <string>
#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

string input = "157623984";
string test  = "389125467";

inline int next(int current) {
    return current == 1 ? 9 : current - 1;
}

void sol1() {
    deque<int> cups;
    for (const char c : input) {
        cups.emplace_back((int) (c - '0'));
    }
    for (int i = 0; i < 100; ++i) {
        int current = cups.front();
        cups.pop_front();
        int destination = next(current);
        deque<int> tmp;
        for (int j = 0; j < 3; ++j) {
            tmp.emplace_back(cups.front());
            cups.pop_front();
        }
        for (int j = 0; j < 3; ++j) {
            for (const int k : tmp) {
                if (k == destination) {
                    destination = next(destination);
                    break;
                }
            }
        }
        auto it = find(cups.begin(), cups.end(), destination);
        cups.insert(++it, tmp.begin(), tmp.end());
        cups.push_back(current);
    }
    while (cups.front() != 1) {
        cups.push_back(cups.front());
        cups.pop_front();
    }
    cups.pop_front();
    for (const int k : cups) {
        cout << k;
    }
    cout << endl;
}

inline int next_bis(int current) {
    return current == 1 ? 1000000 : current - 1;
}

void sol2() {
    deque<int> cups;
    for (const char c : input) {
        cups.emplace_back((int) (c - '0'));
    }
    for (int i = 10; i <= 1000000; ++i) {
        cups.emplace_back(i);
    }
    for (int i = 0; i < 10000000; ++i) {
        if (!(i % 10000)) {
            cout << i << endl;
        }
        int current = cups.front();
        cups.pop_front();
        int destination = next_bis(current);
        deque<int> tmp;
        for (int j = 0; j < 3; ++j) {
            tmp.emplace_back(cups.front());
            cups.pop_front();
        }
        for (int j = 0; j < 3; ++j) {
            for (const int k : tmp) {
                if (k == destination) {
                    destination = next_bis(destination);
                    break;
                }
            }
        }
        auto it = find(cups.begin(), cups.end(), destination);
        cups.insert(++it, tmp.begin(), tmp.end());
        cups.push_back(current);
    }
    auto it = find(cups.begin(), cups.end(), 1);
    uint64_t res  = *(++it);
    res *= *(++it);
    cout << res << endl;
}

int main() {
    sol2();
}