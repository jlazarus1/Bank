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
    void openAccount(Bank* bank, int ATMId,  int accountNum, string password, int initSum);
    void deposit(Bank* bank, int ATMId, int accountNum, string password, int amount);
    void withdraw(Bank* bank, int ATMId, int accountNum, string password, int amount);
    void viewBalance(Bank* bank, int ATMId,int accountNum, string password);
    void closeAccount(Bank* bank, int ATMId,int accountNum, string password);
    void transferToAccount(Bank* bank, int ATMId, int accountNum, string password, int targetAccount, int amount);
    int getATMId() const;
};


#endif //BANK_ATM_H
