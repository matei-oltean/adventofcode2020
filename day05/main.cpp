#include <string>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <./utils.h>

using namespace std;

int ID(const pair<int, int>& seat) {
    return 8 * seat.first + seat.second;
}

uint64_t sol1() {
    auto result = 0;
    string line;
    int mid;
    while (getline(cin, line)) {
        int low = 0, high = 127;
        for (int i = 0; i < 7; ++i) {
            mid = (low + high)/2;
            if (line.at(i) == 'F') {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        int left = 0, right = 7;
        for (int i = 7; i < 10; ++i) {
            mid = (left + right)/2;
            if (line.at(i) == 'L') {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        result = max(result, ID({ low, left }));
    }
    return result;
}

uint64_t sol2() {
    string line;
    int minID = ID({ 127, 7 }), mid;
    unordered_set<int> seats;
    while (getline(cin, line)) {
        int low = 0, high = 127;
        for (int i = 0; i < 7; ++i) {
            mid = (low + high)/2;
            if (line.at(i) == 'F') {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        int left = 0, right = 7;
        for (int i = 7; i < 10; ++i) {
            mid = (left + right)/2;
            if (line.at(i) == 'L') {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        int id = ID({ low, left });
        minID = min(minID, id);
        seats.emplace(id);
    }
    for (int i = 0; i < 127; ++i) {
        for (int j = 0; j < 8; ++j) {
            int id = ID({ i, j });
            if (id <= minID) {
                break;
            }
            if (!seats.count(id)) {
                return id;
            }
        }
    }
    return 0;
}


int main() {
    cout << sol2() << endl;
}