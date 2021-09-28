/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::ultimo_id = 1;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string nm)
{
    this->name = nm;
    this->id = ultimo_id;
    ultimo_id++;
}

bool BankOfficer::operator>(const BankOfficer &b2)
{
    if (myAccounts.size() > b2.myAccounts.size())
        return true;
    else if (myAccounts.size() == b2.myAccounts.size())
        return (name > b2.name);
    else
        return false;
}


