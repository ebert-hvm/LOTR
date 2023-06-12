//g++ ve_21018_Q1.cpp warrior-class.cpp -o main

#include <algorithm>
#include <cstdlib>
#include "soldado.hpp"

int main() {
    Soldado* arrSoldier[3] = {new Mago(300, 50, "bigger", 25, 20), new Mago(250, 100, "eber", 35, 30), new Elfo(500, 40, "bixer", 50, 20)};

    arrSoldier[0]->imprimirStatus();
    arrSoldier[1]->imprimirStatus();
    arrSoldier[0]->atacar(*(arrSoldier[1]));
    arrSoldier[0]->imprimirStatus();
    arrSoldier[1]->imprimirStatus();

    // cout << arrSoldier[2]->getCritChance();


    return 0;
}