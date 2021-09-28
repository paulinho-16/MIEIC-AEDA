#include "veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a)
{
    marca = mc;
    mes = m;
    ano = a;
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil) : Veiculo(mc,m,a)
{
    combustivel = c;
    cilindrada = cil;
}

Automovel::Automovel(string mc, int m, int a, string c, int cil) : Motorizado(mc,m,a,c,cil) {}

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm) : Motorizado(mc,m,a,c,cil)
{
    carga_maxima = cm;
}

Bicicleta::Bicicleta(string mc, int m, int a, string t) : Veiculo(mc,m,a)
{
    tipo = t;
}

string Veiculo::getMarca() const
{
    return marca;
}

int Veiculo::getAno() const
{
    return ano;
}

string Motorizado::getCombustivel() const
{
    return combustivel;
}

int Veiculo::info() const
{
    cout << "Marca: " << marca << endl;
    cout << "Mes: " << mes << endl;
    cout << "Ano: " << ano << endl;
    return 3;
}

int Motorizado::info() const
{
    int elementos_padrao = Veiculo::info();
    cout << "Combustivel: " << combustivel << endl;
    cout << "Cilindrada: " << cilindrada << endl;
    return elementos_padrao + 2;
}

int Automovel::info() const
{
    return Motorizado::info();
}

int Camiao::info() const
{
    int elementos_padrao = Motorizado::info();
    cout << "Carga Maxima: " << carga_maxima << endl;
    return elementos_padrao + 1;
}

int Bicicleta::info() const
{
    int elementos_padrao = Veiculo::info();
    cout << "Tipo: " << tipo << endl;
    return elementos_padrao + 1;
}

bool Veiculo::operator<(const Veiculo &v) const
{
    if (ano < v.getAno())
        return true;
    if (ano == v.getAno())
    {
        if (mes < v.mes)
            return true;
        else
            return false;
    }
    else
        return false;
}

float Veiculo::calcImposto() const
{
    return 0;
}

float Motorizado::calcImposto() const
{
    if ((combustivel == "gasolina") && (cilindrada <= 1000))
    {
        if (ano > 1995)
            return 14.56;
        else
            return 8.10;
    }
    if ((combustivel != "gasolina") && (cilindrada <= 1500))
    {
        if (ano > 1995)
            return 14.56;
        else
            return 8.10;
    }
    if ((combustivel == "gasolina") && (cilindrada > 1000) && (cilindrada <= 1300))
    {
        if (ano > 1995)
            return 29.06;
        else
            return 14.56;
    }
    if ((combustivel != "gasolina") && (cilindrada > 1500) && (cilindrada <= 2000))
    {
        if (ano > 1995)
            return 29.06;
        else
            return 14.56;
    }
    if ((combustivel == "gasolina") && (cilindrada > 1300) && (cilindrada <= 1750))
    {
        if (ano > 1995)
            return 45.15;
        else
            return 22.65;
    }
    if ((combustivel != "gasolina") && (cilindrada > 2000) && (cilindrada <= 3000))
    {
        if (ano > 1995)
            return 45.15;
        else
            return 22.65;
    }
    if ((combustivel == "gasolina") && (cilindrada > 1750) && (cilindrada <= 2600))
    {
        if (ano > 1995)
            return 113.98;
        else
            return 54.89;
    }
    if ((combustivel != "gasolina") && (cilindrada > 3000))
    {
        if (ano > 1995)
            return 113.98;
        else
            return 54.89;
    }
    if ((combustivel == "gasolina") && (cilindrada > 2600) && (cilindrada <= 3500))
    {
        if (ano > 1995)
            return 181.17;
        else
            return 87.13;
    }
    if ((combustivel == "gasolina") && (cilindrada > 3500))
    {
        if (ano > 1995)
            return 320.89;
        else
            return 148.37;
    }
}

float Automovel::calcImposto() const
{
    return Motorizado::calcImposto();
}

float Camiao::calcImposto() const
{
    return Motorizado::calcImposto();
}

float Bicicleta::calcImposto() const
{
    return 0;
}