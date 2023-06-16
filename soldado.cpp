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
void Soldado::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliadosTeam, vector<shared_ptr<Soldado>>& inimigosTeam) {
    if (!vivo()) return;
    atacar(inimigo);
}
void Soldado::atacar(Soldado& inimigo) { atacar(inimigo, poderDeAtaque); }
void Soldado::atacar(Soldado& inimigo, double ATK) {
    if (!inimigo.vivo()) {
        cout << inimigo.getNome() << " chega ao duelo morto...\n\n";
        return;
    }
    ATK = ATK * NDist(RNG);
    int random = RNG() % 100;
    if (random < critChance) {
        cout << fixed << setprecision(2) << "CRIT!  Dano do ataque de " << nome << ": " << 2 * ATK << "\n";
        inimigo.defender(*this, 2 * ATK);
    } else {
        cout << fixed << setprecision(2) << "Dano do ataque de " << nome << ": " << ATK << "\n";
        inimigo.defender(*this, ATK);
    }
}
void Soldado::defender(double dano) {
    if ((double)RNG() / RNG.max() < agility_dodge_probability(agility)) {
        cout << nome << " esquivou do ataque!\n\n";
        return;
    }
    dano = dano * (1 - armor_defend_percentage(armor));
    saude = max((double)0, saude - (dano));
    cout << fixed << setprecision(2) << "Dano reduzido em " << (int)(armor_defend_percentage(armor) * 100) << "% pela armadura.\nDano recebido por " << nome << ": " << dano << "\n\n";
}
void Soldado::defender(Soldado& inimigo, double dano) {
    defender(dano);
}

void Soldado::imprimirStatus() {
    string nome = getNome();
    nome.resize(15, ' ');
    cout << nome << " | ";
    cout << "HP: " << fixed << setw(4) << (int)getSaude() << "/" << setw(4) << (int)getMaxHP() << " | ";
    cout << "ATK: " << (int)getPoderdeAtaque() << "\n";
}
void Soldado::descricao() { return; }

// Elfo
Elfo::Elfo(double HP, double ATK, string N, int AGI, int ARM, int CRIT) : Soldado(HP, ATK, N, AGI + 30, ARM - 25, CRIT) {}
void Elfo::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos) {
    if (!vivo()) return;
    auto lambda = [&inimigo](const shared_ptr<Soldado>& obj) { return obj->getNome() == inimigo.getNome(); };
    // Copia para nao mudar o original
    vector<shared_ptr<Soldado>> copia_de_inimigos = inimigos;
    // Removendo o inimigo atual
    shared_ptr<Soldado> ptr_inimigo = make_shared<Soldado>(inimigo);
    vector<shared_ptr<Soldado>>::iterator it = find_if(copia_de_inimigos.begin(), copia_de_inimigos.end(), lambda);
    if (it != copia_de_inimigos.end()) copia_de_inimigos.erase(it);
    // Removendo inimigos mortos
    for (it = copia_de_inimigos.begin(); it != copia_de_inimigos.end(); it++) {
        if (!(*it)->vivo()) {
            it = copia_de_inimigos.erase(it);
            it--;
        }
    }
    // Ataque no inimigo atual
    Soldado::atacar(inimigo);
    if (copia_de_inimigos.size() == 0) return;
    // Ataque no segundo inimigo aleatoria (nao morto nem o atual)
    shuffle(copia_de_inimigos.begin(), copia_de_inimigos.end(), RNG);
    Soldado::atacar(**find(inimigos.begin(), inimigos.end(), copia_de_inimigos[0]));
}
void Elfo::descricao() {
    cout << "Stats:\nAGI + 30\nARM - 25\nCRIT: 20%\n\n";
    cout << "Ataque: Alem do inimigo no duelo, acerta outro inimigo aleatoriamente, caso seja possivel\n";
}

// Anao
Anao::Anao(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK - 10, N, AGI - 20, ARM + 25) {}
void Anao::atacar(Soldado& inimigo) {
    // Extra damage when low HP
    double DMG = poderDeAtaque * (1 + 0.4 * (maxHP - saude) / maxHP);

    int random = RNG() % 100;
    if (random < 40)
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
    cout << "Ataque: Dano extra para inimigos com pouca vida. 40\% de dar 20 de dano extra no seu ataque, porem caso contrario faz um ataque fraco com metade do seu dano\n";
    cout << "Defesa: Toda vez que defende, ganha +3 ATK";
}

