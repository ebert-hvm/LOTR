#include "warrior-class.hpp"

std::mt19937 RNG{std::random_device{}()};

// Soldado
Soldado::Soldado(double HP, double ATK, std::string N, int AGI, int ARM) : saude(HP), poderDeAtaque(ATK), nome(N), agility(AGI), armor(ARM) {}
int Soldado::getPoderdeAtaque() { return poderDeAtaque; }
int Soldado::getSaude() { return saude; }
std::string Soldado::getNome() { return nome; }
void Soldado::setPoderdeAtaque(int poderDeAtaque) { this->poderDeAtaque = poderDeAtaque; }
void Soldado::setSaude(double saude) { this->saude = saude; }
void Soldado::atacar(Soldado& inimigo) { inimigo.defender(poderDeAtaque); }
void Soldado::defender(double dano) {
    if ((double)RNG() / RNG.max() < agility_dodge_probability(agility)) {
        return;
    }
    if ((double)RNG() / RNG.max() < armor_defend_probability(armor)) {
        double dmg = std::max((double)0, dano - armor);
        saude = std::max((double)0, saude - dmg);
    } else {
        std::cout << "normal";
        saude = std::max((double)0, saude - dano);
    }
}
void Soldado::imprimirStatus() {
    std::cout << getNome() << ":\n";
    std::cout << "saude: " << getSaude() << "\n";
    std::cout << "poder de ataque: " << getPoderdeAtaque() << "\n\n";
}

// Elfo
Elfo::Elfo(double HP, double ATK, std::string N, int AGI, int ARM) : Soldado(HP, ATK + 10, N, AGI + 30, ARM - 10) {}

// Anao
Anao::Anao(double HP, double ATK, std::string N, int AGI, int ARM) : Soldado(HP, ATK - 10, N, AGI - 20, ARM + 25) {}
void Anao::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random > 40)
        inimigo.defender(30 + poderDeAtaque);
    else
        inimigo.defender(0);
}

// Humano
Humano::Humano(double HP, double ATK, std::string N, int AGI, int ARM) : Soldado(HP, ATK, N, AGI, ARM) {}
void Humano::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    inimigo.defender(poderDeAtaque);
    if (random < 10) inimigo.defender(poderDeAtaque);
}

// Sauron
Sauron::Sauron(double HP, double ATK, std::string N, int AGI, int ARM) : Soldado(10 * HP, ATK, N, AGI, ARM) {}
void Sauron::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 30)
        inimigo.defender(2 * poderDeAtaque);
    else
        inimigo.defender(poderDeAtaque);
}

// Orc
Orc::Orc(double HP, double ATK, std::string N, int AGI, int ARM) : Soldado(HP + 60, ATK, N, AGI - 20, ARM + 20) {}
void Orc::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 20) {
        inimigo.defender(1.1 * poderDeAtaque);
        inimigo.defender(1.1 * poderDeAtaque);
    } else
        inimigo.defender(poderDeAtaque);
}

// Mago
Mago::Mago(double HP, double ATK, std::string N, int AGI, int ARM) : Soldado(HP - 100, ATK + 25, N, AGI + 10, ARM - 10) {}
void Mago::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 10) {
        inimigo.defender(2 * poderDeAtaque);
    } else if (random < 70) {
        inimigo.defender(poderDeAtaque);
    } else {
        setPoderdeAtaque(2 * poderDeAtaque);
        setSaude(100 + saude);
    }
}
