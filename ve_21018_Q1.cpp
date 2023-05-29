#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Soldado {
   private:
    string nome;
    double saude, poderDeAtaque;

public:
    Soldado(){}
    int getPoderdeAtaque() {
        return poderDeAtaque;
    }
    int getSaude() {
        return saude;
    }
    string getNome() {
        return nome;
    }
    void setPoderdeAtaque(int poderDeAtaque){
        this->poderDeAtaque = poderDeAtaque;
    }
    void setSaude(double saude){
        this->saude = saude;
    }
    void defender(double poderDeAtaque) {
        saude = max((double)0, saude - poderDeAtaque);
    }
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
    Elfo(double saude, double poderDeAtaque, string nome) : Soldado(saude, 1+poderDeAtaque, nome){}
    void atacar(Soldado& inimigo){
        inimigo.defender(getPoderdeAtaque());
    }
};

class Anao : public Soldado {
   public:
    Anao(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome){}
    void atacar(Soldado& inimigo) {
        double random = (double)rand() / RAND_MAX;
        if(random > 0.4)
            inimigo.defender(20 + getPoderdeAtaque());
        else
            inimigo.defender(0);
    }
};

class Humano : public Soldado {
   public:
    Humano(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome){}
    void atacar(Soldado& inimigo) {
        double random = (double)rand() / RAND_MAX;
        inimigo.defender(getPoderdeAtaque());
        if(random < 0.1) inimigo.defender(getPoderdeAtaque());
    }
};

class Sauron : public Soldado{
    public:
    Sauron(double saude, double poderDeAtaque, string nome) : Soldado(10*saude, poderDeAtaque, nome) {}
    void atacar(Soldado& inimigo) {
        double random = (double)rand() / RAND_MAX;
        if(random < 0.3)
            inimigo.defender(2*getPoderdeAtaque());
        else
            inimigo.defender(getPoderdeAtaque());
    }
};

class Orc : public Soldado{
    public:
    Orc(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {}
    void atacar(Soldado& inimigo) {
        double random = (double)rand() / RAND_MAX;
        if(random < 0.2){
            inimigo.defender(1.1*getPoderdeAtaque());
            inimigo.defender(1.1*getPoderdeAtaque());
        }
        else
            inimigo.defender(getPoderdeAtaque());
    }
};

class Mago : public Soldado{
public:
    Mago(double saude, double poderDeAtaque, string nome) : Soldado(saude, poderDeAtaque, nome) {
    }

    void atacar(Soldado& inimigo) {
        double random = (double)rand() / RAND_MAX;
        if (random < 0.7){
            inimigo.defender(getPoderdeAtaque());
        }
        else{
            //inimigo.defender(getPoderdeAtaque());
            setPoderdeAtaque(2*getPoderdeAtaque());
            setSaude(100+getSaude());
        }
    }
};

int main() {
    srand(time(NULL));
    Soldado* soldados[22];
    
    bool finish = 0;
    int cnt =22;
    int iterations = 20;
    while(iterations--){
        soldados[0] = new Mago(300,50,"gandolf");
        soldados[1] = new Sauron(100,10,"sauron");
        for(int i=2;i<12;i++){
            soldados[i] = new Orc(100,10,"orc");
        }
        for(int i=12;i<17;i++){
            soldados[i] = new Anao(100,10,"Anao");
        }
        for(int i=17;i<22;i++){
            soldados[i] = new Humano(100,10,"Humano");
        }
        finish = 0;
        cnt = 22;
        while (!finish){
            if(cnt == 1){
                cout << soldados[0]->getNome() << "\n";
                finish = 1;
            }
            soldados[rand() % cnt]->atacar(*soldados[rand() % cnt]);
            for(int i=0;i<cnt;i++){
                if(soldados[i]->getSaude() == (double)0){
                    Soldado* temp = soldados[i];
                    cnt--;
                    soldados[i] = soldados[cnt];
                    soldados[cnt] = temp;
                }
                //cout << soldados[i]->getNome() << "/" << soldados[i]->getSaude() << " ";
            }
            //cout << "\n";
        }
        for(int i=0;i<22;i++){
            delete soldados[i];
        }
    }
    
    return 0;
}