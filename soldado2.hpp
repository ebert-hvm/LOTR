#ifndef SOLDADO2_H
#define SOLDADO2_H

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

class Soldado
{
protected:
    string nome;
    double saude, poderDeAtaque;

   public:
    // constructors
    Soldado();
    Soldado(double saude, double poderDeAtaque, string nome);
    //getters
    int getPoderdeAtaque();
    int getSaude();
    string getNome();
    bool vivo();
    //setters
    void setPoderdeAtaque(int poderDeAtaque);
    void setSaude(double saude);
    // abstract methods
    virtual void atacar(Soldado& inimigo) = 0;
    virtual void defender(double poderDeAtaque) = 0;
    //print
    void imprimirStatus();
};

class Elfo : public Soldado {
   public:
    Elfo(double saude, double poderDeAtaque, string nome);
    void atacar(Soldado& inimigo);
    void defender(double poderDeAtaque);
};

class Anao : public Soldado {
   public:
    Anao(double saude, double poderDeAtaque, string nome);
    void atacar(Soldado& inimigo);
    void defender(double poderDeAtaque);
};

#endif