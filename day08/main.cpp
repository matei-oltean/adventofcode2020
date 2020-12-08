#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

bool swap(vector<pair<string, int> >& instructions, size_t i) {
    if (instructions[i].first == "nop") {
        instructions[i].first = "jmp";
        return true;
    } else if (instructions[i].first == "jmp") {
        instructions[i].first = "nop";
        return true;
    }
    return false;
}

vector<pair<string, int> > get_instructions() {
    vector<pair<string, int> > instructions;
    string line;
    while (getline(cin, line)) {
        const string& op = line.substr(0, 3), str_val = line.substr(4, string::npos);
        int val = stoi(str_val);
        instructions.emplace_back(op, val);
    }
    return instructions;
}

pair<uint64_t, bool> execute(const vector<pair<string, int> >& instructions) {
    uint64_t acc = 0;
    size_t i = 0;
    unordered_set<size_t> seen;
    while (!seen.count(i) && i < instructions.size()) {
        seen.emplace(i);
        const auto& [op, val] = instructions[i];
        if (op == "acc") {
            acc += val;
            ++i;
        } else if (op == "jmp") {
            i += val;
        } else {
            ++i;
        }
    }
    bool loops = i != instructions.size();
    return { acc, loops };
}

uint64_t sol1() {
    return execute(get_instructions()).first;
}

uint64_t sol2() {
    auto instructions = get_instructions();
    for (size_t i = 0; i < instructions.size(); ++i) {
        if (!swap(instructions, i)) {
            continue;
        }
        const auto& [acc, loops] = execute(instructions);
        if (!loops) {
            return acc;
        }
        swap(instructions, i);
    }
    return 0;
}

int main() {
    cout << sol1() << endl;
}