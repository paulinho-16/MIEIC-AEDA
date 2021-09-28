/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

// a implementar
Jogo::Jogo()
{
    criancas = {};
}

// a implementar
Jogo::Jogo(list<Crianca>& lc2)
{
    criancas = lc2;
}

// a implementar
void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

// a implementar
list<Crianca> Jogo::getCriancasJogo() const
{
    list<Crianca> res;
    res = criancas;
    return res;
}

// a implementar
string Jogo::escreve() const
{
    string res;
    list<Crianca>::const_iterator it;
    for (it = criancas.begin() ; it != criancas.end() ; it++)
    {
        res += (*it).escreve() + "\n";
    }
    return res;
}

// a implementar
Crianca& Jogo::perdeJogo(string frase)
{
    Crianca *c1 = new Crianca();
    unsigned int palavras = numPalavras(frase);
    unsigned int salvo = (palavras-1) % criancas.size();
    unsigned int contador = 0;
    list <Crianca>::iterator it;
    while (criancas.size() > 1)
    {
        for (it = criancas.begin() ; it != criancas.end(); it++)
        {
            if (contador == salvo)
            {
                criancas.erase(it);
            }
            contador++;
        }
        salvo = (palavras-1) % criancas.size();
        contador = 0;
    }
    list <Crianca>::iterator perdedor = criancas.begin();
    *c1 = *perdedor;
    return *c1;
}

// a implementar
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

// a implementar
list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> res;
    list<Crianca>::iterator it;
    for (it = criancas.begin() ; it != criancas.end() ; it++)
    {
        if ((*it).getIdade() > id)
        {
            res.push_back(*it);
            criancas.erase(it);
        }
    }
    return res;
}

// a implementar
void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    criancas = l1;
}

// a implementar
bool Jogo::operator==(Jogo& j2)
{
	return j2.getCriancasJogo() == criancas;
}

// a implementar
list<Crianca> Jogo::baralha() const
{
    list<Crianca> res;
    list<Crianca>::const_iterator it;
    list<Crianca>::const_iterator ite;
    bool e_nova = true;
    unsigned int nova_crianca, contador = 0;
    srand(time(NULL));
    while (res.size() < criancas.size())
    {
        contador = 0;
        nova_crianca = rand() % criancas.size();
        for (it = criancas.begin() ; it != criancas.end() ; it++)
        {
            if (contador == nova_crianca)
            {
                for (ite = res.begin() ; ite != res.end() ; ite++)
                {
                    if (*it == *ite)
                        e_nova = false;
                }
                if (e_nova)
                    res.push_back(*it);
                e_nova = true;
            }
            contador++;
        }
    }
    return res;
}
