#ifndef SOLDADO_H
#define SOLDADO_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <queue>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
class Soldado {
  protected:
    std::string nome;
    double saude, poderDeAtaque;

  public:
    Soldado();
    Soldado(double saude, double poderDeAtaque, std::string nome);
    int getPoderdeAtaque();
    int getSaude();
    std::string getNome();
    void setPoderdeAtaque(int poderDeAtaque);
    void setSaude(double saude);
    bool vivo();
    void defender(double dano);
    virtual void atacar(Soldado& inimigo);
    void imprimirStatus();
};

class Elfo : public Soldado {
  public:
    Elfo(double saude, double poderDeAtaque, std::string nome);
};

class Anao : public Soldado {
  public:
    Anao(double saude, double poderDeAtaque, std::string nome);
    void atacar(Soldado& inimigo);
};

class Humano : public Soldado {
  public:
    Humano(double saude, double poderDeAtaque, std::string nome);
    void atacar(Soldado& inimigo);
};

class Sauron : public Soldado {
  public:
    Sauron(double saude, double poderDeAtaque, std::string nome);
    void atacar(Soldado& inimigo);
};

class Orc : public Soldado {
  public:
    Orc(double saude, double poderDeAtaque, std::string nome);
    void atacar(Soldado& inimigo);
};

class Mago : public Soldado {
  public:
    Mago(double saude, double poderDeAtaque, std::string nome);
    void atacar(Soldado& inimigo);
};


#endif
