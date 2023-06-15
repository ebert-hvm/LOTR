#include "equipe.hpp"

class Combate {
  private:
    vector<unique_ptr<Horda>> hordas;
    Aliados aliados;
    int horda_atual;
    public:
    Combate();
    int executarRodada();
    bool iniciar();
};