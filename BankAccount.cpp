//
// Created by josh on 20/05/2020.
//

#include "BankAccount.h"

BankAccount::BankAccount(int account, string password, int initSum) {
    this->AccountNum = account;
    this->Password = password;
    this->Balance = initSum;
    tmp = pthread_mutex_init(&this->account_lock, nullptr) //return 0 upon success
}

int BankAccount::getAccountNum() {return this->AccountNum}

int BankAccount::getBalance() {return this->Balance}

string BankAccount::getPassword() {return this->Password}

void BankAccount::setBalance(int newBalance) {
    this->Balance = newBalance;
}


void BankAccount::deposit(int amount, string password) {
    tmp = pthread_mutex_lock(&this->account_lock);
    accPass = getPassword();
    if (!(strcmp(accPass, password))){
        currBal = this.getBalance();
        this.setBalance(currBal + amount);
        //TODO add success massage to log
    }
    else{
        //TODO implement error massage for wrong password
    }
    sleep(1);
    tmp = pthread_mutex_unlock(&this->account_lock);
}


void BankAccount::withdraw(int amount, string password) {
    tmp = pthread_mutex_lock(&this->account_lock);
    accPass = getPassword();
    if (!(strcmp(accPass, password))){
        currBal = this->getBalance();
        if (amount > currBal){
            //TODO implement error massage for low balance
        }
        else{
            this.setBalance(currBal - amount);
            //TODO add success massage to log
        }
    }
    else{
        //TODO implement error massage for wrong password
    }
    sleep(1);
    tmp = pthread_mutex_unlock(&this->account_lock);
}


void BankAccount::transfer(string password, BankAccount target, int amount) {
    tmp = pthread_mutex_lock(&this->account_lock);

    // waiting for answer from the HW forum


    sleep(1);
    tmp = pthread_mutex_unlock(&this->account_lock);
}


void BankAccount::closeAccount(string password) {
    accPass = getPassword();
    if (!(strcmp(accPass, password))){
        tmp = pthread_muted_destroy(&this->closeAccount());
    }
    else{
        //TODO implement error massage for wrong password
    }
}