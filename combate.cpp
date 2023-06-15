#include "combate.hpp"


Combate::Combate() : aliados(), horda_atual(0){
    for(int i=0;i<Horda::size();i++){
        hordas.push_back(make_unique<Horda>(i));
    }
    //->proximoSoldado()->imprimirStatus();
    //aliados.proximoSoldado()->imprimirStatus();
}

int Combate::executarRodada(int rodada){
    vector<shared_ptr<Soldado>> aliadosRestantes, inimigosRestantes;
    shared_ptr<Soldado> aliado, inimigo;
    while(aliados.checarProximoSoldado() and hordas[horda_atual]->checarProximoSoldado()){
        system("clear");
        cout << "Horda " << horda_atual + 1 << "\n";
        cout << "Rodada " << rodada << "\n\n";
        aliado = aliados.proximoSoldado();
        inimigo = hordas[horda_atual]->proximoSoldado();
        cout << aliado->getNome() << " x " << inimigo->getNome() << "\n\n";

        if(aliado->getAgilidade() > inimigo->getAgilidade()){
            aliado->executarAcao(*inimigo, aliados.getSoldados(), hordas[horda_atual]->getSoldados());
            inimigo->executarAcao(*aliado, aliados.getSoldados(), hordas[horda_atual]->getSoldados());
        }
        else{
            inimigo->executarAcao(*aliado, aliados.getSoldados(), hordas[horda_atual]->getSoldados());
            aliado->executarAcao(*inimigo, aliados.getSoldados(), hordas[horda_atual]->getSoldados());
        }
        if (aliado->vivo()) aliadosRestantes.push_back(aliado);
        if (inimigo->vivo()) inimigosRestantes.push_back(inimigo);

        aliado->imprimirStatus();
        inimigo->imprimirStatus();
        cout << "\nContinuar...";
        cin.get();
    }
    aliados.randomEnqueue(aliadosRestantes);
    hordas[horda_atual]->randomEnqueue(inimigosRestantes);
    // Printar status apos os duelos
    system("clear");
    cout << "Horda " << horda_atual + 1 << "\n";
    cout << "Rodada " << rodada + 1 << "\n\n";
    cout << "Resumo da rodada:\n";
    aliados.print();
    cout << "\n";
    hordas[horda_atual]->print();
    cout << "\nContinuar...";
    cin.get();

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
        int res = 0, index = 1;
        while(res == 0){
            res = executarRodada(index);
            index++;
        }
        if(res == -1) return false;
        horda_atual++;
    }
    horda_atual = 0;
    return true;
}