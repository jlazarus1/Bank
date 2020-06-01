//
// Created by josh on 22/05/2020.
//

#ifndef BANK_BANK_H
#define BANK_BANK_H
#include "BankAccount.h"
#include <list>
#include<map>


class Bank
{
private:
    /* Here will be the instance stored. */
    static Bank* instance;
    map<int , BankAccount*> accounts;
    int account0;
    int bankReaders;
    int numOfATMs;
    pthread_mutex_t  logLock;
    pthread_mutex_t  readLock;
    pthread_mutex_t writeLock;
    pthread_mutex_t atmsLock;





    /* Private constructor to prevent instancing. */
    Bank(int numOfATMS);

public:
    /* Static access method. */
    static Bank* getInstance(int numOfATMs);
    void addAccount(int accountNum, string password, int initSum,int atmId);
    void getCommission();
    void deposit(int accountNum, string pass, int amount,int atmId);
    void withdraw(int accountNum, string pass, int amount,int atmId);
    void balanceCheck(int accountNum, string pass,int atmId);
    void transfer(int accountNum, string pass, int targetAcc, int amount,int atmId);
    void removeAccount(int accountNum,int atmId); // in implementing delete the lock
    void lockLog();
    void unlockLog();
    void lockBankRead();
    void unlockBankRead();
    void lockBankWrite();
    void unlockBankWrite();
    void printStatus();
    void lockATMs();
    void unlockATMs();
    void reduceATM();
    int getNumATMs();
    void deleteAccounts();
    ~Bank();
};

#endif //BANK_BANK_H
