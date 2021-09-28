#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{
    tabHInt::const_iterator it = numeros.find(num);
    if (it == numeros.end())
        return false;
    return true;
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    numeros.clear();
    unsigned int m = 0, i = 0;
    while (m<n) {
        pair<tabHInt::iterator,bool> retorno = numeros.insert(valores[i]);
        if (retorno.second)
            m++;
        i++;
    }
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    unsigned int certos = 0;
    for (tabHInt::const_iterator it = sorteio.begin() ; it != sorteio.end() ; it++) {
        if (contem(*it))
            certos++;
    }
    return certos;
}

unsigned int Aposta::somaNumeros() const {
    unsigned int soma = 0;
    for (tabHInt::const_iterator it = numeros.begin() ; it != numeros.end() ; it++) {
        soma += (*it);
    }
    return soma;
}

unsigned int Aposta::tamanho() const {
    return numeros.size();
}


