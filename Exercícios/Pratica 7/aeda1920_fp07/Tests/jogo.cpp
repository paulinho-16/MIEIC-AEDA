#include "jogo.h"
#include <sstream>


//a alterar
ostream &operator << (ostream &os, Circulo &c1)
{
	return os;
}

BinaryTree<Circulo> Jogo::inicia_jogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados) {
    Circulo c1(pontos[pos],estados[pos]);
    if (niv == 0)
        return BinaryTree<Circulo>(c1);
    BinaryTree<Circulo> filho_esquerdo = inicia_jogo(2*pos+1,niv-1,pontos,estados);
    BinaryTree<Circulo> filho_direito = inicia_jogo(2*pos+2,niv-1,pontos,estados);
    return BinaryTree<Circulo>(c1,filho_esquerdo,filho_direito);
}

//a alterar
Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
    jogo = inicia_jogo(0,niv,pontos,estados);
}

//a alterar
string Jogo::escreveJogo()
{
    BTItrLevel<Circulo> it(jogo);
    stringstream jogoStr("");
    string boleano;
    while (!it.isAtEnd()) {
        if (it.retrieve().getEstado()) boleano = "true";
        else boleano = "false";
        jogoStr << it.retrieve().getPontuacao() << "-" << boleano << "-" << it.retrieve().getNVisitas() << "\n";
        it.advance();
    }
    return jogoStr.str();
}

//a alterar
int Jogo::jogada()
{
    int n, pos = 1, pontos;
	BTItrLevel<Circulo> it(jogo);
	while (!it.isAtEnd()) {
	    Circulo &c1 = it.retrieve();
	    if (c1.getEstado()) n = pos+1;
	    else n = pos;
	    c1.mudaEstado();
	    c1.incNVisitas();
	    pontos = c1.getPontuacao();
	    int i = 0;
        while (i<n && !it.isAtEnd()) {
            it.advance();
            i++;
        }
        if (!it.isAtEnd())
	        pos += n;
	}
    return pontos;
}


//a alterar
int Jogo::maisVisitado()
{
    BTItrLevel<Circulo> it(jogo);
    if (it.isAtEnd()) return -1;
    int maisV = -1;
    it.advance();
    while (!it.isAtEnd()) {
        Circulo &c1 = it.retrieve();
        if (c1.getNVisitas() > maisV)
            maisV = c1.getNVisitas();
        it.advance();
    }
    return maisV;
}

