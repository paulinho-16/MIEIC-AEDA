/*
 * Postman.cpp
 */
#include "Postman.h"

unsigned int Postman::ultimo_id = 1;

Postman::Postman(): id(0) {}

Postman::Postman(string name)
{
    this->name = name;
    id = ultimo_id;
    ultimo_id++;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman &p2)
{
    vector<string> ZipCodes1, ZipCodes2;
    for (unsigned int i = 0 ; i < myMail.size() ; i++)
    {
        ZipCodes1.push_back(myMail[i]->getZipCode());
    }
    for (unsigned int i = 0 ; i < (p2.getMail()).size() ; i++)
    {
        ZipCodes2.push_back(p2.getMail()[i]->getZipCode());
    }
    return numberDifferent(ZipCodes1) < numberDifferent(ZipCodes2);
}


