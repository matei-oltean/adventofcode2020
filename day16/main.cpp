#include <string>
#include <iostream>
#include <utils.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <regex>

using namespace std;

uint64_t sol1() {
    string line;
    bool f = true;
    uint64_t res = 0;
    unordered_set<int> valid;
    while (getline(cin, line)) {
        if (line.empty()) {
            f = false;
            continue;
        }
        if (f) {
            const auto num = split(split(line, regex(":\\s")).back(), regex("\\sor\\s"));
            for (const string& s : num) {
                auto bound = split(s, '-');
                for (int i = stoi(bound.front()); i <= stoi(bound.back()); ++i) {
                    valid.emplace(i);
                }
            }
            continue;
        }
        if (line[0] == 'y' || line[0] == 'n') {
            continue;
        }
        const auto fields = split(line, ',');
        for (const string& field : fields) {
            if (!valid.count(stoi(field))) {
                res += stoi(field);
            }

        }
    }
    return res;
}

uint64_t sol2() {
    string line;
    int step = 0;
    uint64_t res = 1;
    unordered_set<int> valid;
    vector<int> my_ticket;
    unordered_map<int, unordered_set<string> > mapping;
    unordered_map<string, unordered_set<int>> possible;
    while (getline(cin, line)) {
        if (line.empty()) {
            ++step;
            continue;
        }
        if (step == 0) {
            const auto spl = split(line, regex(":\\s"));
            const string name = spl.front();
            unordered_set<int> this_map;
            const auto num = split(spl.back(), regex("\\sor\\s"));
            for (const string& s : num) {
                auto bound = split(s, '-');
                for (int i = stoi(bound.front()); i <= stoi(bound.back()); ++i) {
                    valid.emplace(i);
                    this_map.emplace(i);
                }
            }
            possible.emplace(name, this_map);
            continue;
        } else if (step == 1) {
            if (line[0] == 'y') {
                continue;
            }
            const auto fields = split(line, ',');
            for (const string& field : fields) {
                my_ticket.emplace_back(stoi(field));
            }
            continue;
        }
        if (line[0] == 'n') {
            continue;
        }
        const auto fields = split(line, ',');
        unordered_map<int, unordered_set<string> > temp_map;
        bool valid_ticket = true;
        for (int i = 0; i < fields.size(); ++i) {
            const string field_name = fields[i];
            int field_val = stoi(field_name);
            if (!valid.count(field_val)) {
                valid_ticket = false;
                break;
            }
            unordered_set<string> possible_map;
            for (const auto& kv : possible) {
                if (kv.second.count(field_val)) {
                    possible_map.emplace(kv.first);
                }
            }
            temp_map[i] = possible_map;
        }
        if (!valid_ticket) {
            continue;
        }
        for (int i = 0; i < fields.size(); ++i) {
            unordered_set<string> new_map;
            for (const auto& s: temp_map[i]) {
                if (!mapping.count(i) || mapping[i].count(s)) {
                    new_map.emplace(s);
                }
            }
            mapping[i] = new_map;
        }
    }
    int found = 0;
    while (mapping.size()) {
        string key;
        int pos;
        for (const auto& kv : mapping) {
            if (kv.second.size() > 1) {
                continue;
            }
            pos = kv.first;
            key = *(kv.second.begin());
            if (key.rfind("departure", 0) == 0) {
                res *= my_ticket[kv.first];
                found += 1;
                if (found == 6) {
                    return res;
                }
            }
        }
        mapping.erase(pos);
        for (auto& kv: mapping) {
            kv.second.erase(key);
        }
    }
    return res;
}

int main() {
    cout << sol2() << endl;
}