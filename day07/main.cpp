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
    if (any_of(bags.begin(), bags.end(), [&sub_bags, &can_form](const string& bag) { return can_form_gold_shiny(bag, sub_bags, can_form); })) {
        can_form.emplace(bag_name, true);
        return true;
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
        string bag = *iter, bags = *(++iter);
        string bag_name = split(bag, regex("\\sbag")).front();
        // this bag is useless
        if (bags == no_others) {
            can_form.emplace(bag_name, false);
            continue;
        }
        auto quantities = split(bags, regex(",\\s"));
        unordered_set<string> can_make;
        for (const auto& q : quantities) {
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

    for (const auto& [bag_name, bag_set] : makes) {
        if (can_form_gold_shiny(bag_name, makes, can_form)) {
            result += 1;
        }
    }
    return result;
}

uint64_t must_contain(
    const string& bag_name,
    const unordered_map<string, unordered_set<string> >& sub_bags,
    unordered_map<string, uint64_t>& contain) {
    if (contain.count(bag_name)) {
        return contain.at(bag_name);
    }
    auto bags = sub_bags.at(bag_name);
    uint64_t result = 0;
    for (string bag : bags) {
        int quantity = bag.front() - '0';
        string name = bag.substr(2, string::npos);
        result += quantity * (1 + must_contain(name, sub_bags, contain));
    }
    contain.emplace(bag_name, result);
    return result;
}

uint64_t sol2() {
    string line;
    unordered_map<string, uint64_t> contain;
    unordered_map<string, unordered_set<string> > makes;
    while (getline(cin, line)) {
        sregex_token_iterator iter(line.begin(), line.end(), contains, -1);
        string bag = *iter, bags = *(++iter);
        string bag_name = split(bag, regex("\\sbag")).front();
        if (bags == no_others) {
            contain.emplace(bag_name, 0);
            continue;
        }
        auto quantities = split(bags, regex(",\\s"));
        unordered_set<string> can_make;
        for (string q : quantities) {
            string name = split(q, regex("\\sbag")).front();
            can_make.emplace(name);
        }
        makes.emplace(bag_name, can_make);
    }

    return must_contain(gold, makes, contain);
}

int main() {
    cout << sol2() << endl;
}