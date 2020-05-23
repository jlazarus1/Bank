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
    map<int , pthread_mutex_t*> locks
    BankAccount* bankAccount;

    /* Private constructor to prevent instancing. */
    Bank();

public:
    /* Static access method. */
    static Bank* getInstance();
    void addItem(BankAccount account);
    void getCommission()
    BankAccount* getAccount(int accountNum);  // in implementing lock the account
    void removeAccount(int accountNum); // in implementing delete the lock
};

#endif //BANK_BANK_H
