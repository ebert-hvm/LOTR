#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

using namespace std;
mt19937 rng{random_device{}()};

class Soldado {
  protected:
    string nome;
    double saude, poderDeAtaque;

  public:
    Soldado() {}
    int getPoderdeAtaque() { return poderDeAtaque; }
    int getSaude() { return saude; }
    string getNome() { return nome; }
    void setPoderdeAtaque(int poderDeAtaque) { this->poderDeAtaque = poderDeAtaque; }
    void setSaude(double saude) { this->saude = saude; }
    void defender(double dano) { saude = max((double)0, saude - dano); }
    Soldado(double saude, double poderDeAtaque, string nome) : saude(saude),
                                                               poderDeAtaque(poderDeAtaque),
                                                               nome(nome) {}
    virtual void atacar(Soldado& inimigo) = 0;
    void imprimirStatus() {
        cout << getNome() << ":\n";
        cout << "saude: " << getSaude() << "\n";
        cout << "poder de ataque: " << getPoderdeAtaque() << "\n\n";
    }
};

class Elfo : public Soldado {
  public:
    Elfo(double saude, double poderDeAtaque, string nome) : Soldado(saude, 1 + poderDeAtaque, nome) {}
    void atacar(Soldado& inimigo) {
        inimigo.defender(poderDeAtaque);
    }
};

class Anao : public Soldado {
  public:
    Anao(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
    void atacar(Soldado& inimigo) {
        int random = (rng() % 100);
        if (random > 40)
            inimigo.defender(20 + poderDeAtaque);
        else
            inimigo.defender(0);
    }
};

class Humano : public Soldado {
  public:
    Humano(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
    void atacar(Soldado& inimigo) {
        int random = rng() % 100;
        inimigo.defender(poderDeAtaque);
        if (random < 10) inimigo.defender(poderDeAtaque);
    }
};

class Sauron : public Soldado {
  public:
    Sauron(double saude, double poderDeAtaque, string nome) : Soldado(10 * saude, poderDeAtaque, nome) {}
    void atacar(Soldado& inimigo) {
        int random = rng() % 100;
        if (random < 30)
            inimigo.defender(2 * poderDeAtaque);
        else
            inimigo.defender(poderDeAtaque);
    }
};

class Orc : public Soldado {
  public:
    Orc(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
    void atacar(Soldado& inimigo) {
        int random = rng() % 100;
        if (random < 20) {
            inimigo.defender(1.1 * poderDeAtaque);
            inimigo.defender(1.1 * poderDeAtaque);
        } else
            inimigo.defender(poderDeAtaque);
    }
};

class Mago : public Soldado {
  public:
    Mago(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {
    }

    void atacar(Soldado& inimigo) {
        int random = rng() % 100;
        if (random < 70) {
            inimigo.defender(poderDeAtaque);
        } else {
            // inimigo.defender(poderDeAtaque);
            setPoderdeAtaque(2 * poderDeAtaque);
            setSaude(100 + saude);
        }
    }
};

int main() {
    Mago Bigger(20, 5, "bigger");
    Mago Eber(10, 10, "eber");
    Bigger.atacar(Eber);

    // Soldado* soldados[22];

    // bool finish = 0;
    // int cnt =22;
    // int iterations = 20;
    // while(iterations--){
    //     soldados[0] = new Mago(300,50,"gandolf");
    //     soldados[1] = new Sauron(100,10,"sauron");
    //     for(int i=2;i<12;i++){
    //         soldados[i] = new Orc(100,10,"orc");
    //     }
    //     for(int i=12;i<17;i++){
    //         soldados[i] = new Anao(100,10,"Anao");
    //     }
    //     for(int i=17;i<22;i++){
    //         soldados[i] = new Humano(100,10,"Humano");
    //     }
    //     finish = 0;
    //     cnt = 22;
    //     while (!finish){
    //         if(cnt == 1){
    //             cout << soldados[0]->getNome() << "\n";
    //             finish = 1;
    //         }
    //         soldados[rng() % cnt]->atacar(*soldados[rng() % cnt]);
    //         for(int i=0;i<cnt;i++){
    //             if(soldados[i]->getSaude() == (double)0){
    //                 Soldado* temp = soldados[i];
    //                 cnt--;
    //                 soldados[i] = soldados[cnt];
    //                 soldados[cnt] = temp;
    //             }
    //             //cout << soldados[i]->getNome() << "/" << soldados[i]->getSaude() << " ";
    //         }
    //         //cout << "\n";
    //     }
    //     for(int i=0;i<22;i++){
    //         delete soldados[i];
    //     }
    // }

    return 0;
}