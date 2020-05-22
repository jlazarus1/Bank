#include <iostream>
#include <list>
#include "BankAccount.h"
#include "ATM.h"
#include "Bank.h"
#include <pthread.h>
#include <stdio.h>
#include <fstream>
#include <regex>
using namespace std;


/* create a singleton of a bank account*/




//struct to pass to thread
struct thread_data{
    int thread_id;
    ATM* atmInst;
    char * fileToRun;
    Bank* bank;
};


// function to run an atm via a thread
void * runATM(void * threadarg){
    struct thread_data * data;
    data  = (struct thread_data *) threadarg;
    int thread_id = data->thread_id;
    ATM* atm = data->atmInst;
    char* file = data->fileToRun;
    Bank* bank = data->bank;
    ifstream fileToRun(file);
    string line;

    //iterate over lines in the file
    while (getline(fileToRun,line))
    {
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


         }
         else if (tokens.front()=="W"){
             // withdraw from account W  <account> <password> <amount>
             int Amount = stoi(tokens.at(3));

         }
         else if (tokens.front()=="B"){
             // return balance of account B  <account> <password>



         }
         else if (tokens.front()=="Q"){
             // close account Q  <account> <password>


         }
         else if (tokens.front()=="T"){
             // transfer from account to account T <account> <password> <target account> <amount>
             int targetAccount= stoi(tokens.at(3));
             int Amount = stoi(tokens.at(4));

         }
         else
         {


         }


       }

    }



}





int main(int argc, char *argv[]) {
    Bank* mainBank = Bank::getInstance();
    struct thread_data thread_data_array[argc -2];
    pthread_t threads[argc - 2];
    int t,rc;
    ofstream log("log.txt");
    for (t= 0 ; t <argc-2;t++){
        thread_data_array[t].thread_id=t;
        //create new ATM
        ATM* atmInst = new ATM(t);
        thread_data_array[t].atmInst = atmInst;
        thread_data_array[t].fileToRun=argv[t+2];
        thread_data_array[t].bank=mainBank;
        //create thread with the struct as argument
        rc = pthread_create(&threads[t],NULL,runATM, (void *)&thread_data_array[t]);
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

    log.close();
    return 0;
}
;