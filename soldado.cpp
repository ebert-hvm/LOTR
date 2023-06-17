#include "soldado.hpp"

mt19937 RNG{random_device{}()};
normal_distribution<double> NDist(1, 0.1);

// Soldado
Soldado::Soldado(double HP, double ATK, std::string N, int AGI, int DEF, int CRIT) : saude(HP), maxHP(HP), poderDeAtaque(ATK), nome(N), agility(AGI), armor(DEF), critChance(CRIT) {}
double Soldado::agility_dodge_probability(int agility) {
    if (agility > 0) return 0.27 * atan((double)agility / 30) * atan((double)agility / 30);
    return 0;
}
double Soldado::armor_defend_percentage(int armor) {
    if (armor > 0) return 0.5 * atan((double)armor / 50);
    return 0;
}

double Soldado::getPoderdeAtaque() { return poderDeAtaque; }
double Soldado::getSaude() { return saude; }
double Soldado::getMaxHP() { return maxHP; }
string Soldado::getNome() { return nome; }
int Soldado::getAgilidade() { return agility; }
int Soldado::getArmadura() { return armor; }
int Soldado::getCritChance() { return critChance; }
string Soldado::getRaca(){return raca;}
bool Soldado::vivo() { return saude > 0; }

void Soldado::setPoderdeAtaque(int ATK) { this->poderDeAtaque = ATK; }
void Soldado::setSaude(double HP) { this->saude = HP; }
void Soldado::setMaxHP(double HP) { this->maxHP = HP; }
void Soldado::setAgilidade(int AGI) { this->agility = AGI; }
void Soldado::setArmadura(int DEF) { this->armor = DEF; }
void Soldado::setCritChance(int CRIT) { this->critChance = CRIT; }

void Soldado::executarAcao(Soldado& inimigo) {
    vector<shared_ptr<Soldado>> empty_vec;
    executarAcao(inimigo, empty_vec, empty_vec);
}
void Soldado::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliadosTeam, vector<shared_ptr<Soldado>>& inimigosTeam) {
    if (!vivo()) {
        cout << nome << " chega ao duelo morto...\n\n";
        return;
    }
    atacar(inimigo);
}
void Soldado::atacar(Soldado& inimigo) { atacar(inimigo, poderDeAtaque); }
void Soldado::atacar(Soldado& inimigo, double ATK) {
    if (!inimigo.vivo()) {
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
    cout << fixed << setprecision(2) << "Dano reduzido em " << (int)(armor_defend_percentage(armor) * 100) << "% pela armadura.\nDano recebido por " << nome << ": " << dano << "\n\n";
    saude = max((double)0, saude - (dano));
    if (!vivo()) cout << nome << " morreu...\n\n";
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
//void Soldado::descricao() { return; }

// Elfo
//string Elfo::raca = "Elfo";
Elfo::Elfo(double HP, double ATK, string N, int AGI, int ARM, int CRIT) : Soldado(HP, ATK, N, AGI + 30, ARM - 25, CRIT) {
    raca = "Elfo";
}
void Elfo::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos) {
    if (!vivo()) {
        cout << nome << " chega ao duelo morto...\n\n";
        return;
    }
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
    // Ataque no segundo inimigo aleatoria (nao morto nem o atual)
    if (copia_de_inimigos.size() == 0) return;
    shuffle(copia_de_inimigos.begin(), copia_de_inimigos.end(), RNG);
    Soldado::atacar(**find(inimigos.begin(), inimigos.end(), copia_de_inimigos[0]));
}
void Elfo::descricao() {
    cout << "-------------------------------------------ELFO------------------------------------------\n";
    cout << "Stats: AGI + 30, ARM - 25, CRIT - 20%\n";
    cout << "Ataque: Alem do inimigo no duelo, acerta outro inimigo aleatoriamente, caso seja possivel\n";
}

// Anao
//string Anao::raca = "Anao";
Anao::Anao(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK - 10, N, AGI - 20, ARM + 25) {
    raca = "Anao";
}
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
    cout << "-------------------------------------------ANAO------------------------------------------\n";
    cout << "Stats: ARM + 25, ATK - 10, AGI - 20, CRIT - 5%\n";
    cout << "Ataque: Dano extra para inimigos com pouca vida. Além disso, pode dar 20 de dano extra,\nou atacar com metade do ATK\n";
    cout << "Defesa: Toda vez que defende, ganha +3 ATK\n\n";
}

