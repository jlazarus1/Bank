//
// Created by josh on 20/05/2020.
//

#include <algorithm>
#include "ATM.h"

#include <iostream>
#include <fstream>
#include <utility>

ATM::ATM(int ID) {
    ATMId = ID;
}
int ATM::getATMId() const {return ATMId;}

void ATM::openAccount(Bank* bank, int id, int accountNum, string password, int initSum) {

    auto* newAccount = new BankAccount(accountNum,std::move(password),initSum);
    bank->addAccount(newAccount,id);

}

void ATM::deposit(Bank* bank, int id, int accountNum, string password, int amount){

    bank->deposit(accountNum,password,amount,id);

    }

    void ATM::withdraw(Bank *bank, int ATMId, int accountNum, string password, int amount) {

    bank->withdraw(accountNum,password,amount,ATMId);

    }



    void ATM::closeAccount(Bank *bank, int ATMId, int accountNum, string password) {

    bank->removeAccount(accountNum,ATMId);

}

void ATM::viewBalance(Bank *bank, int ATMId, int accountNum, string password) {
    bank->balanceCheck(accountNum,password,ATMId);
}

void ATM::transferToAccount(Bank *bank, int ATMId, int accountNum, string password, int targetAccount, int amount) {

    bank->transfer(accountNum,password,targetAccount,amount,ATMId);
}






