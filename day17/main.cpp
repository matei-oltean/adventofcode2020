#include <string>
#include <iostream>
#include <set>
#include <unordered_map>
#include <tuple>

using namespace std;
using point = tuple<int, int, int>;
using point4d = tuple<int, int, int, int>;
using map3d = unordered_map<int, unordered_map<int, unordered_map<int, int> > >;
using map4d = unordered_map<int, map3d>;

void run(set<point>& active, size_t iterations) {
    for (size_t iter = 0; iter < iterations; ++iter) {
        set<point> new_active;
        map3d neighbours;
        for (const auto& pt : active) {
            const auto& [x, y, z] = pt;
            neighbours[x][y][z] -= 1;
            for (int xx = x - 1; xx <= x + 1; ++xx) {
                for (int yy = y - 1; yy <= y + 1; ++yy) {
                    for (int zz = z - 1; zz <= z + 1; ++zz) {
                        neighbours[xx][yy][zz] += 1;
                    }
                }
            }
        }
        for (const auto& x : neighbours) {
            for (const auto& y : x.second) {
                for (const auto& z : y.second) {
                    const point p = make_tuple(x.first, y.first, z.first);
                    if (z.second == 3 || (z.second == 2 && active.count(p))) {
                        new_active.emplace(p);
                    }
                }
            }
        }
        active = new_active;
    }
}

void run(set<point4d>& active, size_t iterations) {
    for (size_t iter = 0; iter < iterations; ++iter) {
        set<point4d> new_active;
        map4d neighbours;
        for (const auto& pt : active) {
            const auto& [x, y, z, w] = pt;
            neighbours[x][y][z][w] -= 1;
            for (int xx = x - 1; xx <= x + 1; ++xx) {
                for (int yy = y - 1; yy <= y + 1; ++yy) {
                    for (int zz = z - 1; zz <= z + 1; ++zz) {
                        for (int ww = w - 1; ww <= w + 1; ++ww) {
                            neighbours[xx][yy][zz][ww] += 1;
                        }
                    }
                }
            }
        }
        for (const auto& x : neighbours) {
            for (const auto& y : x.second) {
                for (const auto& z : y.second) {
                    for (const auto& cube : z.second) {
                        const point4d p = make_tuple(x.first, y.first, z.first, cube.first);
                        if (cube.second == 3 || (cube.second == 2 && active.count(p))) {
                            new_active.emplace(p);
                        }
                    }
                }
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