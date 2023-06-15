#include "soldado.hpp"

class Equipe {
  protected:
    vector<shared_ptr<Soldado>> soldados;
    queue<shared_ptr<Soldado>> fila;

  public:
    void randomEnqueue(vector<shared_ptr<Soldado>>);
    shared_ptr<Soldado> proximoSoldado();
    bool checarProximoSoldado();
    void print();
};

class Horda : public Equipe {
   public:
    Horda(int index);
    static int size();
};

class Aliados : public Equipe {
  public:
    Aliados();
    void montarEquipe();
};

int choiceHandler(int optionsNumber);