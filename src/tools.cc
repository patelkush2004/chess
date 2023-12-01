#include "tools.h"
#include <random>

int randomGenerator(int x, int y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(x, y);

    return distribution(gen);
}