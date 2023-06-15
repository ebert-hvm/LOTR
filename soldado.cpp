#include "soldado.hpp"

mt19937 RNG{random_device{}()};
normal_distribution<double> NDist(1, 0.1);

// Soldado
Soldado::Soldado(double HP, double ATK, std::string N, int AGI, int ARM, int CRIT) : saude(HP), maxHP(HP), poderDeAtaque(ATK), nome(N), agility(AGI), armor(ARM), critChance(CRIT) {}
double Soldado::getPoderdeAtaque() { return poderDeAtaque; }
double Soldado::getSaude() { return saude; }
double Soldado::getMaxHP() { return maxHP; }
string Soldado::getNome() { return nome; }
int Soldado::getAgilidade() { return agility; }
int Soldado::getArmadura() { return armor; }
int Soldado::getCritChance() { return critChance; }
bool Soldado::vivo() { return saude > 0; }

void Soldado::setPoderdeAtaque(int ATK) { this->poderDeAtaque = ATK; }
void Soldado::setSaude(double HP) { this->saude = HP; }
void Soldado::setMaxHP(double HP) { this->maxHP = HP; }
void Soldado::setAgilidade(int AGI) { this->agility = AGI; }
void Soldado::setArmadura(int ARM) { this->armor = ARM; }
void Soldado::setCritChance(int CRIT) { this->critChance = CRIT; }

void Soldado::executarAcao(Soldado& inimigo) {
    vector<shared_ptr<Soldado>> empty_vec;
    executarAcao(inimigo, empty_vec, empty_vec);
}
void Soldado::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>> aliadosTeam, vector<shared_ptr<Soldado>> inimigosTeam) {
    if(!vivo()) return;
    atacar(inimigo);
}
void Soldado::atacar(Soldado& inimigo) { atacar(inimigo, poderDeAtaque); }
void Soldado::atacar(Soldado& inimigo, double ATK) {
    ATK = ATK * NDist(RNG);
    int random = RNG() % 100;
    if (random < critChance) {
        cout << fixed << setprecision(2) << "CRIT!  Dano do ataque: " << 2 * ATK << "\n";
        inimigo.defender(2 * ATK);
    } else {
        cout << fixed << setprecision(2) << "Dano do ataque: " << ATK << "\n";
        inimigo.defender(ATK);
    }
}
void Soldado::defender(double dano) {
    if ((double)RNG() / RNG.max() < agility_dodge_probability(agility)) {
        cout << "Ataque esquivado!\n";
        return;
    }
    dano = dano * (1 - armor_defend_percentage(armor));
    saude = max((double)0, saude - (dano));
    cout << fixed << setprecision(2) << "Dano reduzido em " << (int)(armor_defend_percentage(armor) * 100) << "% pela armadura.\nDano recebido: " << dano << "\n";
}

void Soldado::imprimirStatus() {
    string nome = getNome();
    nome.resize(15, ' ');
    cout << nome << " | ";
    cout << "hp: " << getSaude() << "\n";
    //cout << "atk: " << getPoderdeAtaque() << "\n";
}

// Elfo
Elfo::Elfo(double HP, double ATK, string N, int AGI, int ARM, int CRIT) : Soldado(HP, ATK + 10, N, AGI + 30, ARM - 10, CRIT) {}
void Elfo::descricao() {
    cout << "Stats:\nATK + 10, AGI + 30\nARM - 10\nCRIT: 20%\n\n";
}

// Anao
Anao::Anao(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK - 10, N, AGI - 20, ARM + 25) {}
void Anao::atacar(Soldado& inimigo) {
    // Extra damage when low HP
    double DMG = poderDeAtaque * (1 + 0.4 * (maxHP - saude) / maxHP);

    int random = RNG() % 100;
    if (random > 40)
        Soldado::atacar(inimigo, 20 + DMG);
    else
        Soldado::atacar(inimigo, 0.5 * DMG);
}
void Anao::defender(double dano) {
    // Gain ATK when getting attacked
    setPoderdeAtaque(poderDeAtaque + 3);
    Soldado::defender(dano);
}
void Anao::descricao() {
    cout << "Stats:\nARM + 25\nATK - 10, AGI - 20\nCRIT: 5%\n\n";
    cout << "O Anao da dano extra para inimigos com pouca vida, tendo ainda chance de dar 20 de dano extra no seu ataque, porem ele regularmente faz um ataque fraco com metade do seu dano. Toda vez que o Anao é atacado, ele ganha +3 de ATK\n";
}

// Humano
Humano::Humano(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK, N, AGI, ARM) {}
void Humano::atacar(Soldado& inimigo) {
    // Deal extra damage to low HP enemies
    double DMG = poderDeAtaque * (1 + 0.6 * (inimigo.getMaxHP() - inimigo.getSaude()) / inimigo.getMaxHP());

    int random = RNG() % 100;
    Soldado::atacar(inimigo, DMG);
    if (random < 10) Soldado::atacar(inimigo, DMG);
}
void Humano::descricao(){
    cout << "Stats:\nCrit: 5%\n\n";
}

// Sauron
Sauron::Sauron(double HP, double ATK, string N, int AGI, int ARM) : Soldado(5 * HP, ATK, N, AGI, ARM) {}
void Sauron::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 20)
        Soldado::atacar(inimigo, 1.5 * poderDeAtaque);
    else if (random < 40) {
        Soldado::atacar(inimigo, poderDeAtaque / 2);
        Soldado::atacar(inimigo, poderDeAtaque / 2);
        Soldado::atacar(inimigo, poderDeAtaque / 2);
    } else {
        Soldado::atacar(inimigo, poderDeAtaque);
        setPoderdeAtaque(poderDeAtaque + 5);
    }
}
void Sauron::descricao(){
    cout << "Stats:\nHP * 5\nCrit: 5%\n\n";
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
void Orc::descricao(){
    cout << "Stats:\nHP + 60, ARM + 20\nAGI - 20\nCrit: 5%\n\n";
}

// Mago
Mago::Mago(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP - 100, ATK + 25, N, AGI + 10, ARM - 10) {}
void Mago::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>> aliados, vector<shared_ptr<Soldado>> inimigos) {
    if (saude <= 0) return;
    atacar(inimigo);
}
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
void Mago::descricao(){
    cout << "Stats:\nATK + 25, AGI + 10\nHP - 100, ARM - 10\nCrit: 5%\n\n";
}