// Humano
Humano::Humano(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK, N, AGI, ARM) {}
void Humano::atacar(Soldado& inimigo, double ATK) {
    // Deal extra damage to low HP enemies
    double DMG = ATK * (1 + 0.6 * (inimigo.getMaxHP() - inimigo.getSaude()) / inimigo.getMaxHP());

    int random = RNG() % 100;
    Soldado::atacar(inimigo, DMG);
    if (random < 15) {
        cout << nome << " realizou um segundo ataque!\n";
        Soldado::atacar(inimigo, DMG);
    }
}
void Humano::defender(Soldado& inimigo, double dano) {
    int random = RNG() % 100;
    Soldado::defender(dano);
    if (random < 25) {
        cout << "O " << nome << " realizou um contra ataque!\n";
        Humano::atacar(inimigo, poderDeAtaque / 2);
    }
}
void Humano::descricao() {
    cout << "Stats:\nCrit: 5%\n\n";
    cout << "Ataque: 15\% de ataque duplo";
    cout << "Defesa: 25\% de contra-atacar com a metade do poder de ataque cada vez que toma dano";
}

// Sauron
Sauron::Sauron(double HP, double ATK, string N, int AGI, int ARM) : Soldado(5 * HP, ATK, N, AGI, ARM) {}
void Sauron::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos) {
    if (!vivo()) return;
    int random = RNG() % 100;
    if (random < 20) {
        cout << nome << " executa um ataque pesado!\n";
        Soldado::atacar(inimigo, 1.5 * poderDeAtaque);
    } else if (random < 40) {
        cout << nome << " executa 3 ataques leves!\n";
        Soldado::atacar(inimigo, poderDeAtaque / 2);
        Soldado::atacar(inimigo, poderDeAtaque / 2);
        Soldado::atacar(inimigo, poderDeAtaque / 2);
    } else if (random < 70 && saude / maxHP <= 0.25) {
        cout << nome << " entra em uma furia descontrolada! Ele ataca TODOS!\n";
        for (auto it = aliados.begin(); it != aliados.end(); it++) {
            if (!(*it)->vivo()) continue;
            Soldado::atacar(**it, poderDeAtaque * 0.75);
        }
        for (auto it = inimigos.begin(); it != inimigos.end(); it++) {
            if (!(*it)->vivo() || (*it)->getNome() == nome) continue;
            Soldado::atacar(**it, poderDeAtaque * 0.75);
        }
    } else {
        cout << nome << " ataca e ganha +5 ATK e recupera +25 HP!\n";
        // Ataque padrao com self buff
        Soldado::atacar(inimigo, poderDeAtaque);
        setPoderdeAtaque(poderDeAtaque + 5);
        setSaude(min(saude + 25, saude));
    }
}
void Sauron::descricao() {
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
void Orc::descricao() {
    cout << "Stats:\nHP + 60, ARM + 20\nAGI - 20\nCrit: 5%\n\n";
}

// Mago
Mago::Mago(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP - 100, ATK + 25, N, AGI + 10, ARM - 10) {}
void Mago::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos) {
    if (!vivo()) return;
    int random = RNG() % 100;
    if (random < 50) {
        cout << nome << " aplica um efeito de cura em todos os seus aliados:\n";
        for (auto it = aliados.begin(); it != aliados.end(); it++) {
            if (!(*it)->vivo()) continue;
            cout << (*it)->getNome() << " recebe AGI + 2, CRIT + 2, ATK + 5, HP + 20\n";
            (*it)->setAgilidade((*it)->getAgilidade() + 2);
            // (*it)->setArmadura((*it)->getArmadura() + 2);
            (*it)->setCritChance((*it)->getCritChance() + 2);
            (*it)->setPoderdeAtaque((*it)->getPoderdeAtaque() + 5);
            (*it)->setSaude(min((*it)->getSaude() + 20, (*it)->getMaxHP()));
        }
        cout << "\n";
    } else
        atacar(inimigo);
}
void Mago::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 20) {
        Soldado::atacar(inimigo, 2 * poderDeAtaque);
    } else if (random < 75) {
        Soldado::atacar(inimigo, poderDeAtaque);
    } else {
        setPoderdeAtaque(1.6 * poderDeAtaque);
        setSaude(min(100 + saude, saude));
    }
}
void Mago::descricao() {
    cout << "Stats:\nATK + 25, AGI + 10\nHP - 100, ARM - 10\nCrit: 5%\n\n";
}
