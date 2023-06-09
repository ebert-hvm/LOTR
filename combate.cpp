#include "combate.hpp"


Combate::Combate() : aliados(), horda_atual(0){
    for(int i=0;i<Horda::size();i++){
        hordas.push_back(make_unique<Horda>(i));
    }
    //->proximoSoldado()->imprimirStatus();
    //aliados.proximoSoldado()->imprimirStatus();
}

int Combate::executarRodada(){
    vector<shared_ptr<Soldado>> aliadosRestantes, inimigosRestantes;
    shared_ptr<Soldado> aliado, inimigo;
    while(aliados.checarProximoSoldado() and hordas[horda_atual]->checarProximoSoldado()){
        aliado = aliados.proximoSoldado();
        inimigo = hordas[horda_atual]->proximoSoldado();
        cout << aliado->getNome() << " x " << inimigo->getNome() << "\n";
        aliado->atacar(*inimigo);
        if (inimigo->vivo()) {
            inimigo->atacar(*aliado);
            inimigosRestantes.push_back(inimigo);
        }
        if (aliado->vivo())
            aliadosRestantes.push_back(aliado);
    }
    aliados.randomEnqueue(aliadosRestantes);
    hordas[horda_atual]->randomEnqueue(inimigosRestantes);
    aliados.print();
    cout << "\n";
    hordas[horda_atual]->print();
    if(!(aliados.checarProximoSoldado()))
        return -1; // vitoria inimigo
    if(!(hordas[horda_atual]->checarProximoSoldado()))
        return 1; // vitoria aliada
    return 0; // nao acabou a rodada
}

bool Combate::iniciar(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(horda_atual < Horda::size()){
        int res = 0;
        cout << "Rodada " << horda_atual+1 << ":\n";
        while(res == 0){
            res = executarRodada();
            cout << "\nContinuar...";
            cin.get();
        }
        if(res == -1) return false;
        cout << "Fim da rodada\n";
        cin.get();
        horda_atual++;
    }
    horda_atual = 0;
    return true;
}