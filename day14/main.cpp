#include <string>
#include <iostream>
#include <utils.h>
#include <unordered_map>
#include <regex>

using namespace std;

inline uint64_t count_bits(const unordered_map<uint64_t, uint64_t>& memory) {
    uint64_t res = 0;
    for (auto v : memory) {
        res += v.second;
    }
    return res;
}

uint64_t sol1() {
    string line;
    unordered_map<uint64_t, uint64_t> memory;
    string mask;
    while (getline(cin, line)) {
        auto m = split(line, regex("\\s=\\s"));
        if (line[1] == 'a') {
            mask = m.back();
            reverse(mask.begin(), mask.end());
        } else {
            uint64_t num = stoull(m.back());
            uint64_t mem = stoull(m.front().substr(4, m.front().size() - 5));
            string num_bis = mask;
            for (size_t i = 0; i < num_bis.size(); ++i) {
                if (num_bis[i] != 'X') {
                    continue;
                }
                num_bis[i] = (num & (1 << i)) >> i ? '1' : '0';
            }
            reverse(num_bis.begin(), num_bis.end());
            memory[mem] = stoull(num_bis, nullptr, 2);
        }
    }
    return count_bits(memory);
}

uint64_t sol2() {
    string line;
    unordered_map<uint64_t, uint64_t> memory;
    string mask;
    while (getline(cin, line)) {
        auto m = split(line, regex("\\s=\\s"));
        if (line[1] == 'a') {
            mask = m.back();
            reverse(mask.begin(), mask.end());
        } else {
            uint64_t num = stoull(m.back());
            uint64_t mem = stoull(m.front().substr(4, m.front().size() - 5));
            string num_bis = mask;
            for (size_t i = 0; i < num_bis.size(); ++i) {
                if (num_bis[i] == '0') {
                    num_bis[i] = (mem & (1 << i)) >> i ? '1' : '0';
                }
            }
            reverse(num_bis.begin(), num_bis.end());
            vector<string> idx { "" };
            size_t last = 0;
            for (size_t i = 0; i < num_bis.size(); ++i) {
                if (num_bis[i] != 'X') {
                    continue;
                }
                vector<string> temp;
                string s_to_add = num_bis.substr(last, i - last);
                last = i + 1;
                for (string s : idx) {
                    temp.emplace_back(s + s_to_add + '1');
                    temp.emplace_back(s + s_to_add + '0');
                }
                idx = temp;
            }
            vector<string> temp;
            string s_to_add = num_bis.substr(last, string::npos);
            for (string s : idx) {
                temp.emplace_back(s + s_to_add);
            }
            for (string id : temp) {
                memory[stoull(id, nullptr, 2)] = num;
            }
        }
    }
    return count_bits(memory);
}

int main() {
    cout << sol2() << endl;
}