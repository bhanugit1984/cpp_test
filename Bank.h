#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include<map>
using namespace std;

class InsufficientFunds
{
};
class Account
{
    private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    static long NextAccountNumber;
    
    public:
    Account();
	Account(string fname, string lname, float balance);
	long getAccNo();
	string getFirstName();
	string getLastName();
	float getBalance();
	void Deposit(float amount);
    void Withdraw(float amount);
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();
    friend ofstream & operator << (ofstream & ofs, Account & acc);
    friend ifstream & operator >> (ifstream & ifs, Account & acc);
    friend ostream & operator << (ostream & os, Account & acc);
};

class Bank
{
    private:
    map < long, Account* > accounts;
    
    public:
    Bank();
    Account* OpenAccount(string fname, string lname, float balance);
    Account* BalanceEnquiry(long accountNumber);
    Account* Deposit(long accountNumber, float amount);
    Account* Withdraw(long accountNumber, float amount);
    void CloseAccount(long accountNumber);
    void ShowAllAccounts();
    ~Bank();
};

#endif
