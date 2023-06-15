#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <random>
#include <vector>

using namespace std;
mt19937 RNG{random_device{}()};
normal_distribution<double> NDist(1, 0.1);

double armor_defend_probability(int armor) {
    return 0.5 * std::atan((double)armor / 50);
}

double agility_dodge_probability(int agility) {
    return 0.25 * std::atan((double)agility / 30) * std::atan((double)agility / 30);
}

int main() {
    int n = 100;
    while (n--) {
        cout << NDist(RNG) << "\n";
    }
    // cout << (double)RNG() / RNG.max();
}