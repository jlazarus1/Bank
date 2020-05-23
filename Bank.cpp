//
// Created by josh on 22/05/2020.
//

#include "Bank.h"

Bank* Bank::instance = 0;

Bank* Bank::getInstance()
{
    if (instance == 0)
    {
        instance = new Bank();
    }

    return instance;
}

void Bank::addItem(BankAccount account) {
    if (!(this->accounts.count(account.getAccountNum())))
    {
        this->accounts.insert(account.getAccountNum(), account);
    }
    else
    {
        //TODO implement error massage for existing account number
    }



}

Bank::Bank()
{}
