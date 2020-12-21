#include <string>
#include <iostream>
#include <regex>
#include <utils.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void solution() {
    uint64_t res = 0;
    string line, list = "";
    unordered_map<string, int> nb_present;
    unordered_map<string, unordered_set<string> > allergen_to_ingredients;
    unordered_set<string> ingredient_match, all_allergens;
    unordered_map<string, string> allergen_to_ingredient;
    while (getline(cin, line)) {
        line = line.substr(0, line.size() - 1);
        const auto sp = split(line, regex("\\s\\(contains\\s"));
        const auto ingredients = split(sp.front(), ' ');
        const auto allergens = split(sp.back(), regex(",\\s"));
        for (const auto& allergen : allergens) {
            if (allergen_to_ingredients.count(allergen) && allergen_to_ingredients.at(allergen).size() == 1) {
                continue;
            }
            all_allergens.emplace(allergen);
            unordered_set<string> new_al, current;
            bool has_map = allergen_to_ingredients.count(allergen);
            if (has_map) {
                current = allergen_to_ingredients.at(allergen);
            }
            for (const auto& ingredient : ingredients) {
                if (!ingredient_match.count(ingredient) && (!has_map || current.count(ingredient))) {
                    new_al.emplace(ingredient);
                }
            }
            if (new_al.size() == 1) {
                const string& match = *(new_al.begin());
                ingredient_match.emplace(match);
                allergen_to_ingredient[allergen] = match;
            }
            allergen_to_ingredients[allergen] =  new_al;
        }
        for (const auto& ingredient : ingredients) {
            nb_present[ingredient]++;
        }
    }
    while (allergen_to_ingredients.size()) {
        unordered_map<string, unordered_set<string> > new_map;
        for (const auto& mapping : allergen_to_ingredients) {
            if (mapping.second.size() == 1) {
                const string& match = *(mapping.second.begin());
                ingredient_match.emplace(match);
                allergen_to_ingredient[mapping.first] = match;
            } else {
                unordered_set<string> new_al;
                for (const auto& ingredient : mapping.second) {
                    if (!ingredient_match.count(ingredient)) {
                        new_al.emplace(ingredient);
                    }
                }
                new_map.emplace(mapping.first, new_al);
            }
        }
        allergen_to_ingredients = new_map;
    }

    for (const auto& cnt : nb_present) {
        if (!ingredient_match.count(cnt.first)) {
            res += cnt.second;
        }
    }
    cout << res << endl;

    vector<string> allergen_names(all_allergens.begin(), all_allergens.end());
    sort(allergen_names.begin(), allergen_names.end());
    for (const auto& name : allergen_names) {
        list += allergen_to_ingredient[name] + ',';
    }
    cout << list.substr(0, list.size() - 1) << endl;
}

int main() {
    solution();
}