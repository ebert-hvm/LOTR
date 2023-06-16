#ifndef SOLDADO_H
#define SOLDADO_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;
class Soldado {
  protected:
    string nome;
    double saude, maxHP, poderDeAtaque;
    int agility, armor, critChance;

    double agility_dodge_probability(int agility) {
        if (agility > 0)
            return 0.25 * atan((double)agility / 30) * atan((double)agility / 30);
        return 0;
    }
    double armor_defend_percentage(int armor) {
        if (armor > 0)
            return 0.5 * atan((double)armor / 50);
        return 0;
    }

  public:
    Soldado();
    Soldado(double HP, double ATK, string N, int AGI, int ARM, int CRIT = 5);

    double getPoderdeAtaque();
    double getSaude();
    double getMaxHP();
    string getNome();
    int getAgilidade();
    int getArmadura();
    int getCritChance();
    bool vivo();

    void setPoderdeAtaque(int ATK);
    void setSaude(double HP);
    void setMaxHP(double HP);
    void setAgilidade(int AGI);
    void setArmadura(int ARM);
    void setCritChance(int CRIT);
  
    virtual void executarAcao(Soldado& inimigo);
    virtual void executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos);
    virtual void atacar(Soldado& inimigo);
    virtual void atacar(Soldado& inimigo, double ATK);
    virtual void defender(double dano);

    void imprimirStatus();
    virtual void descricao();

    bool operator==(Soldado& bixo);
};

class Elfo : public Soldado {
  public:
    Elfo(double HP, double ATK, string N, int AGI, int ARM, int CRIT = 20);
    void executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos);
    // void defender(double dano);
    void descricao();
};

class Anao : public Soldado {
  public:
    Anao(double HP, double ATK, string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
    void defender(double dano);
    void descricao();
};

class Humano : public Soldado {
  public:
    Humano(double HP, double ATK, string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
    void descricao();
};

class Sauron : public Soldado {
  public:
    Sauron(double HP, double ATK, string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
    void descricao();
};

class Orc : public Soldado {
  public:
    Orc(double HP, double ATK, string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
    void descricao();
};

class Mago : public Soldado {
  public:
    Mago(double HP, double ATK, string N, int AGI, int ARM);
    void executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>> aliados, vector<shared_ptr<Soldado>> inimigos);
    void atacar(Soldado& inimigo);
    void descricao();
};

#endif
