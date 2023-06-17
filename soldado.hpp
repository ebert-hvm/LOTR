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

using namespace std;
class Soldado {
  protected:
    string nome;
    double saude, maxHP, poderDeAtaque;
    int agility, armor, critChance;

    double agility_dodge_probability(int agility);
    double armor_defend_percentage(int armor);

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
    virtual void defender(Soldado& inimigo, double dano);

    void imprimirStatus();
    virtual void descricao();
};

class Elfo : public Soldado {
    static string raca;

  public:
    Elfo(double HP, double ATK, string N, int AGI, int ARM, int CRIT = 20);
    void executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos);
    // void defender(double dano);
    static void descricao();
};

class Anao : public Soldado {
    static string raca;

  public:
    Anao(double HP, double ATK, string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
    void defender(double dano);
    static void descricao();
};

class Humano : public Soldado {
    static string raca;

  public:
    Humano(double HP, double ATK, string N, int AGI, int ARM);
    void atacar(Soldado& inimigo, double ATK);
    void defender(Soldado& inimigo, double dano);
    static void descricao();
};

class Sauron : public Soldado {
    static string raca;

  public:
    Sauron(double HP, double ATK, string N, int AGI, int ARM);
    void executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos);
    void descricao();
};

class Orc : public Soldado {
    static string raca;

  public:
    Orc(double HP, double ATK, string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
    void defender(double dano);
    void descricao();
};

class OrcBerserk : public Soldado {
    static string raca;

  public:
    OrcBerserk(double HP, double ATK, string N, int AGI, int ARM, int CRIT = 10);
    void atacar(Soldado& inimigo);
    void defender(Soldado& inimigo, double dano);
    void descricao();
};

class Mago : public Soldado {
    static string raca;

  public:
    Mago(double HP, double ATK, string N, int AGI, int ARM);
    void executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos);
    void atacar(Soldado& inimigo);
    static void descricao();
};

class Hobbit : public Soldado {
    static string raca;
    static const int group_attack_probability[6];
    static int number_of_hobbits;

  public:
    ~Hobbit();
    Hobbit(double HP, double ATK, string N, int AGI, int ARM);
    void executarAcao(Soldado& inimigo, vector<shared_ptr<Soldado>>& aliados, vector<shared_ptr<Soldado>>& inimigos);
    void defender(Soldado& inimigo, double dano);
    void descricao();
    int getNofHobbits();
};

#endif
