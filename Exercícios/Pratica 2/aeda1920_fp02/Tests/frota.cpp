#include "frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1)
{
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const
{
    return veiculos.size();
}

int Frota::menorAno() const
{
    if (veiculos.size() == 0)
        return 0;
    int menor_ano = 999999;
    for (size_t i = 0;i<veiculos.size();i++)
    {
        if ((*veiculos.at(i)).getAno() < menor_ano)
            menor_ano = (*(veiculos.at(i))).getAno();
    }
    return menor_ano;
}

ostream & operator<<(ostream & o, const Frota & f)
{
    for (size_t i = 0;i<f.veiculos.size();i++)
    {
        (*(f.veiculos.at(i))).info();
    }
    return o;
}

vector<Veiculo *> Frota::operator() (int anoM) const
{
    vector<Veiculo *> ano_igual;
    for (size_t i = 0;i< veiculos.size();i++)
    {
        if (((*(veiculos.at(i))).getAno()) == anoM)
            ano_igual.push_back(veiculos.at(i));
    }
    return ano_igual;
}

float Frota::totalImposto() const
{
    float soma = 0;
    for (size_t i = 0;i<veiculos.size();i++)
    {
        soma += (*(veiculos.at(i))).calcImposto();
    }
    return soma;
}