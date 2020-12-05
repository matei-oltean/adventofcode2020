#include <string>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <./utils.h>

using namespace std;

int ID(string& seat) {
    replace(seat.begin(), seat.end(), 'B', '1');
    replace(seat.begin(), seat.end(), 'F', '0');
    replace(seat.begin(), seat.end(), 'R', '1');
    replace(seat.begin(), seat.end(), 'L', '0');
    return stoi(seat, nullptr, 2);
}

uint64_t sol1() {
    auto result = 0;
    string line;
    while (getline(cin, line)) {
        result = max(result, ID(line));
    }
    return result;
}

uint64_t sol2() {
    string line;
    int minID = 1024;
    unordered_set<int> seats;
    while (getline(cin, line)) {
        int id = ID(line);
        minID = min(minID, id);
        seats.emplace(id);
    }
    for (; minID < 1024; ++minID) {
        if (!seats.count(minID)) {
            return minID;
        }
    }
    return 0;
}


int main() {
    cout << sol2() << endl;
}