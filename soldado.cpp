#include "soldado.hpp"

mt19937 RNG{random_device{}()};

// Soldado
Soldado::Soldado(double saude, double poderDeAtaque, string nome) : saude(saude), poderDeAtaque(poderDeAtaque), nome(nome) {}
int Soldado::getPoderdeAtaque() { return poderDeAtaque; }
int Soldado::getSaude() { return saude; }
string Soldado::getNome() { return nome; }
void Soldado::setPoderdeAtaque(int poderDeAtaque) { this->poderDeAtaque = poderDeAtaque; }
void Soldado::setSaude(double saude) { this->saude = saude; }
bool Soldado::vivo() {return saude > 0; }
void Soldado::defender(double dano) { saude = max((double)0, saude - dano); }
void Soldado::atacar(Soldado& inimigo) { inimigo.defender(poderDeAtaque); }
void Soldado::imprimirStatus() {
    string nome = getNome();
    nome.resize(15, ' ');
    cout << nome << " | ";
    cout << "hp: " << getSaude() << " | ";
    cout << "atk: " << getPoderdeAtaque() << "\n";
}

// Elfo
Elfo::Elfo(double saude, double poderDeAtaque, string nome) : Soldado(saude, 1 + poderDeAtaque, nome) {}

// Anao
Anao::Anao(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
void Anao::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random > 40)
        inimigo.defender(20 + poderDeAtaque);
    else
        inimigo.defender(0);
}

// Humano
Humano::Humano(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
void Humano::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    inimigo.defender(poderDeAtaque);
    if (random < 10) inimigo.defender(poderDeAtaque);
}

// Sauron
Sauron::Sauron(double saude, double poderDeAtaque, string nome) : Soldado(10 * saude, poderDeAtaque, nome) {}
void Sauron::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 30)
        inimigo.defender(2 * poderDeAtaque);
    else
        inimigo.defender(poderDeAtaque);
}

// Orc
Orc::Orc(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
void Orc::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 20) {
        inimigo.defender(1.1 * poderDeAtaque);
        inimigo.defender(1.1 * poderDeAtaque);
    } else
        inimigo.defender(poderDeAtaque);
}

// Mago
Mago::Mago(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
void Mago::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 70) {
        inimigo.defender(poderDeAtaque);
    } else {
        // inimigo.defender(poderDeAtaque);
        setPoderdeAtaque(2 * poderDeAtaque);
        setSaude(100 + saude);
    }
}
