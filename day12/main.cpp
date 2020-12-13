#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

inline int manhattan(const pair<int, int>& position) {
    return std::abs(position.first) + std::abs(position.second);
}

inline void next_dir(pair<int, int>& direction, int right) {
    auto [x, y] = direction;
    direction.first = - y * right;
    direction.second = x * right;
}

void process(const string& line, pair<int, int>& position, pair<int, int>& direction, bool move_to_waypoint) {
    char instruction = line.at(0);
    int val = stoi(line.substr(1, string::npos));
    pair<int, int>& pos_to_be_moved = move_to_waypoint ? direction : position;
    if (instruction == 'N') {
        pos_to_be_moved.first += val;
    } else if (instruction == 'S') {
        pos_to_be_moved.first -= val;
    } else if (instruction == 'E') {
        pos_to_be_moved.second += val;
    } else if (instruction == 'W') {
        pos_to_be_moved.second -= val;
    } else if (instruction == 'F') {
        position.first += val * direction.first;
        position.second += val * direction.second;
    } else {
        for (int i = 0; i < val / 90; ++i) {
            next_dir(direction, instruction == 'R' ? 1 : -1);
        }
    }
}

uint64_t sol1() {
    pair<int, int> position(0, 0), direction(0, 1);
    string line;
    while (getline(cin, line)) {
        process(line, position, direction, false);
    }
    return manhattan(position);
}

uint64_t sol2() {
    pair<int, int> position(0, 0), waypoint(1, 10);
    string line;
    while (getline(cin, line)) {
        process(line, position, waypoint, true);
    }
    return manhattan(position);
}

int main() {
    cout << sol2() << endl;
}