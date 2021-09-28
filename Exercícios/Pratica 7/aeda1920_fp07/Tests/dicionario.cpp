#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//a alterar
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     if (palavra < ps1.palavra)
         return true;
     return false;
}

bool PalavraSignificado::operator==(const PalavraSignificado &ps1) const {
    if (palavra == ps1.palavra)
        return true;
    return false;
}

//a alterar
void Dicionario::lerDicionario(ifstream &fich)
{
    string palavra, significado;
    while (!fich.eof()) {
        getline(fich,palavra);
        getline(fich, significado);
        PalavraSignificado p1(palavra, significado);
        palavras.insert(p1);
    }
}

//a alterar
string Dicionario::consulta(string palavra) const
{
    PalavraSignificado p1(palavra,"");
    PalavraSignificado p_temp("","");
    PalavraSignificado result = palavras.find(p1);
    if (result == p_temp) {
        BSTItrIn<PalavraSignificado> it(palavras);
        string p_antes = "", s_antes = "";
        while (!it.isAtEnd() && it.retrieve() < p1) {
            p_antes = it.retrieve().getPalavra();
            s_antes = it.retrieve().getSignificado();
            it.advance();
        }
        string p_apos = "", s_apos = "";
        if (!it.isAtEnd()) {
            p_apos = it.retrieve().getPalavra();
            s_apos = it.retrieve().getSignificado();
        }
        throw PalavraNaoExiste(p_antes,s_antes,p_apos,s_apos);
    }
    return result.getSignificado();
}

//a alterar
bool Dicionario::corrige(string palavra, string significado)
{
    PalavraSignificado aux(palavra,significado);
    PalavraSignificado p_temp("","");
    PalavraSignificado pal = palavras.find(aux);
    if (pal == p_temp) {
        palavras.insert(aux);
        return false;
    }
    else {
        palavras.remove(pal);
        palavras.insert(aux);
        return true;
    }
}

//a alterar
void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    while(!it.isAtEnd()) {
        cout << it.retrieve().getPalavra() << endl << it.retrieve().getSignificado() << endl;
        it.advance();
    }
    cout << "\noutra forma: \n";
    iteratorBST<PalavraSignificado> it2 = palavras.begin();
    while (it2!=palavras.end()) {
        cout << (*it2).getPalavra() << endl << (*it2).getSignificado() << endl;
        it2++;
    }
}

