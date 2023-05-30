//g++ ve_21018_Q1.cpp warrior-class.cpp -o main

#include <algorithm>
#include <cstdlib>
#include "warrior-class.h"

int main() {
    
    
    Soldado* arrSoldier[2] = {new Mago(20, 5, "bigger"), new Mago(10, 10, "eber")};

    arrSoldier[0]->imprimirStatus();
    arrSoldier[1]->imprimirStatus();
    arrSoldier[0]->atacar(*(arrSoldier[1]));
    arrSoldier[0]->imprimirStatus();
    arrSoldier[1]->imprimirStatus();





    // Soldado* soldados[22];
    // bool finish = 0;
    // int cnt =22;
    // int iterations = 20;
    // while(iterations--){
    //     soldados[0] = new Mago(300,50,"gandolf");
    //     soldados[1] = new Sauron(100,10,"sauron");
    //     for(int i=2;i<12;i++){
    //         soldados[i] = new Orc(100,10,"orc");
    //     }
    //     for(int i=12;i<17;i++){
    //         soldados[i] = new Anao(100,10,"Anao");
    //     }
    //     for(int i=17;i<22;i++){
    //         soldados[i] = new Humano(100,10,"Humano");
    //     }
    //     finish = 0;
    //     cnt = 22;
    //     while (!finish){
    //         if(cnt == 1){
    //             cout << soldados[0]->getNome() << "\n";
    //             finish = 1;
    //         }
    //         soldados[RNG() % cnt]->atacar(*soldados[RNG() % cnt]);
    //         for(int i=0;i<cnt;i++){
    //             if(soldados[i]->getSaude() == (double)0){
    //                 Soldado* temp = soldados[i];
    //                 cnt--;
    //                 soldados[i] = soldados[cnt];
    //                 soldados[cnt] = temp;
    //             }
    //             //cout << soldados[i]->getNome() << "/" << soldados[i]->getSaude() << " ";
    //         }
    //         //cout << "\n";
    //     }
    //     for(int i=0;i<22;i++){
    //         delete soldados[i];
    //     }
    // }

    return 0;
}