/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const
{
    double result = 0;
    for (unsigned int i = 0 ; i < accounts.size() ; i++)
    {
        if (accounts[i]->getCodH() == cod1)
        {
            result += accounts[i]->getWithdraw();
        }
    }
	return result;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name)
{
	vector<Account *> res;
	for (unsigned int i = 0 ; i < bankOfficers.size() ; i++)
    {
	    if (bankOfficers[i].getName() == name)
        {
	        res = bankOfficers[i].getAccounts();
	        bankOfficers.erase(bankOfficers.begin() + i);
        }
    }
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    BankOfficer *bo= new BankOfficer();
    bool Encontrou = false;
    for (unsigned int i = 0 ; i<bankOfficers.size() ; i++)
    {
        if (bankOfficers[i].getName() == name)
        {
            Encontrou = true;
            bankOfficers[i].addAccount(ac);
            *bo = bankOfficers[i];
        }
    }
    if (!Encontrou)
        throw NoBankOfficerException(name);
    return *bo;
}

bool CompararAccounts(Account *ac1, Account *ac2)
{
    if (ac1->getBalance() < ac2->getBalance())
        return true;
    else if (ac1->getBalance() == ac2->getBalance())
        return (ac1->getCodIBAN() < ac2->getCodIBAN());
    else
        return false;
}

// a alterar
void Bank::sortAccounts()
{
    sort(accounts.begin(),accounts.end(),CompararAccounts);
}

