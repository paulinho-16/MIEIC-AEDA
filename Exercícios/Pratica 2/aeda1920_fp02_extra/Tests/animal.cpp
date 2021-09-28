
#include "animal.h"
#include <sstream>
using namespace std;

/*
 * Classe Animal
 */

int Animal::maisJovem = 99;

string Animal::getNome() const
{
	return nome;
}

Animal::Animal(string nome, int idade)
{
    this->nome = nome;
    this->idade = idade;
    if (idade < maisJovem)
        maisJovem = idade;
}

Cao::Cao(string nome, int idade, string raca) : Animal(nome,idade)
{
    this->raca = raca;
}

Voador::Voador(int vmax, int amax)
{
    velocidade_max = vmax;
    altura_max = amax;
}

Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome,idade), Voador(vmax,amax) {}

bool Cao::eJovem() const
{
    if (idade < 5)
        return true;
    return false;
}

bool Morcego::eJovem() const
{
    if (idade < 4)
        return true;
    return false;
}

string Animal::getInformacao() const
{
    string result = nome + ", " + to_string(idade);
    return result;
}

string Cao::getInformacao() const
{
    return Animal::getInformacao() + ", " + raca;
}

string Voador::getInformacao() const
{
    string result = to_string(velocidade_max) + ", " + to_string(altura_max);
    return result;
}

string Morcego::getInformacao() const
{
    string result = Animal::getInformacao() + ", " + Morcego::getInformacao();
    return result;
}
