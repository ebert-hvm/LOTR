#include "combate.hpp"

int main(){
    int option = 1;
    while(option){
        cout << "Menu:\n1 - Jogar\n2 - Sair\n";
        option = choiceHandler(2);
        if(option == 2) break;
        Combate combate;
        if(combate.iniciar()){
            cout << "Vitória\n"; 
        }
        else{
            cout << "Fim de Jogo\n";
        }
        getchar();
    }
}