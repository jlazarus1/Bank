//
// Created by josh on 20/05/2020.
//

#include <algorithm>
#include "ATM.h"
#include "BankAccount.h"
#include <iostream>
#include <fstream>

ATM::ATM(int ID) {
    ATMId = ID;
}
int ATM::getATMId() const {return ATMId;}

void ATM::openAccount(Bank* bank, int ATMId, int accountNum, string password, int initSum) {
    //open the log.txt file
    ofstream log("log.txt");
    list<BankAccount>::iterator it;
    BankAccount newAccount(accountNum,password,initSum);
 //   it = find(accounts.begin(),accounts.end(),newAccount);
//    if (it == accounts.end())
//    {
//        log<<"Error "<<ATMId <<" : Your transaction failed – account with the same id exists\n";
//    }
//    else {
//TODO find if the account exists or not.
// TODO add mutex to guard adding item to the bank.
     bank->addItem(newAccount);
     cout<<ATMId<<"\n";

//    }


}


