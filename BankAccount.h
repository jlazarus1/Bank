//
// Created by josh on 20/05/2020.
//

#include <string>
#include <iostream>

#ifndef BANK_BANKACCOUNT_H
#define BANK_BANKACCOUNT_H

using namespace std;

class BankAccount {
private:
    int AccountNum;
    string Password;
    int Balance;
    pthread_mutex_t accountReadLock;
    pthread_mutex_t accountWriteLock;
    int numOfReaders;

public:
    BankAccount(int account, string password, int initSum);
    //TODO implement these functions

    int getAccountNum();
    int getBalance();
    int commission(double percent);
    string getPassword();
    void setBalance(int newBalance);
    void deposit(int amount);
    bool withdraw(int amount);
   bool transfer(BankAccount* target, int amount);
    bool checkPassword(string pass);
    void lockReadAccount();
    void unlockReadAccount();
    void lockWriteAccount();
    void unlockWriteAccount();
    void print();
     ~BankAccount();
};


#endif //BANK_BANKACCOUNT_H
