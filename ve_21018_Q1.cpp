//g++ ve_21018_Q1.cpp warrior-class.cpp -o main

#include <algorithm>
#include <cstdlib>
#include "soldado.hpp"

int main() {
    Soldado* arrSoldier[2] = {new Mago(300, 50, "bigger", 25, 20), new Mago(250, 100, "eber", 35, 30)};

    arrSoldier[0]->imprimirStatus();
    arrSoldier[1]->imprimirStatus();
    arrSoldier[0]->atacar(*(arrSoldier[1]));
    arrSoldier[0]->imprimirStatus();
    arrSoldier[1]->imprimirStatus();




    return 0;
}