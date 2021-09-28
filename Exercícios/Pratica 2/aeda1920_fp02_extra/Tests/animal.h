
#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinario.h"
#include <string>
using namespace std;


class Animal {
private:
    static int maisJovem;
protected:
	string nome;
	int idade;
	Veterinario *vet;
public:
	Animal(string nome, int idade);
	virtual ~Animal(){};
	string getNome() const;
    static int getMaisJovem() { return maisJovem; };
    virtual bool eJovem() const = 0;
    virtual string getInformacao() const;
	//completar
};

class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
    bool eJovem() const;
    string getInformacao() const;
    //completar
};

class Voador {
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
    virtual ~Voador(){};
    virtual string getInformacao() const;
	//completar
};


class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
    bool eJovem() const;
    string getInformacao() const;
    //completar
};


#endif /* SRC_ANIMAL_H_ */
