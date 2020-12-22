#include <string>
#include <iostream>
#include <deque>
#include <unordered_set>

using namespace std;

string dtos(const deque<int>& d) {
    string res = "";
    for (const auto i : d) {
        res += i + ',';
    }
    return res.substr(0, res.size() - 1);
}

pair<deque<int>, deque<int> > parse() {
    deque<int> player1, player2;
    string line;
    uint64_t res = 0;
    bool first = true;
    while (getline(cin, line)) {
        if (line.empty()) {
            first = false;
            continue;
        }
        if (line[0] == 'P') {
            continue;
        }
        int card = stoi(line);
        if (first) {
            player1.push_back(card);
        } else {
            player2.push_back(card);
        }
    }
    return { player1, player2 };
}

uint64_t get_score(deque<int>& winning) {
    uint64_t res = 0, mult = 1;
    while (!winning.empty()) {
        res += mult * winning.back();
        ++mult;
        winning.pop_back();
    }
    return res;
}

uint64_t sol1() {
    auto [player1, player2] = parse();
    while (!player1.empty() && !player2.empty()) {
        int p1 = player1.front(), p2 = player2.front();
        player1.pop_front();
        player2.pop_front();
        bool o_g_t = p1 > p2;
        deque<int>& winning = o_g_t ? player1 : player2;
        winning.push_back(o_g_t ? p1 : p2);
        winning.push_back(o_g_t ? p2 : p1);
    }
    return get_score(player1.empty() ? player2 : player1);
}

bool sub_game(deque<int>& player1, deque<int>& player2) {
    bool first_has_won = false;
    unordered_set<string> seen1, seen2;
    while (!player1.empty() && !player2.empty()) {
        string p1tos = dtos(player1), p2tos = dtos(player2);
        if (seen1.count(p1tos) || seen2.count(p2tos)) {
            first_has_won = true;
            break;
        }
        seen1.emplace(p1tos);
        seen2.emplace(p2tos);
        int p1 = player1.front(), p2 = player2.front();
        player1.pop_front();
        player2.pop_front();
        bool one_won = p1 > p2;
        if (p1 <= player1.size() && p2 <= player2.size()) {
            deque<int> new_p1, new_p2;
            int i = 0, j = 0;
            for (const auto card : player1) {
                new_p1.push_back(card);
                if (++i == p1) {
                    break;
                }
            }
            for (const auto card : player2) {
                new_p2.push_back(card);
                if (++j == p2) {
                    break;
                }
            }
            one_won = sub_game(new_p1, new_p2);
        }
        deque<int>& winning = one_won ? player1 : player2;
        winning.push_back(one_won ? p1 : p2);
        winning.push_back(one_won ? p2 : p1);
    }
    return first_has_won || player2.empty();
}

uint64_t sol2() {
    auto [player1, player2] = parse();
    return get_score(sub_game(player1, player2) ? player1 : player2);
}

int main() {
    cout << sol2() << endl;
}