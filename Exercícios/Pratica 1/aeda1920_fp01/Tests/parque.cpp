#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli)
{
    vagas = lotacao;
    clientes.clear();
}

unsigned int ParqueEstacionamento::getNumLugares() const
{
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    for(size_t i = 0;i<clientes.size();i++)
    {
        if(clientes[i].nome == nome)
            return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome)
{
    if (clientes.size() + 1 <= numMaximoClientes)
    {
        InfoCartao novo_cliente;
        novo_cliente.nome = nome;
        novo_cliente.presente = false;
        clientes.push_back(novo_cliente);
        return true;
    }
    return false;
}

bool ParqueEstacionamento::entrar(const string &nome)
{
    if (vagas == 0)
        return false;
    if(posicaoCliente(nome) == -1)
        return false;
    else
    {
        if(clientes[posicaoCliente(nome)].presente == true)
            return false;
    }
    vagas--;
    clientes[posicaoCliente(nome)].presente = true;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string &nome)
{
    if(posicaoCliente(nome) == -1)
        return false;
    if(clientes[posicaoCliente(nome)].presente == true)
        return false;
    clientes.erase(clientes.begin() + posicaoCliente(nome));
    return true;
}

bool ParqueEstacionamento::sair(const string &nome)
{
    if (posicaoCliente(nome) == -1)
        return false;
    if (clientes[posicaoCliente(nome)].presente == false)
        return false;
    clientes[posicaoCliente(nome)].presente = false;
    vagas++;
    return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
    return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const
{
    return clientes.size();
}