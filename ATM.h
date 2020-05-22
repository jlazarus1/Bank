//
// Created by josh on 20/05/2020.
//

#ifndef BANK_ATM_H
#define BANK_ATM_H
#include "BankAccount.h"
#include "Bank.h"

class ATM {
private:
    int ATMId;

public:
    explicit ATM(int ID);
    void openAccount(Bank* bank,int ATMId,  int accountNum, string password, int initSum);
    //TODO implement all these
    //TODO add mutexes to these
    void deposit(int accountNum, string password, int amount);
    void withdraw(int accountNum, string password, int amount);
    void viewBalance(int accountNum, string password);
    void closeAccount(int accountNum, string password);
    void transferToAccount(int accountNum, string password, int targetAccount, int amount);
    int getATMId() const;
};


#endif //BANK_ATM_H