// Humano
//string Humano::raca = "Humano";
Humano::Humano(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK, N, AGI, ARM) {
    raca = "Humano";
}
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
    cout << "------------------------------------------HUMANO-----------------------------------------\n";
    cout << "Stats: Crit - 5%\n";
    cout << "Ataque: 15\% de ataque duplo\n";
    cout << "Defesa: 25\% de contra-atacar com metade do ATK\n";
}

// Sauron
//string Sauron::raca = "Sauron";
Sauron::Sauron(double HP, double ATK, string N, int AGI, int ARM) : Soldado(5 * HP, ATK, N, AGI, ARM) {}
void Sauron::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos) {
    if (!vivo()) {
        cout << nome << " chega ao duelo morto...\n\n";
        return;
    }
    int random = RNG() % 100;
    if (random < 20) {
        cout << nome << " executa um ataque pesado!\n";
        Soldado::atacar(inimigo, 1.5 * poderDeAtaque);
    } else if (random < 40) {
        cout << nome << " executa 3 ataques leves!\n";
        Soldado::atacar(inimigo, poderDeAtaque / 2);
        Soldado::atacar(inimigo, poderDeAtaque / 2);
        Soldado::atacar(inimigo, poderDeAtaque / 2);
    } else if (random < 70 && saude / maxHP <= 0.4) {
        cout << nome << " entra em uma furia descontrolada! Ele ataca TODOS!\n";
        for (auto it = aliados.begin(); it != aliados.end(); it++) {
            if (!(*it)->vivo()) continue;
            Soldado::atacar(**it, poderDeAtaque);
        }
        for (auto it = inimigos.begin(); it != inimigos.end(); it++) {
            if (!(*it)->vivo() || (*it)->getNome() == nome) continue;
            Soldado::atacar(**it, poderDeAtaque);
        }
    } else {
        cout << nome << " ataca e ganha +5 ATK e recupera +30 HP!\n";
        // Ataque padrao com self buff
        Soldado::atacar(inimigo, poderDeAtaque);
        setPoderdeAtaque(poderDeAtaque + 5);
        setSaude(min(saude + 30, saude));
    }
}
void Sauron::descricao() {
    cout << "Stats:\nHP * 5\nCrit: 5%\n\n";
}

// Orc
//string Orc::raca = "Orc";
Orc::Orc(double HP, double ATK, std::string N, int AGI, int ARM) : Soldado(HP + 60, ATK, N, AGI - 20, ARM + 30) {}
void Orc::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    if (random < 20) {
        cout << nome << " executou dois ataques mais fortes!\n";
        Soldado::atacar(inimigo, 1.1 * poderDeAtaque);
        Soldado::atacar(inimigo, 1.1 * poderDeAtaque);
    } else
        Soldado::atacar(inimigo, poderDeAtaque);
}
void Orc::defender(double dano) {
    setArmadura(armor - 2);
    Soldado::defender(dano);
}
void Orc::descricao() {
    cout << "Stats:\nHP + 60, ARM + 30\nAGI - 20\nCrit - 5%\n\n";
}

