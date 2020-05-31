//
// Created by josh on 20/05/2020.
//

#include <cstring>
#include "BankAccount.h"
#include <fstream>
#include <math.h>

BankAccount::BankAccount(int account, string password, int initSum) {
    pthread_mutex_init(&accountReadLock,NULL);
    pthread_mutex_init(&accountWriteLock,NULL);
    this->AccountNum = account;
    this->Password = password;
    this->Balance = initSum;
    numOfReaders=0;

}
BankAccount::~BankAccount() {

    pthread_mutex_destroy(&accountWriteLock);
    pthread_mutex_destroy(&accountReadLock);
}

int BankAccount::getAccountNum() {return this->AccountNum;}

int BankAccount::getBalance() {return this->Balance;}

string BankAccount::getPassword() {return this->Password;}

void BankAccount::setBalance(int newBalance) {
    this->Balance = newBalance;
}


void BankAccount::deposit(int amount) {
    lockWriteAccount();

        int currBal = this->getBalance();
        this->setBalance(currBal + amount);

    unlockWriteAccount();
    }



bool BankAccount::withdraw(int amount) {
lockWriteAccount();

    int currBal = this->getBalance();
    if (amount > currBal) {
        unlockWriteAccount();
        return false;
    } else {
        this->setBalance(currBal - amount);
        unlockWriteAccount();
        return true;
    }
}


bool BankAccount::transfer( BankAccount* target, int amount) {
lockWriteAccount();
target->lockWriteAccount();
int currBal = getBalance();
// not enough money to move to target
if (amount>currBal){
    unlockWriteAccount();
    //unlock target write
    target->unlockWriteAccount();
    return false;
}
else {
    int targetBal = target->getBalance();
    target->setBalance(targetBal+amount);
    setBalance(currBal-amount);
    unlockWriteAccount();
    target->unlockWriteAccount();
    return true;

}


}



bool BankAccount::checkPassword(string pass) {
    return Password == pass;

}
void BankAccount::lockReadAccount() {
    pthread_mutex_lock(&accountReadLock);
    numOfReaders++;
    if(numOfReaders==1){
        pthread_mutex_lock(&accountWriteLock);
    }
    pthread_mutex_unlock(&accountReadLock);
}

void BankAccount::unlockReadAccount() {
    pthread_mutex_lock(&accountReadLock);
    numOfReaders--;
    if(numOfReaders==0){
        pthread_mutex_unlock(&accountWriteLock);
    }
    pthread_mutex_unlock(&accountReadLock);
}

void BankAccount::lockWriteAccount() {
    pthread_mutex_lock(&accountWriteLock);
}
void BankAccount::unlockWriteAccount() {
    pthread_mutex_unlock(&accountWriteLock);
}

int BankAccount::commission(double percent) {
    lockWriteAccount();
    int commission = round((percent * (double)getBalance())/ 100.0);
    int bal = getBalance();
    setBalance(bal-commission);
    unlockWriteAccount();
    return commission;
}

void BankAccount::print(){
    lockReadAccount();
    cout<<"Account "<<getAccountNum()<<": Balance - "<<getBalance()<<"$ , Account password - "<<getPassword()<<"\n";
    unlockReadAccount();
    return;
}