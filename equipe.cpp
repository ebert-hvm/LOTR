#include "equipe.hpp"

//EQUIPE
void Equipe::randomEnqueue(vector<shared_ptr<Soldado>> soldadosVivos) {
    vector<int> permutation(soldadosVivos.size());
    iota(permutation.begin(), permutation.end(), 0);
    random_device rd;
    mt19937 rng(rd());
    shuffle(permutation.begin(), permutation.end(), rng);
    for (auto index : permutation) {
        fila.push(soldadosVivos[index]);
    }
    /*queue<shared_ptr<Soldado>> debug;
    while(!fila.empty()){
        shared_ptr<Soldado> ptr = fila.front();
        debug.push(ptr);
        fila.pop();
        ptr->imprimirStatus();
    }
    fila = debug;*/
}

bool Equipe::checarProximoSoldado() {
    return !fila.empty();
}

shared_ptr<Soldado> Equipe::proximoSoldado() {
    if (!fila.empty()) {
        shared_ptr<Soldado> ptr = fila.front();
        fila.pop();
        return ptr;
    } else
        return nullptr;
}

void Equipe::print() {
    for (const auto& el : soldados) {
        el->imprimirStatus();
    }
}

vector<shared_ptr<Soldado>>& Equipe::getSoldados(){
    return soldados;
};

// HORDA
Horda::Horda(int index) {
    switch (index) {
        case 0:
            for (int i = 0; i < 10; i++) {
                string nome = "Orc" + to_string(i + 1);
                double saude = 100.0;
                double poderDeAtaque = 10.0;
                soldados.push_back(make_shared<Orc>(saude, poderDeAtaque, nome, 10, 10));
            }
            break;
        case 1:
            for(int i=0;i<5;i++){
                string nome = "Orc picudo" + to_string(i+1);
                double saude = 150.0;
                double poderDeAtaque = 20.0;
                soldados.push_back(make_shared<Orc>(saude, poderDeAtaque, nome, 35, 40));
            }
            break;
        case 2:
            for(int i=0;i<5;i++){
                std::string nome = "Orc picudo" + to_string(i+1);
                soldados.push_back(make_shared<Orc>(150, 20, nome, 35, 40));
            }
            soldados.push_back(make_shared<Sauron>(400, 50, "Duarte", 10, 70));
            break;
        default:
            throw("Indice inválido!");
            break;
    }
    randomEnqueue(soldados);
}

int Horda::size(){
    return 3;
}

//ALIADOS
void Aliados::montarEquipe(){
    cout << "Monte sua equipe! \n\n";
    cout << "Primeiro escolha seu mago:\n1 - Ebo\n2 - Biggers\n";
    switch(choiceHandler(2)){
        case 1:
            soldados.push_back(make_shared<Mago>(500, 100, "Ebo", 30, 40));
            break;
        case 2:
            soldados.push_back(make_shared<Mago>(500,100,"Biggers", 30, 40));
            break;
        default:
            throw("Escolha inválida");
            break;
    }
    //soldados.push_back(make_shared<Hobbit>(150,20,"Ebo", 90, 30));
    //soldados.push_back(make_shared<Hobbit>(150,20,"Biggers", 90, 30));
    //soldados.push_back(make_shared<Hobbit>(150,20,"Gandalf", 90, 30));
    soldados.push_back(make_shared<Elfo>(300,30,"Legolas", 80, 20));
    soldados.push_back(make_shared<Elfo>(300,30,"Elrond", 80, 20));
    soldados.push_back(make_shared<Anao>(500,40,"Gimli", 20, 60));
    soldados.push_back(make_shared<Humano>(200,30,"Aragorn", 50, 40));
    soldados.push_back(make_shared<Humano>(250,25,"Boromir", 40, 45));
    //soldados.push_back(make_shared<Hobbit>(150,20,"Frodo", 90, 30));
    //soldados.push_back(make_shared<Hobbit>(150,15,"Sam", 80, 40));
    //soldados.push_back(make_shared<Hobbit>(180,30,"Bilbo", 50, 40));
}

Aliados::Aliados(){
    montarEquipe();
    randomEnqueue(soldados);
}

int choiceHandler(int optionsNumber){
    int choice;
    while (1) {
        if (!(cin >> choice) || choice <= 0 || choice > optionsNumber) {
            cout << "Escolha Inválida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else
            return choice;
    }
}