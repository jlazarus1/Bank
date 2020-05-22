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

public:
    BankAccount(int account, string password, int initSum);
    //TODO implement these functions
    void setAccountNum(int num);
    void setPassword(string password);
    void transaction(int sum,string action);

    int getAccountNum();
    int getBalance();


};


#endif //BANK_BANKACCOUNT_H
