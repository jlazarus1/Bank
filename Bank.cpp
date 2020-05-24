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
    tmp = pthread_mutex_lock(&this->enterLock));

    accNum = account.getAccountNum();
    if (!(this->accounts.count(accNum)))
    {
        this->accounts.insert({accNum, account});
        pthread_mutex_t lock;
        tmp = pthread_mutex_init(&lock, nullptr); //return 0 upon success
        this->locks.insert({accNum, &lock})
    }
    else
    {
        //TODO implement error massage for existing account number
    }
    tmp = pthread_mutex_unlock(&this->enterLock));
}

Bank::Bank() {
    tmp = pthread_mutex_init(&this->enterLock, nullptr);
}

bool Bank::enterAccount(int accountNum) {

    auto itr_lock = this->locks.find(accountNum);
    if (itr_lock != this->locks.end()){
        tmp = pthread_mutex_lock(&(itr_lock->second));
        return true
    }
    else {
        // TODO implement error massage for account not exist
        return false
    }
}

void Bank::exitAccount(int accountNum) {
    auto itr_lock = this->locks.find(accountNum);
    if (itr_lock != this->locks.end()){
        tmp = pthread_mutex_unlock(&(itr_lock->second));
    }
    else {
        // TODO implement error massage for account not exist (not suppose to happen)
    }
}

void Bank::deposit(int accountNum, string pass, int amount) {
    tmp = pthread_mutex_lock(&this->enterLock));
    tmp = pthread_mutex_unlock(&this->enterLock));

    if (!(this->enterAccount(accountNum))) {
        return;
    }
    itr_acc = this->accounts.find(accountNum);
    if (itr_acc == this->accounts.end()){
        // TODO implement error massage for account not exist
        return;
    }
    else {
        itr_acc->second.deposit(amount, pass);
        sleep(1);
        this->exitAccount(accountNum);
        return;
    }
}


void Bank::removeAccount(int accountNum) {
    tmp = pthread_mutex_lock(&this->enterLock));

    if (!(this->enterAccount(accountNum))) {
        tmp = pthread_mutex_unlock(&this->enterLock));
        return;
    }
    else {
        this->exitAccount(accountNum);
        itr_lock = this->locks(accountNum);
        tmp = pthread_mutex_destroy(&itr_lock->second);
        this->locks.erase(accountNum);
        this->accounts.erase(accountNum);
    }
    tmp = pthread_mutex_unlock(&this->enterLock));
}


void Bank::withdraw(int accountNum, string pass, int amount) {
    tmp = pthread_mutex_lock(&this->enterLock));
    tmp = pthread_mutex_unlock(&this->enterLock));

    if (!(this->enterAccount(accountNum))) {
        return;
    }
    itr_acc = this->accounts.find(accountNum);
    if (itr_acc == this->accounts.end()){
        // TODO implement error massage for account not exist
        return;
    }
    else {
        itr_acc->second.withdraw(amount, pass);
        sleep(1);
        this->exitAccount(accountNum);
        return;
    }
}


void Bank::balanceCheck(int accountNum, string pass) {
    tmp = pthread_mutex_lock(&this->enterLock));
    tmp = pthread_mutex_unlock(&this->enterLock));

    if (!(this->enterAccount(accountNum))) {
        return;
    }
    itr_acc = this->accounts.find(accountNum);
    if (itr_acc == this->accounts.end()){
        // TODO implement error massage for account not exist
        return;
    }
    else {
        itr_acc->second.balanceCheck();
        sleep(1);
        this->exitAccount(accountNum);
        return;
    }
}


void Bank::transfer(int accountNum, string pass, int targetAcc, int amount) {
    tmp = pthread_mutex_lock(&this->enterLock));
    tmp = pthread_mutex_unlock(&this->enterLock));

    if (!(this->enterAccount(accountNum))) {
        return;
    }
    itr_acc = this->accounts.find(accountNum);
    if (itr_acc == this->accounts.end()){
        // TODO implement error massage for account not exist
        return;
    }
    else {
        itr_acc->second.transfer(pass, targetAcc, amount);
        sleep(1);
        this->exitAccount(accountNum);
        return;
    }
}
