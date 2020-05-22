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
    list<BankAccount> accounts;

    /* Private constructor to prevent instancing. */
    Bank();

public:
    /* Static access method. */
    static Bank* getInstance();
  void addItem(BankAccount account);
};

#endif //BANK_BANK_H
