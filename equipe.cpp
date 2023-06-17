#include "equipe.hpp"

// EQUIPE
void Equipe::randomEnqueue(vector<shared_ptr<Soldado>> soldadosVivos)
{
    vector<int> permutation(soldadosVivos.size());
    iota(permutation.begin(), permutation.end(), 0);
    random_device rd;
    mt19937 rng(rd());
    shuffle(permutation.begin(), permutation.end(), rng);
    for (auto index : permutation)
    {
        fila.push(soldadosVivos[index]);
    }
    /*queue<shared_ptr<Soldado>> debug;
    while(!fila.empty()){
        shared_ptr<Soldado> ptr = fila.front();
        debug.push(ptr);
        fila.pop();
        ptr->imprimirStatus();
    }
    fila = debug;*/
}

bool Equipe::checarProximoSoldado()
{
    return !fila.empty();
}

shared_ptr<Soldado> Equipe::proximoSoldado()
{
    if (!fila.empty())
    {
        shared_ptr<Soldado> ptr = fila.front();
        fila.pop();
        return ptr;
    }
    else
        return nullptr;
}

void Equipe::print()
{
    for (const auto &el : soldados)
    {
        el->imprimirStatus();
    }
}

vector<shared_ptr<Soldado>> &Equipe::getSoldados()
{
    return soldados;
};

// HORDA
Horda::Horda(int index)
{
    switch (index)
    {
    case 0:
        for (int i = 0; i < 9; i++)
        {
            string nome = "Orc" + to_string(i + 1);
            soldados.push_back(make_shared<Orc>(100, 20, nome, 10, 10));
        }
        soldados.push_back(make_shared<OrcBerserk>(100, 40, "Orc Berserk", 10, 15));
        break;
    case 1:
        for (int i = 0; i < 5; i++)
        {
            string nome = "Orc" + to_string(i + 1);
            soldados.push_back(make_shared<Orc>(100, 25, nome, 15, 15));
        }
        for (int i = 0; i < 3; i++)
        {
            string nome = "Orc Berserk" + to_string(i + 1);
            soldados.push_back(make_shared<OrcBerserk>(220, 45, nome, 25, 25));
        }
        soldados.push_back(make_shared<Saruman>(250, 50, "Saruman", 5, 20));
        break;
    case 2:
        for (int i = 0; i < 5; i++)
        {
            string nome = "Orc" + to_string(i + 1);
            soldados.push_back(make_shared<Orc>(200, 30, nome, 15, 15));
        }
        for (int i = 0; i < 5; i++)
        {
            string nome = "Orc Berserk" + to_string(i + 1);
            soldados.push_back(make_shared<OrcBerserk>(220, 50, nome, 25, 30));
        }
        soldados.push_back(make_shared<Sauron>(400, 50, "Dew'Artt", 10, 70));
        break;
    default:
        throw("Indice inválido!");
        break;
    }
    randomEnqueue(soldados);
}

int Horda::size()
{
    return 3;
}

// ALIADOS
void Aliados::montarEquipe()
{
    int cont = 0;
    vector<shared_ptr<Soldado>> vec = {
        make_shared<Mago>(400, 40, "Gandalf", 30, 40),
        make_shared<Hobbit>(240, 48, "Frodo", 70, 30),
        make_shared<Hobbit>(225, 45, "Bilbo", 70, 30),
        make_shared<Hobbit>(220, 36, "Sam", 70, 30),
        make_shared<Hobbit>(210, 36, "Marry", 70, 30),
        make_shared<Hobbit>(200, 50, "Pippin", 70, 30),
        make_shared<Humano>(300, 50, "Aragorn", 50, 45),
        make_shared<Humano>(300, 40, "Boromir", 40, 40),
        make_shared<Elfo>(250, 30, "Legolas", 50, 45),
        make_shared<Elfo>(250, 30, "Elrond", 40, 40),
        make_shared<Anao>(300, 40, "Gimli", 50, 50),
        make_shared<Anao>(280, 30, "Thorin", 40, 40)
    };
    while (cont < 5)
    {
        system("clear");
        cout << "Monte sua equipe!\n";
        Mago::descricao();
        Hobbit::descricao();
        Humano::descricao();
        Elfo::descricao();
        Anao::descricao();
        //cout << "-----------------------------------------------------------\n";
        cout << "Equipe: ";
        for(auto sol: soldados) {
            cout << sol->getNome() << " | ";
        }
        cout << "\nVocê deve escolher 5 aliados (" << cont << " / 5)\n";
        for(int i=0;i<vec.size();i++){
            cout << setw(2) <<i+1 << " - " << setw(7) << vec[i]->getNome() << " - " << vec[i]->getRaca() << "\n";
        }
        int choice = choiceHandler(vec.size());
        soldados.push_back(vec[choice-1]);
        vec.erase(vec.begin()+choice-1);
        cont++;
    }
    system("clear");
    cout << "Equipe escolhida: ";
    for(auto sol: soldados) {
        cout << sol->getNome() << " | ";
    }
    cout << "\nComeçar...\n";
    cin.get();
}

Aliados::Aliados()
{
    montarEquipe();
    randomEnqueue(soldados);
}

int choiceHandler(int optionsNumber)
{
    int choice;
    while (1)
    {
        if (!(cin >> choice) || choice <= 0 || choice > optionsNumber)
        {
            cout << "Escolha Inválida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
            return choice;
    }
}