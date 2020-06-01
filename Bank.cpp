//
// Created by josh on 22/05/2020.
//

#include <unistd.h>
#include "Bank.h"
#include <iostream>
#include <fstream>


Bank* Bank::instance = 0;

Bank* Bank::getInstance(int numOfATMs)
{
    if (instance == 0)
    {
        instance = new Bank(numOfATMs);
    }

    return instance;
}

void Bank::addAccount(int accountNum, string password, int initSum,int atmId) {
    lockBankWrite();
    ofstream log;
    log.open("log.txt",fstream::out | fstream ::app);
    BankAccount* acc = new BankAccount(accountNum,password,initSum);

    int accNum = acc->getAccountNum();
    //account does not exist
    if (!(this->accounts.count(accNum)))
    {
        sleep(1);
        lockLog();
        log<<atmId<<": New account id is "<< acc->getAccountNum()<<" with password "<<acc->getPassword()<<" and initial balance "<<acc->getBalance()<<"\n";
        unlockLog();
        this->accounts.insert({accNum, acc});
    }
    else
    {
        //account is in the bank already
        sleep(1);
        delete acc;
       lockLog();
       log<<"Error "<<atmId<<": your transaction failed - account with the same id exists\n";
       unlockLog();
    }
   unlockBankWrite();
}

Bank::Bank(int numOfATMs) {
  pthread_mutex_init(&this->writeLock, nullptr);
  pthread_mutex_init(&this->readLock, nullptr);
  pthread_mutex_init(&this->logLock, nullptr);
  pthread_mutex_init(&this->atmsLock, nullptr);
  bankReaders=0;
  account0 = 0;
  this->numOfATMs=numOfATMs;
}





void Bank::deposit(int accountNum, string pass, int amount, int atmId) {
    lockBankRead();
    ofstream log;
    log.open("log.txt",fstream::out | fstream ::app);
    auto itr_acc = this->accounts.find(accountNum);
    //no such account
    if (itr_acc == this->accounts.end()){
        sleep(1);
        lockLog();
        log<<"Error "<<atmId<<": Your transaction failed - account id "<<accountNum<<" does not exist\n";
        unlockLog();
        unlockBankRead();
        return;
    }
    else {
        //check password, if wrong
        if (!itr_acc->second->checkPassword(pass))
        {
            sleep(1);
            lockLog();
            log<<"Error "<<atmId<<": Your transaction failed - password for account id "<<accountNum<< " is incorrect\n";
            unlockLog();
            unlockBankRead();
            return;
        }
        //if password correct, deposit
        sleep(1);
        itr_acc->second->deposit(amount);
        //lock log for writing to log
        lockLog();
        log<<atmId<<": Account "<<accountNum<<" new balance is "<<itr_acc->second->getBalance()<<" after "<<amount<<"$ was deposited\n";
        unlockLog();

        unlockBankRead();
        return;
    }
}


void Bank::removeAccount(int accountNum,int atmId) {
    lockBankWrite();
    ofstream log;
    log.open("log.txt",fstream::out | fstream ::app);
    //account exists
    if ((this->accounts.count(accountNum)))
    {
        sleep(1);
        map<int,BankAccount*>::iterator it;
        it= accounts.find(accountNum);
        auto acc_it = accounts.find(accountNum);
        BankAccount* acc = acc_it->second;
        this->accounts.erase(it);
        acc->~BankAccount();
        delete(acc);
        lockLog();
        log<<atmId<<": account id "<<accountNum<<" was removed\n";
        unlockLog();
        unlockBankWrite();
        return;
    }
    //account does not exist
    else
    {
        sleep(1);
        lockLog();
        log<<"Error "<<atmId<<": Your transaction failed - account id "<<accountNum<<" does not exist\n";
        unlockLog();
        unlockBankWrite();
        return;
    }

}


void Bank::withdraw(int accountNum, string pass, int amount,int atmId) {
   lockBankRead();
    ofstream log;
    log.open("log.txt",fstream::out | fstream ::app);
    map<int,BankAccount*>::iterator itr_acc;
    //iterator to account in map
    itr_acc = accounts.find(accountNum);
    //account does not exist
    if (itr_acc == this->accounts.end()){
        lockLog();
        log<<"Error "<<atmId<<": Your transaction failed - account id "<<accountNum<<" does not exist\n";
        unlockLog();
        unlockBankRead();
        return;
    }
    //account exists
    else {

        //wrong password
        if (!itr_acc->second->checkPassword(pass))
            {
            lockLog();
            log<<"Error "<<atmId<<": Your transaction failed - password for account id "<<accountNum<<" is incorrect\n";
            unlockLog();
            unlockBankRead();
            return;
            }
        //correct password
        else{
            //return value from withdraw was false - the transaction failed due to not enough money
          if (!itr_acc->second->withdraw(amount)){
              lockLog();
              log<<"Error "<<atmId<<": Your transaction failed - account id "<<accountNum<<" balance is lower than "<<amount<<"\n";
              unlockLog();
              unlockBankRead();
              return;
          }
          else {
              //all went well with transaction
              lockLog();
              log<<atmId<<": Account "<<atmId<<" new balance is "<<itr_acc->second->getBalance()<<" after "<<amount<<"$ was withdrew\n";
              unlockLog();
              unlockBankRead();
              return;

          }

        }
    }
}


