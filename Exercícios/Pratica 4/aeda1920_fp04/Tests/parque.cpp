#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;

bool InfoCartao::operator==(const InfoCartao &inf2) const
{
    if (nome == inf2.nome) return true;
    return false;
}

bool InfoCartao::operator<(const InfoCartao &inf2) const
{
    if (frequencia < inf2.frequencia) return false;
    else if (frequencia > inf2.frequencia) return true;
    else return (nome < inf2.nome);
}

bool CompararNomes (const InfoCartao &inf1, const InfoCartao &inf2)
{
    return inf1.nome < inf2.nome;
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a imnplementar
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    InfoCartao inf;
    inf.nome = nome;
    return sequentialSearch(clientes,inf);
}

//a implementar
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);
    if (pos == -1) throw ClienteNaoExistente(nome);
    return clientes[pos].frequencia;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}


// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    sort(clientes.begin(), clientes.end(), CompararNomes);
}


// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    ordenaClientesPorFrequencia();
    vector<string> nomes;
    for (unsigned int i = 0 ; i<clientes.size() ; i++)
    {
        if (clientes[i].frequencia >= n1 && clientes[i].frequencia <= n2)
            nomes.push_back(clientes[i].nome);
    }
    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
        for (unsigned int i = 0;i<pe.clientes.size();i++)
        {
            os << "Nome: " << pe.clientes[i].nome << "\tPresente: " << pe.clientes[i].presente << "\tNumero de utilizacoes: " << pe.clientes[i].frequencia << endl;
        }
        return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;
    if (p >= clientes.size()) throw PosicaoNaoExistente(p);
    info = clientes[p];
    return info;
}
