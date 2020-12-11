#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int convert(char c) {
    return c == '#' ? 1 : 0;
}

vector<vector<char> > parse() {
    string line;
    vector<vector<char> > game;
    while (getline(cin, line)) {
        vector<char> v;
        for (char c : line) {
            v.push_back(c);
        }
        game.push_back(v);
    }
    return game;
}

int living_neighbours(const vector<vector<char> >& game, int i, int j) {
    auto res = -convert(game[i][j]);
    for (size_t ii = max(i - 1, 0); ii < min(i + 2, int(game.size())); ++ii) {
        for (size_t jj = max(j - 1, 0); jj < min(j + 2, int(game[i].size())); ++jj) {
            res += convert(game[ii][jj]);
        }
    }
    return res;
}

int seen_neighbours(const vector<vector<char> >& game, int i, int j) {
    auto res = -convert(game[i][j]);;
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

void run(vector<vector<char> >& game, int threshold, function<int(const vector<vector<char> >& game, int i, int j)> neighbours) {
    bool changed = true;
    while (changed) {
        vector<vector<char> > temp;
        changed = false;
        for (size_t i = 0; i < game.size(); ++i) {
            vector<char> v;
            for (size_t j = 0; j < game[i].size(); ++j) {
                auto state = game[i][j];
                if (state == '.') {
                    v.push_back('.');
                    continue;
                }
                auto living = neighbours(game, i, j);
                if (state == 'L') {
                    if (living == 0) {
                        v.push_back('#');
                        changed = true;
                    } else {
                        v.push_back('L');
                    }
                } else {
                    if (living >= threshold) {
                        v.push_back('L');
                        changed = true;
                    } else {
                        v.push_back('#');
                    }
                }
            }
            temp.push_back(v);
        }
        game = temp;
    }
}

uint64_t sol1() {
    auto v = parse();
    run(v, 4, living_neighbours);
    int res = 0;
    for (auto row : v) {
        for (auto seat : row) {
            res += convert(seat);
        }
    }
    return res;
}

uint64_t sol2() {
    auto v = parse();
    run(v, 5, seen_neighbours);
    int res = 0;
    for (auto row : v) {
        for (auto seat : row) {
            res += convert(seat);
        }
    }
    return res;
}

int main() {
    cout << sol2() << endl;
}