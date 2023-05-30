#include "soldado.hpp"

Soldado::Soldado(double saude, double poderDeAtaque, string nome) : saude(saude),
    poderDeAtaque(poderDeAtaque), nome(nome) {}
int Soldado::getPoderdeAtaque() {
    return poderDeAtaque;
}
int Soldado::getSaude() {
    return saude;
}
string Soldado::getNome() {
    return nome;
}

bool Soldado::vivo(){
    return saude > 0;
}

void Soldado::setPoderdeAtaque(int poderDeAtaque) {
    this->poderDeAtaque = poderDeAtaque;
}
void Soldado::setSaude(double saude) {
    this->saude = saude;
}

void Soldado::imprimirStatus() {
    string nome = getNome();
    nome.resize(10, ' ');
    cout << nome << " | ";
    cout << "hp: " << getSaude() << " | ";
    cout << "atk: " << getPoderdeAtaque() << "\n";
}

Elfo::Elfo(double saude, double poderDeAtaque, string nome) : Soldado(saude, 1 + poderDeAtaque, nome) {}
void Elfo::atacar(Soldado& inimigo) {
    inimigo.defender(getPoderdeAtaque());
}
void Elfo::defender(double poderDeAtaque){
    saude = max((double)0, saude - poderDeAtaque);
}


Anao::Anao(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
void Anao::atacar(Soldado& inimigo) {
    double random = (double)rand() / RAND_MAX;
    if (random > 0.4)
        inimigo.defender(20 + getPoderdeAtaque());
    else
        inimigo.defender(0);
}
void Anao::defender(double poderDeAtaque){
    saude = max((double)0, saude - poderDeAtaque);
}
