#include <iostream>

uint64_t key_1 = 6929599;
uint64_t key_2 = 2448427;

uint64_t transform(uint64_t subject, uint64_t loop_size) {
    uint64_t res = 1;
    for (uint64_t i = 0; i < loop_size; ++i) {
        res = (res * subject) % 20201227;
    }
    return res;
}

size_t find_loop(uint64_t subject, uint64_t target) {
    uint64_t i = 0, res = 1;
    for (; target != res; ++i) {
        res = (res * subject) % 20201227;
    }
    return i;
}

uint64_t sol1() {
    uint64_t loop_1 = find_loop(7, key_1);
    return transform(key_2, loop_1);
}

int main() {
    std::cout << sol1() << std::endl;
}