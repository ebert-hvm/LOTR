#include "combate.hpp"


Combate::Combate() : aliados(){
    for(int i=0;i<hordaSize;i++){
        hordas.push_back(make_unique<Horda>(static_cast<HordaIndex>(i)));
    }
    //hordas[0]->proximoSoldado()->imprimirStatus();
    //aliados.proximoSoldado()->imprimirStatus();
}

bool Combate::executarRodada(){
    vector<shared_ptr<Soldado>> aliadosRestantes, inimigosRestantes;
    if(!(aliados.checarProximoSoldado()) or !(hordas[0]->checarProximoSoldado())) return false;
    shared_ptr<Soldado> aliado, inimigo;
    while(aliados.checarProximoSoldado() and hordas[0]->checarProximoSoldado()){
        aliado = aliados.proximoSoldado();
        inimigo = hordas[0]->proximoSoldado();
        cout << aliado->getNome() << " x " << inimigo->getNome() << "\n";
        aliado->atacar(*inimigo);
        if(inimigo->vivo()){
            inimigo->atacar(*aliado);
            inimigosRestantes.push_back(inimigo);
        }
        if(aliado->vivo())
            aliadosRestantes.push_back(aliado);
    }
    aliados.randomEnqueue(aliadosRestantes);
    hordas[0]->randomEnqueue(inimigosRestantes);
    aliados.print();
    cout << "\n";
    hordas[0]->print();
    return true;
}