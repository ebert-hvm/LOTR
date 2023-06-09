#include "equipe.hpp"

class Combate {
  private:
    vector<unique_ptr<Horda>> hordas;
    Aliados aliados;

  public:
    Combate();
    bool executarRodada();
};