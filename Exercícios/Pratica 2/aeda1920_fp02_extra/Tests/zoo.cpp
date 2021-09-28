#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

/*
 * Classe Zoo
 */

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1)
{
    animais.push_back(a1);
}

string Zoo::getInformacao() const
{
    string result;
    for (size_t i = 0;i<animais.size();i++)
    {
        result += (*(animais.at(i))).getInformacao() + " ";
    }
    cout << result;
    return result;
}

bool Zoo::animalJovem(string nomeA)
{
    for (size_t i = 0;i<animais.size();i++)
    {
        if ((*(animais.at(i))).getNome() == nomeA)
        {
            if ((*(animais.at(i))).eJovem())
                return true;
        }
    }
    return false;
}

void Zoo::alocaVeterinarios(istream &isV)
{
    string name;
    int code;
    while(!isV.eof())
    {
        getline(isV, name);
        isV >> code;
        isV.ignore(1000,'\n');
        Veterinario vet(name, code);
        veterinarios.push_back(&vet);
    }
}