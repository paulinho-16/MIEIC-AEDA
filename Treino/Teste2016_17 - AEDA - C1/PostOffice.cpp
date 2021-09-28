/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name)
{
    vector<Mail *> correspondencia;
    vector<Postman>::iterator it;
    for (it = postmen.begin() ; it != postmen.end() ; it++)
    {
        if ((*it).getName() == name)
        {
            correspondencia = (*it).getMail();
            postmen.erase(it);
            break;
        }
    }
    return correspondencia;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance)
{
    vector<Mail *>::iterator it;
    vector<Mail *> result;
    balance = 0;
    for (it = mailToSend.begin() ; it != mailToSend.end() ; it++)
    {
        balance += (*it)->getPrice();
        if ((*it)->getZipCode() >= firstZipCode && (*it)->getZipCode() <= lastZipCode)
        {
            addMailToDeliver(*it);
        }
        else
        {
            result.push_back(*it);
        }
    }
    mailToSend.clear();
    return result;
}

Postman PostOffice::addMailToPostman(Mail *m, string name)
{
    vector<Postman>::iterator it;
    for (it = postmen.begin() ; it != postmen.end() ; it++)
    {
        if ((*it).getName() == name)
        {
            (*it).addMail(m);
            return *it;
        }
    }
    throw NoPostmanException(name);
}
