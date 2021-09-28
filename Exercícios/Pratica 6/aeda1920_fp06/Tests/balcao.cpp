#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar
Cliente::Cliente() {
    numPresentes = rand()%5 + 1;
}

//a alterar
int Cliente::getNumPresentes() const {
    return numPresentes;
}

//a alterar
Balcao::Balcao(int te): tempo_embrulho(te) {
    tempo_atual = 0;
    prox_chegada = rand()%20 + 1;
    prox_saida = 0;
    clientes_atendidos = 0;
}

//a alterar
void Balcao:: proximoEvento()
{
    if (clientes.empty()) {
        tempo_atual = prox_chegada;
        chegada();
    }
    else {
        if (prox_chegada < prox_saida) {
            tempo_atual = prox_chegada;
            chegada();
        } else {
            tempo_atual = prox_saida;
            saida();
        }
    }
}

//a alterar
void Balcao::chegada()
{
    Cliente c;
    prox_chegada = tempo_atual + (rand()%20 + 1);
    if (clientes.empty())
        prox_saida = tempo_atual + c.getNumPresentes()*tempo_embrulho;
    clientes.push(c);
    cout << "tempo= " << tempo_atual << "\nchegou novo cliente com " << c.getNumPresentes() << " presentes" << endl;
}

//a alterar
void Balcao::saida()
{
    Cliente c = getProxCliente();
    clientes.pop();
    cout << "tempo = " << tempo_atual << endl;
    cout << "cliente atendido: " << c.getNumPresentes() << " presentes" << endl;
    clientes_atendidos++;
    if (clientes.empty())
        prox_saida = tempo_atual + clientes.front().getNumPresentes()*tempo_embrulho;
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
ostream & operator << (ostream & out, const Balcao & b1)
{
     out << "numero de clientes atendidos: " << b1.clientes_atendidos << endl;
     out << "numero de clientes em espera: " << b1.clientes.size() << endl << endl;
     return out;
}

//a alterar
int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

//a alterar
int Balcao::getProxSaida() const {
	return prox_saida;
}

//a alterar
int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

//a alterar
Cliente & Balcao::getProxCliente() {
    if (clientes.empty())
        throw FilaVazia();
    Cliente *c = new Cliente();
    *c = clientes.front();
    return *c;
}

      
