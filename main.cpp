#include <iostream>
#include <map>
#include "BankAccount.h"
#include "ATM.h"
#include "Bank.h"
#include <pthread.h>
#include <stdio.h>
#include <fstream>
#include <regex>
#include <unistd.h>
using namespace std;



/* create a singleton of a bank account*/




//struct to pass to thread
struct thread_data{
    ATM* atmInst;
    char * fileToRun;
    Bank* bank;
} DataThread;

struct bank_data{
    Bank* bank;
}BankThread;


// function to run an atm via a thread
void * runATM(void * threadarg){
    struct thread_data * data;
    data  = (struct thread_data *) threadarg;
    ATM* atm = data->atmInst;
    char* file = data->fileToRun;
    Bank* bank = data->bank;
    ifstream fileToRun(file);
    string line;

    //iterate over lines in the file
    while (getline(fileToRun,line))
    {
        //sleep for 100 milliseconds
        usleep(1000);
        // get the specific line
       istringstream iss(line);
       //create a vector of items from the line
       vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
       if (line=="") {
           continue;
       }
       else {
           int accountNum = stoi(tokens.at(1));
           string password = tokens.at(2);

         if (tokens.front()=="O"){
             //open account O <account> <password> < initial amount>
            int initAmount = stoi(tokens.at(3));
             atm->openAccount(bank,atm->getATMId(), accountNum , password, initAmount);
         }
         else if (tokens.front()=="D"){
             //deposit to account D  <account> <password> <amount>
             int Amount = stoi(tokens.at(3));
             atm->deposit(bank,atm->getATMId(),accountNum,password,Amount);

         }
         else if (tokens.front()=="W"){
             // withdraw from account W  <account> <password> <amount>
             int Amount = stoi(tokens.at(3));
             atm->withdraw(bank,atm->getATMId(),accountNum,password,Amount);

         }
         else if (tokens.front()=="B"){
             // return balance of account B  <account> <password>
            atm->viewBalance(bank,atm->getATMId(),accountNum,password);


         }
         else if (tokens.front()=="Q"){
             // close account Q  <account> <password>
             atm->closeAccount(bank,atm->getATMId(),accountNum,password);


         }
         else if (tokens.front()=="T"){
             // transfer from account to account T <account> <password> <target account> <amount>
             int targetAccount= stoi(tokens.at(3));
             int Amount = stoi(tokens.at(4));
             atm->transferToAccount(bank,atm->getATMId(),accountNum,password,targetAccount,Amount);

         }
         else
         {


         }


       }

    }
    //remove atm from working atms list.
    bank->reduceATM();
    pthread_exit(NULL);


}

// thread function to run bank to get commission every 3 seconds
void* runBank(void* threadArgs){
    struct bank_data * data;
    data  = (struct bank_data *) threadArgs;
    Bank* bank = data->bank;
while (bank->getNumATMs()>0){
    sleep(3);
    bank->getCommission();
}
pthread_exit(NULL);
}

// thread function to print to screen the status of the bank and the accounts
void* printBank(void* printArgs){
    struct bank_data * data;
    data  = (struct bank_data *) printArgs;
    Bank* bank = data->bank;
    while(bank->getNumATMs()>0){
        usleep(50000);
        bank->printStatus();

    }

    pthread_exit(NULL);

}







int main(int argc, char *argv[]) {
    const int N =  atoi(argv[1]);
    Bank* mainBank = Bank::getInstance(N);
    pthread_t* BankThread_p = new pthread_t;
    pthread_t* BankPrint_p = new pthread_t;

    struct thread_data* thread_data_array = new thread_data[N];
    struct bank_data bank_data_thread[1];
    bank_data_thread[0].bank=mainBank;
    pthread_t* threads = new pthread_t[N];
    int t,rc;
    pthread_create(BankPrint_p,NULL,printBank,(void*)&bank_data_thread[0]);
    pthread_create(BankThread_p,NULL,runBank,(void*)&bank_data_thread[0]);
    ofstream log("log.txt");
    for (t= 0 ; t <argc-2;t++){
        //create new ATM
        ATM* atmInst = new ATM(t);
        thread_data_array[t].atmInst = atmInst;
        thread_data_array[t].fileToRun=argv[t+2];
        thread_data_array[t].bank=mainBank;
        //create thread with the struct as argument
        rc = pthread_create(&threads[t],NULL,runATM, (void*)&thread_data_array[t]);
        if(rc){
            log<<"ERROR; return code from pthread_create() is "<<rc<<"\n";
            exit(-1);
        }


    }


    //wait for the threads to end
    for (int i=0;i<argc-2;i++)
    {
        pthread_join(threads[i],NULL);

    }
    pthread_join(*BankPrint_p,NULL);
    pthread_join(*BankThread_p,NULL);
    for (int i=0;i<N;i++){
        delete thread_data_array[i].atmInst;
    }
    delete[] thread_data_array;
    delete BankThread_p;
    delete BankPrint_p;
    delete[] threads;
    mainBank->deleteAccounts();
    mainBank->~Bank();


    log.close();
    return 0;
}
