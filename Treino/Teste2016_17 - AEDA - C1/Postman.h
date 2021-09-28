/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>

class Postman {
	unsigned int id;
	string name;
	vector<Mail *> myMail;
public:
	Postman();
    Postman(string name);
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	static unsigned int ultimo_id;
	bool operator<(const Postman &p2);
};

template<class T>
bool NoVetor(const vector<T> & v1, const T &elemento)
{
    for (unsigned int i = 0 ; i<v1.size(); i++)
    {
        if (elemento == v1[i])
            return true;
    }
    return false;
}

template<class T>
unsigned int numberDifferent (const vector<T> & v1)
{
    unsigned int contador = 0;
    vector<T> temp;
    for (unsigned int i = 0 ; i < v1.size() ; i++)
    {
        if (!NoVetor(temp,v1[i]))
        {
            temp.push_back(v1[i]);
            contador++;
        }
    }
    return contador;
}

#endif /* SRC_POSTMAN_H_ */