void Bank::balanceCheck(int accountNum, string pass,int atmId) {
    lockBankRead();
    ofstream log;
    log.open("log.txt",fstream::out | fstream ::app);
    auto itr_acc = this->accounts.find(accountNum);
    if (itr_acc == this->accounts.end()){
        lockLog();
        log<<"Error "<<atmId<<": Your transaction failed - account id "<<accountNum<<" does not exist\n";
        unlockLog();
        unlockBankRead();
        return;
    }
    else {
        sleep(1);
        //lock account for reading
        itr_acc->second->lockReadAccount();
        int bal = itr_acc->second->getBalance();
        //unlock after reading account
        itr_acc->second->unlockReadAccount();
       lockLog();
       log<<atmId<<" Account "<<accountNum<<" balance is "<<bal<<"\n";
       unlockLog();
       unlockBankRead();
       return;
    }
}


void Bank::transfer(int accountNum, string pass, int targetAcc, int amount,int atmId) {
    lockBankRead();
    ofstream log;
    log.open("log.txt",fstream::out | fstream ::app);
    auto itr_acc = this->accounts.find(accountNum);
    auto itr_target = this->accounts.find(targetAcc);
    if (itr_acc == this->accounts.end()){
        lockLog();
        log<<"Error "<<atmId<<": Your transaction failed - account id "<<accountNum<<" does not exist\n";
        unlockLog();
        unlockBankRead();
        return;
    }
    else if (itr_target==this->accounts.end()){
        lockLog();
        log<<"Error "<<atmId<<": Your transaction failed - account id "<<targetAcc<<" does not exist\n";
        unlockLog();
        unlockBankRead();
        return;
    }
    else {
        //wrong password
        if(!itr_acc->second->checkPassword(pass))
        {
            lockLog();
            log<<"Error "<<atmId<<": Your transaction failed - password for account id "<<accountNum<<" is incorrect\n";
            unlockLog();
            unlockBankRead();
            return;
        }
        else {
            //all is good, transfer to target
            itr_acc->second->transfer(itr_target->second,amount);
            lockLog();
            log<<atmId<<": Transfer "<<amount<<" from account "<<accountNum<<" to account "<<targetAcc<<" new account balance is "<<itr_acc->second->getBalance()<<" new target account balance is "<<itr_target->second->getBalance()<<"\n";
            unlockLog();
            unlockBankRead();
            return;
        }
    }
}

void Bank::getCommission() {
    lockBankRead();
    ofstream log;
    log.open("log.txt",fstream::out | fstream ::app);
    double commPercent;
    int commission;
    for (auto i=accounts.begin(); i!=accounts.end();i++){
        commPercent = (4-2) * ((double) random()/(double)RAND_MAX) + 2;
        commission = i->second->commission(commPercent);
        account0+=commission;
        lockLog();
        log<<"Bank: commissions of "<<commPercent<<"% were charged, the bank gained "<<commission<<"$ from account"<<i->second->getAccountNum()<<"\n";
        unlockLog();
    }
    unlockBankRead();

}

int Bank::getNumATMs() {
    return numOfATMs;
}

void Bank::reduceATM() {
    lockATMs();
    numOfATMs--;
    unlockATMs();
}


void Bank::printStatus() {

    lockBankRead();
    printf("\033[2J\033[1;1H");
    cout << "Current Bank Status\n";
    for(auto & account : accounts){
        account.second->print();
    }
    cout<<"The Bank has "<<this->account0<<"$\n";


    unlockBankRead();
}


void Bank::lockBankRead() {
    pthread_mutex_lock(&readLock);
    bankReaders++;
    if(bankReaders==1){
        pthread_mutex_lock(&writeLock);
    }
    pthread_mutex_unlock(&readLock);
}

void Bank::unlockBankRead() {
    pthread_mutex_lock(&readLock);
    bankReaders--;
    if(bankReaders==0){
        pthread_mutex_unlock(&writeLock);
    }
    pthread_mutex_unlock(&readLock);
}

void Bank::lockBankWrite() {
    pthread_mutex_lock(&writeLock);
}

void Bank::unlockBankWrite() {
    pthread_mutex_unlock(&writeLock);
}

void Bank::lockLog() {
    pthread_mutex_lock(&logLock);
}
void Bank::unlockLog() {
    pthread_mutex_unlock(&logLock);
}

void Bank::lockATMs() {
    pthread_mutex_lock(&atmsLock);
}
void Bank::unlockATMs() {
    pthread_mutex_unlock(&atmsLock);
}
void Bank::deleteAccounts() {
    map<int,BankAccount*>::iterator it;

    for (it=accounts.begin();it!=accounts.end();it++)
    {
        delete it->second;

    }
    accounts.clear();


}

Bank::~Bank()= default;
