//
// Created by josh on 20/05/2020.
//

#include <string>;

#ifndef BANK_BANKACCOUNT_H
#define BANK_BANKACCOUNT_H

using namespace std;

class BankAccount {
private:
    int AccountNum;
    string Password;
    int Balance;
    pthread_mutex_t account_lock;

public:
    BankAccount(int account, string password, int initSum);
    //TODO implement these functions

    int getAccountNum();
    int getBalance();
    string getPassword();
    void setBalance(int newBalance);
    void deposit(int amount, string password);
    void withdraw(int amount, string password);
    void closeAccount(string password) // remember to destroy mutex
    void transfer(string password, BankAccount target, int amount);

};


#endif //BANK_BANKACCOUNT_H
