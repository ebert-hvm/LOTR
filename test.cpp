#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>
#include <queue>

using namespace std;

int choiceHandler(int optionsNumber) {
    int choice;
    while (1) {
        if (!(cin >> choice) or choice <= 0 or choice > optionsNumber) {
            cout << "Escolha Inválida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else
            return choice;
    }
}

int main() {
    int a = 2;
    if(0 and (a=1)) cout << a;
}