// OrcBerserk
//string OrcBerserk::raca = "OrcBerserk";
OrcBerserk::OrcBerserk(double HP, double ATK, string N, int AGI, int ARM, int CRIT) : Soldado(HP + 100, ATK + 10, N, AGI - 10, ARM + 20, CRIT) {}
void OrcBerserk::atacar(Soldado& inimigo) {
    int random = RNG() % 100;
    int ene_armor = inimigo.getArmadura();
    double DMG = poderDeAtaque;
    // Dano bonus = 5% vida do inimigo
    if (saude / maxHP < 0.2) DMG += 0.05 * inimigo.getSaude();
    if (random < 30) {
        cout << nome << " faz um ataque que ignora a armadura de " << inimigo.getNome() << " !\n";
        inimigo.setArmadura(0);
        Soldado::atacar(inimigo, DMG);
        inimigo.setArmadura(ene_armor);
    } else if (random < 40) {
        cout << nome << " sacrifica parte de seu ataque para aumentar sua armadura\n";
        cout << "ATK: " << (int)poderDeAtaque << "  -->  " << (int)(poderDeAtaque * 0.66) << "\n";
        cout << "DEF: " << armor << "  -->  " << (int)(1.5 * armor) << "\n\n";
        setPoderdeAtaque(0.66 * poderDeAtaque);
        setArmadura((int)(1.5 * armor));
    } else
        Soldado::atacar(inimigo, DMG);
}
void OrcBerserk::defender(Soldado& inimigo, double dano) {
    cout << "A armadura de espinhos de " << nome << " causa 5 de dano a " << inimigo.getNome() << "\n";
    inimigo.setSaude(max(1.0, inimigo.getSaude() - 5));
    Soldado::defender(dano);
}
void OrcBerserk::descricao() {
    cout << "Stats:\nHP + 100, DEF + 20, ATK + 10\nAGI - 10\nCrit: 10%\n\n";
}

// Saruman
string Saruman::raca = "Saruman";
Saruman::Saruman(double HP, double ATK, string N, int AGI, int DEF, int CRIT) : Soldado(HP + 40, ATK + 15, N, AGI + 10, DEF - 25, CRIT) {}
void Saruman::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos) {
    if (!vivo()) {
        cout << nome << " chega ao duelo morto...\n\n";
        return;
    }
    int random = RNG() % 100;
    if (random < 25) {
        // Remove inimigos mortos de uma copia dos inimigos
        vector<shared_ptr<Soldado>> copia_de_inimigos = inimigos;
        for (auto it = copia_de_inimigos.begin(); it != copia_de_inimigos.end(); it++) {
            if (!(*it)->vivo()) {
                it = copia_de_inimigos.erase(it);
                it--;
            }
        }
        // Se o unico vivo e ele mesmo, fazer diferente
        if (copia_de_inimigos.size() == 1) {
            cout << nome << " executa uma encantacao, se fortalecendo:\n";
            cout << "HP + 30, ATK + 10, DEF + 5, AGI + 5, CRIT + 1\n\n";
            setSaude(min(maxHP, saude + 30));
            setPoderdeAtaque(poderDeAtaque + 10);
            setArmadura(armor + 5);
            setAgilidade(agility + 5);
            setCritChance(critChance + 1);
            return;
        }
        shuffle(copia_de_inimigos.begin(), copia_de_inimigos.end(), RNG);
        shared_ptr<Soldado> alvo = *find(inimigos.begin(), inimigos.end(), copia_de_inimigos[0]);
        cout << nome << " rouba atributos de um de seus proprios aliados, " << alvo->getNome() << ", tornando-o fraco e incapacitado\n\n";
        setSaude(min(maxHP, saude + 30));
        setPoderdeAtaque(poderDeAtaque + alvo->getPoderdeAtaque() / 2);
        setArmadura(armor + alvo->getArmadura() / 2);
        setAgilidade(agility + alvo->getAgilidade() / 2);
        setCritChance(critChance + alvo->getCritChance() / 2);
        alvo->setSaude(0.6 * alvo->getSaude());
        alvo->setPoderdeAtaque(10);
        alvo->setArmadura(5);
        alvo->setAgilidade(5);
        alvo->setCritChance(1);
    } else if (random < 50) {
        cout << nome << " suga a forca de " << inimigo.getNome() << ", se curando no processo\n\n";
        setSaude(min(maxHP, saude + 30));
        inimigo.setPoderdeAtaque(min(0.9 * inimigo.getPoderdeAtaque() - 5, 10.0));
        inimigo.setAgilidade(inimigo.getAgilidade() - 3);
        inimigo.setArmadura(inimigo.getArmadura() - 3);
    } else {
        atacar(inimigo);
    }
}
void Saruman::atacar(Soldado& inimigo) {
    // Mais dano quanto mais vida tem
    double DMG = poderDeAtaque * (1 + 0.25 * (saude / maxHP));
    Soldado::atacar(inimigo, DMG);
}
void Saruman::descricao() {
    cout << "Stats:\nHP + 40, AGI + 10, ATK + 15\nDEF - 25\nCrit: 10%\n\n";
}

