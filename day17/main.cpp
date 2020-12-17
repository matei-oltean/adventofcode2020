#include <string>
#include <iostream>
#include <set>
#include <map>
#include <tuple>

using namespace std;
using point = tuple<int, int, int>;
using point4d = tuple<int, int, int, int>;

void run(set<point>& active, size_t iterations) {
    for (size_t iter = 0; iter < iterations; ++iter) {
        set<point> new_active;
        map<point, int> neighbours;
        for (const auto& pt : active) {
            const auto& [x, y, z] = pt;
            neighbours[pt] -= 1;
            for (int xx = x - 1; xx <= x + 1; ++xx) {
                for (int yy = y - 1; yy <= y + 1; ++yy) {
                    for (int zz = z - 1; zz <= z + 1; ++zz) {
                        neighbours[make_tuple(xx, yy, zz)] += 1;
                    }
                }
            }
        }
        for (const auto& cube : neighbours) {
            if (cube.second == 3 || (cube.second == 2 && active.count(cube.first))) {
                new_active.emplace(cube.first);
            }
        }
        active = new_active;
    }
}

void run(set<point4d>& active, size_t iterations) {
    for (size_t iter = 0; iter < iterations; ++iter) {
        set<point4d> new_active;
        map<point4d, int> neighbours;
        for (const auto& pt : active) {
            const auto& [x, y, z, w] = pt;
            neighbours[pt] -= 1;
            for (int xx = x - 1; xx <= x + 1; ++xx) {
                for (int yy = y - 1; yy <= y + 1; ++yy) {
                    for (int zz = z - 1; zz <= z + 1; ++zz) {
                        for (int ww = w - 1; ww <= w + 1; ++ww) {
                            neighbours[make_tuple(xx, yy, zz, ww)] += 1;
                        }
                    }
                }
            }
        }
        for (const auto& cube : neighbours) {
            if (cube.second == 3 || (cube.second == 2 && active.count(cube.first))) {
                new_active.emplace(cube.first);
            }
        }
        active = new_active;
    }
}

uint64_t sol1() {
    string line;
    int x = 0;
    set<point> active;
    while(getline(cin, line)) {
        for (int j = 0; j < line.size(); ++j) {
            if (line[j] == '#') {
                active.emplace(x, j, 0);
            }
        }
        ++x;
    }
    run(active, 6);
    return active.size();
}

uint64_t sol2() {
    string line;
    int x = 0;
    set<point4d> active;
    while(getline(cin, line)) {
        for (int j = 0; j < line.size(); ++j) {
            if (line[j] == '#') {
                active.emplace(x, j, 0, 0);
            }
        }
        ++x;
    }
    run(active, 6);
    return active.size();
}

int main() {
    cout << sol2() << endl;
}