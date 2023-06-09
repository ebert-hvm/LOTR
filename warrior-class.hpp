#ifndef WARRIOR_CLASS_H
#define WARRIOR_CLASS_H

#include <iostream>
#include <random>
#include <string>

class Soldado {
  protected:
    std::string nome;
    double saude, poderDeAtaque;
    int agility, armor;

    double agility_dodge_probability(int agility) {
        if (agility > 0)
            return 0.25 * std::atan((double)agility / 30) * std::atan((double)agility / 30);
        return 0;
    }
    double armor_defend_probability(int armor) {
        if (armor > 0)
            return 0.5 * std::atan((double)armor / 50);
        return 0;
    }

  public:
    Soldado();
    Soldado(double HP, double ATK, std::string N, int AGI, int ARM);

    int getPoderdeAtaque();
    int getSaude();
    std::string getNome();

    void setPoderdeAtaque(int poderDeAtaque);
    void setSaude(double saude);

    virtual void defender(double dano);
    virtual void atacar(Soldado& inimigo);
    void imprimirStatus();
};

class Elfo : public Soldado {
  public:
    Elfo(double HP, double ATK, std::string N, int AGI, int ARM);
};

class Anao : public Soldado {
  public:
    Anao(double HP, double ATK, std::string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
};

class Humano : public Soldado {
  public:
    Humano(double HP, double ATK, std::string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
};

class Sauron : public Soldado {
  public:
    Sauron(double HP, double ATK, std::string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
};

class Orc : public Soldado {
  public:
    Orc(double HP, double ATK, std::string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
};

class Mago : public Soldado {
  public:
    Mago(double HP, double ATK, std::string N, int AGI, int ARM);
    void atacar(Soldado& inimigo);
};

#endif
