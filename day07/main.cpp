#include <string>
#include <iostream>
#include <algorithm>
#include <regex>
#include <utils.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;

regex contains("\\scontain\\s");
string gold("shiny gold");
string no_others("no other bags.");

bool can_form_gold_shiny(
    const string& bag_name,
    const unordered_map<string, unordered_set<string> >& sub_bags,
    unordered_map<string, bool>& can_form) {
    if (can_form.count(bag_name)) {
        return can_form.at(bag_name);
    }
    if (!sub_bags.count(bag_name)) {
        can_form.emplace(bag_name, false);
        return false;
    }
    auto bags = sub_bags.at(bag_name);
    for (string bag : bags) {
        if (can_form_gold_shiny(bag, sub_bags, can_form)) {
            can_form.emplace(bag_name, true);
            return true;
        }
    }
    can_form.emplace(bag_name, false);
    return false;
}

uint64_t sol1() {
    uint64_t result = 0;
    string line;
    unordered_map<string, bool> can_form;
    unordered_map<string, unordered_set<string> > makes;
    while (getline(cin, line)) {
        sregex_token_iterator iter(line.begin(), line.end(), contains, -1);
        string bag = *iter;
        string bags = *(++iter);
        string bag_name = split(bag, regex("\\sbag")).front();
        // this bag is useless
        if (bags == no_others) {
            can_form.emplace(bag_name, false);
            continue;
        }
        auto quantities = split(bags, regex(",\\s"));
        unordered_set<string> can_make;
        for (auto q : quantities) {
            auto quantity = split(q, regex("\\d+\\s"));
            string name = split(quantity.front(), regex("\\sbag")).front();
            if (name == gold) {
                can_form.emplace(bag_name, true);
                can_make.clear();
                break;
            }
            can_make.emplace(name);
        }
        makes.emplace(bag_name, can_make);
    }

    for (auto bag_name : makes) {
        if (can_form_gold_shiny(bag_name.first, makes, can_form)) {
            result += 1;
        }
    }
    return result;
}

uint64_t sol2() {
    return 0;
}

int main() {
    cout << sol1() << endl;
}