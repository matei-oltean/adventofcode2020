#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

inline int convert(char c) {
    return c == '#';
}

vector<string> parse() {
    string line;
    vector<string> game;
    while (getline(cin, line)) {
        game.push_back(line);
    }
    return game;
}

int living_neighbours(const vector<string>& game, int i, int j) {
    auto res = -convert(game[i][j]);
    for (size_t ii = max(i - 1, 0); ii < min(i + 2, int(game.size())); ++ii) {
        for (size_t jj = max(j - 1, 0); jj < min(j + 2, int(game[i].size())); ++jj) {
            res += convert(game[ii][jj]);
        }
    }
    return res;
}

int seen_neighbours(const vector<string>& game, int i, int j) {
    auto res = -convert(game[i][j]);
    vector<pair<int, int> > directions;
    for (int k = -1; k < 2; ++k) {
        for (int kk = -1; kk < 2; ++kk) {
            directions.emplace_back(k, kk);
        }
    }
    for (auto& [di, dj] : directions) {
        int ii = i + di, jj = j + dj;
        while (ii >= 0 && jj >= 0 && ii < game.size() && jj < game[ii].size() && game[ii][jj] != 'L') {
            if (game[ii][jj] == '#') {
                res += 1;
                break;
            }
            ii += di;
            jj += dj;
        }
    }
    return res;
}

void run(vector<string>& game, int threshold, function<int(const vector<string>& game, int i, int j)> neighbours) {
    bool changed = true;
    while (changed) {
        vector<string> temp;
        changed = false;
        for (size_t i = 0; i < game.size(); ++i) {
            string s = game[i];
            for (size_t j = 0; j < game[i].size(); ++j) {
                auto state = game[i][j];
                if (state == '.') {
                    continue;
                }
                auto living = neighbours(game, i, j);
                if (state == 'L') {
                    if (living == 0) {
                        s[j] = '#';
                        changed = true;
                    }
                } else {
                    if (living >= threshold) {
                        s[j] = 'L';
                        changed = true;
                    }
                }
            }
            temp.push_back(s);
        }
        game = temp;
    }
}

uint64_t count_occupied(const vector<string>& seats) {
    int res = 0;
    for (auto row : seats) {
        for (auto seat : row) {
            res += convert(seat);
        }
    }
    return res;
}

uint64_t sol1() {
    auto v = parse();
    run(v, 4, living_neighbours);
    return count_occupied(v);
}

uint64_t sol2() {
    auto v = parse();
    run(v, 5, seen_neighbours);
    return count_occupied(v);
}

int main() {
    cout << sol2() << endl;
}