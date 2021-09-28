#include "jogador.h"

//a alterar
void Jogador::adicionaAposta(const Aposta & ap)
{
    apostas.insert(ap);
}

//a alterar
unsigned Jogador::apostasNoNumero(unsigned num) const
{
    unsigned int vezes = 0;
    for (tabHAposta::const_iterator it = apostas.begin() ; it != apostas.end() ; it++) {
        if ((*it).contem(num))
            vezes++;
    }
	return vezes;
}

//a alterar
tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;
	for (tabHAposta::const_iterator it = apostas.begin() ; it != apostas.end() ; it++) {
	    if ((*it).calculaCertos(sorteio) > 3)
	        money.insert(*it);
	}
	return money;
}
