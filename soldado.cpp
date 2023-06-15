#include "soldado.hpp"

mt19937 RNG{random_device{}()};
normal_distribution<double> NDist(1, 0.1);

// Soldado
Soldado::Soldado(double HP, double ATK, std::string N, int AGI, int ARM, int CRIT) : saude(HP), poderDeAtaque(ATK), nome(N), agility(AGI), armor(ARM), critChance(CRIT) {}
int Soldado::getPoderdeAtaque() { return poderDeAtaque; }
int Soldado::getSaude() { return saude; }
string Soldado::getNome() { return nome; }
int Soldado::getAgilidade() { return agility; }
int Soldado::getArmadura() { return armor; }
int Soldado::getCritChance() { return critChance; }

void Soldado::setPoderdeAtaque(int ATK) { this->poderDeAtaque = ATK; }
void Soldado::setSaude(double HP) { this->saude = HP; }
void Soldado::setAgilidade(int AGI) { this->agility = AGI; }
void Soldado::setArmadura(int ARM) { this->armor = ARM; }
void Soldado::setCritChance(int CRIT) { this->critChance = CRIT; }

bool Soldado::vivo() { return saude > 0; }

void Soldado::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>> aliadosTeam, vector<shared_ptr<Soldado>> inimigosTeam) {
    atacar(inimigo);
    return;
}
void Soldado::atacar(Soldado& inimigo) { atacar(inimigo, poderDeAtaque); }
void Soldado::atacar(Soldado& inimigo, double ATK) {
    ATK = ATK * NDist(RNG);
    int random = RNG() % 100;
    if (random < critChance) {
        inimigo.defender(2 * ATK);
    } else
        inimigo.defender(ATK);
}
void Soldado::defender(double dano) {
    if ((double)RNG() / RNG.max() < agility_dodge_probability(agility)) {
        return;
    }
    if ((double)RNG() / RNG.max() < armor_defend_probability(armor)) {
        double dmg = max((double)0, dano - armor);
        saude = max((double)0, saude - dmg);
    } else {
        saude = max((double)0, saude - dano);
    }
}
void Soldado::imprimirStatus() {
    string nome = getNome();
    nome.resize(15, ' ');
    cout << nome << " | ";
    cout << "hp: " << getSaude() << " | ";
    cout << "atk: " << getPoderdeAtaque() << "\n";
}

// Elfo
Elfo::Elfo(double HP, double ATK, string N, int AGI, int ARM, int CRIT) : Soldado(HP, ATK + 10, N, AGI + 30, ARM - 10, CRIT) {}

// Anao
Anao::Anao(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK - 10, N, AGI - 20, ARM + 25) {}
void Anao::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random > 40)
        Soldado::atacar(inimigo, 20 + poderDeAtaque);
    else
        Soldado::atacar(inimigo, 0);
}

// Humano
Humano::Humano(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK, N, AGI, ARM) {}
void Humano::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    Soldado::atacar(inimigo, poderDeAtaque);
    if (random < 10) Soldado::atacar(inimigo, poderDeAtaque);
}

// Sauron
Sauron::Sauron(double HP, double ATK, string N, int AGI, int ARM) : Soldado(10 * HP, ATK, N, AGI, ARM) {}
void Sauron::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 30)
        Soldado::atacar(inimigo, 2 * poderDeAtaque);
    else
        Soldado::atacar(inimigo, poderDeAtaque);
}

// Orc
Orc::Orc(double HP, double ATK, std::string N, int AGI, int ARM) : Soldado(HP + 60, ATK, N, AGI - 20, ARM + 20) {}
void Orc::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 20) {
        Soldado::atacar(inimigo, 1.1 * poderDeAtaque);
        Soldado::atacar(inimigo, 1.1 * poderDeAtaque);
    } else
        Soldado::atacar(inimigo, poderDeAtaque);
}

// Mago
Mago::Mago(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP - 100, ATK + 25, N, AGI + 10, ARM - 10) {}
void Mago::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 10) {
        Soldado::atacar(inimigo, 2 * poderDeAtaque);
    } else if (random < 70) {
        Soldado::atacar(inimigo, poderDeAtaque);
    } else {
        setPoderdeAtaque(2 * poderDeAtaque);
        setSaude(100 + saude);
    }
}