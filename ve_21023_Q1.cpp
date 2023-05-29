#include <iostream>
#include <random>

using namespace std;
random_device random_number;

class Soldado {
  protected:
    string nome;
    int saude;
    int poder_de_ataque;
    ~Soldado() = default;
    Soldado(string nome, int saude, int poder_de_ataque) : nome(nome), saude(saude), poder_de_ataque(poder_de_ataque) {}

  public:
    string getNome() { return nome; };
    int getSaude() { return saude; };
    int getPoderDeAtaque() { return poder_de_ataque; };
    void atacar(Soldado& target) {
        if (saude > 0)
            target.defender(poder_de_ataque);
    };
    void defender(int dano) {
        saude -= dano;
        // if (saude <= 0)
        //     delete this;
    };
};

class Elfo : public Soldado {
  public:
    ~Elfo() = default;
    Elfo(string nome, int saude, int poder_de_ataque)
        : Soldado(
              nome,
              saude,
              poder_de_ataque + 1) {}
};

class Anao : public Soldado {
  public:
    ~Anao() = default;
    Anao(string nome, int saude, int poder_de_ataque)
        : Soldado(
              nome,
              saude,
              poder_de_ataque + 20) {}

    void atacar(Soldado& target) {
        if (random_number() % 100 < 60)
            target.defender(poder_de_ataque);
    };
};

class Humano : public Soldado {
  public:
    ~Humano() = default;
    Humano(string nome, int saude, int poder_de_ataque)
        : Soldado(
              nome,
              saude,
              poder_de_ataque) {}

    void atacar(Soldado& target) {
        if (random_number() % 100 < 90)
            target.defender(poder_de_ataque);
        else {
            target.defender(poder_de_ataque);
            target.defender(poder_de_ataque);
        }
    };
};

class Orc : public Soldado {
  public:
    ~Orc() = default;
    Orc(string nome, int saude, int poder_de_ataque)
        : Soldado(
              nome,
              saude,
              poder_de_ataque) {}

    void atacar(Soldado& target) {
        if (random_number() % 100 < 80)
            target.defender(poder_de_ataque);
        else {
            target.defender(poder_de_ataque * 1.1);
            target.defender(poder_de_ataque * 1.1);
        }
    };
};

class Sauron : public Soldado {
  public:
    ~Sauron() = default;
    Sauron(string nome, int saude, int poder_de_ataque)
        : Soldado(
              nome,
              10 * saude,
              poder_de_ataque) {}

    void atacar(Soldado& target) {
        if (random_number() % 100 < 70)
            target.defender(poder_de_ataque);
        else {
            target.defender(2 * poder_de_ataque);
        }
    };
};

class Mago : public Soldado {
  public:
    ~Mago() = default;
    Mago(string nome, int saude, int poder_de_ataque)
        : Soldado(
              nome,
              saude / 2,
              2.5 * poder_de_ataque) {}

    void atacar(Soldado& target) {
        if (random_number() % 100 < 95)
            target.defender(poder_de_ataque);
        else {
            target.defender(poder_de_ataque * 4);
        }
    };
};

int main() {
    // Criar exercito aleatoriamente e atacar aleatoriamente ate sobrar um soldado com saude > 0
    Sauron E("eb", 10, 10);
    Mago A("an", 10, 10);
    cout << E.getNome() << " ";
    cout << E.getSaude() << " ";
    cout << E.getPoderDeAtaque() << endl;
    cout << A.getNome() << " ";
    cout << A.getSaude() << " ";
    cout << A.getPoderDeAtaque() << endl;
    A.atacar(E);
    cout << E.getSaude();

    return 0;
}