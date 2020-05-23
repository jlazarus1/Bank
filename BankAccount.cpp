//
// Created by josh on 20/05/2020.
//

#include "BankAccount.h"

BankAccount::BankAccount(int account, string password, int initSum) {
    this->AccountNum = account;
    this->Password = password;
    this->Balance = initSum;
}

int BankAccount::getAccountNum() {return this->AccountNum}

int BankAccount::getBalance() {return this->Balance}

string BankAccount::getPassword() {return this->Password}

void BankAccount::setBalance(int newBalance) {
    this->Balance = newBalance;
}


void BankAccount::deposit(int amount, string password) {
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
}


void BankAccount::withdraw(int amount, string password) {
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
}


void BankAccount::transfer(string password, BankAccount target, int amount) {

    // waiting for answer from the HW forum


    sleep(1);
}