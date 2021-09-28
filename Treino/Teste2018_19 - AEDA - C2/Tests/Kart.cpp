#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}

bool CompararKarts(CKart c1, CKart c2)
{
    if (c1.getNumero() < c2.getNumero())
        return true;
    return false;
}

//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord, frota_pista;
	vector<CPista>::iterator itp;
	vector<CKart>::iterator itk;
	for (itp = pistasG.begin(); itp != pistasG.end() ; itp++) {
	    frota_pista = (*itp).getFrotaActual();
	    for (itk = frota_pista.begin() ; itk != frota_pista.end() ; itk++) {
	        vord.push_back(*itk);
	    }
	}
	sort(vord.begin(),vord.end(),CompararKarts);
	return vord;
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    vector <CKart> carts_avariados, res;
    for (auto &p : pistasG) {
        carts_avariados = p.getKartsAvariados();
        for (auto &a : carts_avariados) {
            if (a.getCilindrada() == cilind)
                res.push_back(a);
        }
    }
    return res.size();
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    for (auto &k : frotaKartsPista) {
        if (!k.getAvariado() && k.getCilindrada() == cilind) {
            kartsLinhaPartida.push(k);
            numeroKarts--;
            if (numeroKarts == 0) break;
        }
    }
    if (kartsLinhaPartida.size() < numeroKarts)
        return false;
    return true;
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    while (kartsLinhaPartida.size() > 0) {
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}

