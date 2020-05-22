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
    this->accounts.push_front(account);


}

Bank::Bank()
{}
