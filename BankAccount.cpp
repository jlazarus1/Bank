//
// Created by josh on 20/05/2020.
//

#include "BankAccount.h"

BankAccount::BankAccount(int account, string password, int initSum) {
    this->AccountNum = account;
    this->Password = password;
    this->Balance = initSum;
}