// Mago
Mago::Mago(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP - 100, ATK + 25, N, AGI + 10, ARM - 10) {
    raca = "Mago";
}
void Mago::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos) {
    if (!vivo()) {
        cout << nome << " chega ao duelo morto...\n\n";
        return;
    }
    int random = RNG() % 100;
    if (random < 50) {
        cout << nome << " aplica um efeito de cura em todos os seus aliados e os inspira:\n";
        for (auto it = aliados.begin(); it != aliados.end(); it++) {
            if (!(*it)->vivo()) continue;
            cout << (*it)->getNome() << " recebe AGI + 2, DEF + 2, CRIT + 2, ATK + 5, HP + 30\n";
            (*it)->setAgilidade((*it)->getAgilidade() + 2);
            (*it)->setArmadura((*it)->getArmadura() + 2);
            (*it)->setCritChance((*it)->getCritChance() + 2);
            (*it)->setPoderdeAtaque((*it)->getPoderdeAtaque() + 5);
            (*it)->setSaude(min((*it)->getSaude() + 30, (*it)->getMaxHP()));
        }
        cout << "\n";
    } else if (random < 60) {
        cout << nome << " aplica um efeito de cura em si mesmo e aumenta seu poder de ataque exponencialmente!\n";
        cout << "ATK: " << (int)poderDeAtaque << "  ->  ";
        setPoderdeAtaque(1.6 * poderDeAtaque);
        cout << (int)poderDeAtaque << "\n\n";
        setSaude(min(100 + saude, saude));
    } else
        atacar(inimigo);
}
void Mago::atacar(Soldado& inimigo) {
    int random = RNG() % 40;
    Soldado::atacar(inimigo, poderDeAtaque * (1 + (float)random / 100));
}
void Mago::descricao() {
    cout << "-------------------------------------------MAGO------------------------------------------\n";
    cout << "Stats: ATK + 25, AGI + 10, HP - 100, ARM - 10, Crit - 5%\n";
    cout << "Ataque: Sempre da dano extra de 0-40\%\n";
    cout << "Habilidade: Pode Melhorar os stats dos seus aliados ou se curar e aumentar o proprio ATK\n";
}

// Hobbit
//string Hobbit::raca = "Hobbit";
int Hobbit::number_of_hobbits = 0;
const int Hobbit::group_attack_probability[6] = {0, 0, 32, 22, 18, 15};
Hobbit::~Hobbit() { number_of_hobbits--; }
Hobbit::Hobbit(double HP, double ATK, string N, int AGI, int ARM) : Soldado(HP, ATK - 20, N, AGI + 20, ARM) {
    number_of_hobbits++; raca = "Hobbit";
}
void Hobbit::executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos) {
    if (!vivo()) {
        cout << nome << " chega ao duelo morto...\n\n";
        return;
    }
    int random = RNG() % 100;
    if (random < group_attack_probability[number_of_hobbits]) {
        cout << nome << " inspira todos os demais Hobbits, fazendo um grande ataque em grupo!\n\n";
        for (auto it = aliados.begin(); it != aliados.end(); it++) {
            if (shared_ptr<Hobbit> dummy_hobbit = dynamic_pointer_cast<Hobbit>(*it)) {
                if (!(*it)->vivo()) continue;
                (*it)->atacar(inimigo);
            }
        }
    } else
        Soldado::atacar(inimigo);
}
void Hobbit::defender(Soldado& inimigo, double dano) {
    Soldado::defender(inimigo, dano);
    if (!vivo()) number_of_hobbits--;
}
void Hobbit::descricao() {
    cout << "------------------------------------------HOBBIT-----------------------------------------\n";
    cout << "Stats: AGI + 20, ATK - 20, ARM - 10, CRIT - 5%\n";
    cout << "Ataque: ~50\% de chamar todos os outros Hobbits do time para atacarem junto\n";
}
int Hobbit::getNofHobbits() { return number_of_hobbits; }
