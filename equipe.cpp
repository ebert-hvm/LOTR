#include "equipe.hpp"

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

Horda::Horda(HordaIndex index) {
    switch (index) {
        case primeira:
            for (int i = 0; i < 10; i++) {
                string nome = "Orc" + to_string(i + 1);
                double saude = 100.0;
                double poderDeAtaque = 10.0;
                soldados.push_back(make_shared<Anao>(saude, poderDeAtaque, nome));
            }
            break;
        case segunda:
            for (int i = 0; i < 5; i++) {
                string nome = "Orc picudo" + to_string(i + 1);
                double saude = 100.0;
                double poderDeAtaque = 10.0;
                soldados.push_back(make_shared<Elfo>(saude, poderDeAtaque, nome));
            }
            break;
        case chefao:
            for (int i = 0; i < 5; i++) {
                std::string nome = "Orc" + std::to_string(i + 1);
                double saude = 100.0;
                double poderDeAtaque = 10.0;
                soldados.push_back(make_shared<Anao>(saude, poderDeAtaque, nome));
            }
            for (int i = 0; i < 5; i++) {
                std::string nome = "Orc picudo" + std::to_string(i + 1);
                double saude = 100.0;
                double poderDeAtaque = 10.0;
                soldados.push_back(make_shared<Elfo>(saude, poderDeAtaque, nome));
            }
            break;
        default:
            throw("Indice inválido!");
            break;
    }
    randomEnqueue(soldados);
}

int choiceHandler(int optionsNumber) {
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

void Aliados::montarEquipe() {
    cout << "Monte sua equipe! \n\n";
    cout << "Primeiro escolha seu mago:\n1 - Ebo\n2 - Biggers\n";
    switch (choiceHandler(2)) {
        case 1:
            soldados.push_back(make_shared<Elfo>(100, 100, "Ebo"));
            break;
        case 2:
            soldados.push_back(make_shared<Anao>(100, 100, "Biggers"));
            break;
        default:
            throw("Escolha inválida");
            break;
    }
    cout << "O resto vai ser anao, toma!\n";
    for (int i = 0; i < 2; i++) {
        string nome = "anao " + to_string(i);
        soldados.push_back(make_shared<Anao>(100, 15, nome));
    }
}

Aliados::Aliados() {
    montarEquipe();
    randomEnqueue(soldados);
}