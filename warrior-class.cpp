#include "warrior-class.h"

std::mt19937 RNG{std::random_device{}()};

// Soldado
Soldado::Soldado(double saude, double poderDeAtaque, std::string nome) : saude(saude), poderDeAtaque(poderDeAtaque), nome(nome) {}
int Soldado::getPoderdeAtaque() { return poderDeAtaque; }
int Soldado::getSaude() { return saude; }
std::string Soldado::getNome() { return nome; }
void Soldado::setPoderdeAtaque(int poderDeAtaque) { this->poderDeAtaque = poderDeAtaque; }
void Soldado::setSaude(double saude) { this->saude = saude; }
void Soldado::defender(double dano) { saude = std::max((double)0, saude - dano); }
void Soldado::atacar(Soldado& inimigo) { inimigo.defender(poderDeAtaque); }
void Soldado::imprimirStatus() {
    std::cout << getNome() << ":\n";
    std::cout << "saude: " << getSaude() << "\n";
    std::cout << "poder de ataque: " << getPoderdeAtaque() << "\n\n";
}

// Elfo
Elfo::Elfo(double saude, double poderDeAtaque, std::string nome) : Soldado(saude, 1 + poderDeAtaque, nome) {}

// Anao
Anao::Anao(double saude, double poderDeAtaque, std::string nome) : Soldado(saude, poderDeAtaque, nome) {}
void Anao::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random > 40)
        inimigo.defender(20 + poderDeAtaque);
    else
        inimigo.defender(0);
}

// Humano
Humano::Humano(double saude, double poderDeAtaque, std::string nome) : Soldado(saude, poderDeAtaque, nome) {}
void Humano::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    inimigo.defender(poderDeAtaque);
    if (random < 10) inimigo.defender(poderDeAtaque);
}

// Sauron
Sauron::Sauron(double saude, double poderDeAtaque, std::string nome) : Soldado(10 * saude, poderDeAtaque, nome) {}
void Sauron::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 30)
        inimigo.defender(2 * poderDeAtaque);
    else
        inimigo.defender(poderDeAtaque);
}

// Orc
Orc::Orc(double saude, double poderDeAtaque, std::string nome) : Soldado(saude, poderDeAtaque, nome) {}
void Orc::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 20) {
        inimigo.defender(1.1 * poderDeAtaque);
        inimigo.defender(1.1 * poderDeAtaque);
    } else
        inimigo.defender(poderDeAtaque);
}

// Mago
Mago::Mago(double saude, double poderDeAtaque, std::string nome) : Soldado(saude, poderDeAtaque, nome) {}
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
