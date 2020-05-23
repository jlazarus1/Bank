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
    accNum = account.getAccountNum();
    if (!(this->accounts.count(accNum)))
    {
        this->accounts.insert(accNum, account);
        pthread_mutex_t lock;
        tmp = pthread_mutex_init(&lock, nullptr); //return 0 upon success
        this->locks.insert(accNum, &lock)
    }
    else
    {
        //TODO implement error massage for existing account number
    }



}

Bank::Bank()
{}
