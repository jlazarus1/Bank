//
// Created by josh on 22/05/2020.
//

#ifndef BANK_BANK_H
#define BANK_BANK_H
#include "BankAccount.h"
#include <list>

class Bank
{
private:
    /* Here will be the instance stored. */
    static Bank* instance;
    map<int , BankAccount*> accounts;
    BankAccount* bankAccount;
    pthread_mutex_t account_lock_for_removing;

    /* Private constructor to prevent instancing. */
    Bank();

public:
    /* Static access method. */
    static Bank* getInstance();
    void addItem(BankAccount account);
    void getCommission()
    BankAccount* getAccount(int accountNum);
    void removeAccount(int accountNum)
};

#endif //BANK_BANK_H
