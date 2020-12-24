#include <string>
#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;
using point = pair<int, int>;

set<point> neigh {
    { -2,  0 },
    {  2,  0 },
    {  1,  1 },
    {  1, -1 },
    { -1,  1 },
    { -1, -1 }
};

set<point> initial_tiles() {
    set<point> tiles;
    string line;
    while (getline(cin, line)) {
        int x = 0, y = 0;
        for (int i = 0; i < line.size(); ++i) {
            char c = line[i];
            bool m_y = false;
            if (c == 's' || c == 'n') {
                y += c == 'n' ? 1 : -1;
                m_y = true;
                c = line[++i];
            }
            x = x + (m_y ? 1 : 2)*(c == 'e' ? -1 : 1);
        }
        if (!tiles.count({ x, y })) {
            tiles.emplace(x, y);
        } else {
            tiles.erase({ x, y });
        }
    }
    return tiles;
}

void run(set<point>& active, size_t iterations) {
    for (size_t iter = 0; iter < iterations; ++iter) {
        set<point> new_active;
        unordered_map<int, unordered_map<int, int> > neighbours;
        for (const auto& pt : active) {
            const auto& [x, y] = pt;
            for (const auto& [dx, dy] : neigh) {
                neighbours[x + dx][y + dy] += 1;
            }
        }
        for (const auto& x : neighbours) {
            for (const auto& y : x.second) {
                const point p(x.first, y.first);
                if (y.second == 2 || (y.second == 1 && active.count(p))) {
                    new_active.emplace(p);
                }
            }
        }
        active = new_active;
    }
}

int main() {
    set<point> tiles = initial_tiles();
    cout << tiles.size() << endl;
    run(tiles, 100);
    cout << tiles.size() << endl;
}