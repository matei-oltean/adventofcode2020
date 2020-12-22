#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <array>

using namespace std;
using tile = array<string, 4>;

uint64_t sol1() {
    uint64_t res = 1;
    string line;
    unordered_map<string, int> counts;
    unordered_map<int, tile> id_to_borders;
    unordered_set<int> ids;
    while (getline(cin, line)) {
        if (line.empty()) {
            continue;
        }
        int id = stoi(line.substr(5, line.size() - 1 - 5));
        ids.emplace(id);
        tile border = { "", "", "", ""};
        for (int i = 0; i < 10; ++i) {
            getline(cin, line);
            if (i == 0) {
                border[0] = line;
            }
            if (i == 9) {
                border[3] = line;
            }
            border[1] += line[0];
            border[2] += line[line.size() - 1];
        }
        id_to_borders.emplace(id, border);
        for (const auto& bord: border) {
            for (const auto& s : { bord , string(bord.rbegin(), bord.rend()) }) {
                counts[s] += 1;
            }
        }
    }
    for (const int id : ids) {
        int found = 0;
        for (const auto& b : id_to_borders[id]) {
            int c = counts[b];
            if (c > 1) {
                ++found;
            }
        }
        if (found == 2) {
            res *= id;
        }
    }
    return res;
}

int main() {
    cout << sol1() << endl;
}