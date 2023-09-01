#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include<map>
#include "Bank.h"
using namespace std;
#define MIN_BALANCE 100

long openAccount(string fname, string lname, float amount, Bank& ob);
void depositAmount(long acctno, float amount, Bank& ob);
void withdrawAmount(long acctno, float amount, Bank& ob);
void deleteAccount(long acctno, Bank& ob);


long openAccount(string fname, string lname, float amount, Bank& b)
{
    Account *acc;
	acc = b.OpenAccount (fname, lname, amount);
	cout << endl << "Congratulations Account is Created" << endl;
	cout << *acc;
	return acc->getAccNo();
}

void depositAmount(long acctno, float amount, Bank& b)
{
	Account *acc = b.Deposit (acctno, amount);
	if(acc!=NULL)
	{
	 cout << *acc;
	}
	else
	{
	 cout << endl << "Account Number not found"<<endl;
	}
}

void withdrawAmount(long acctno, float amount, Bank& b)
{
	Account *acc = b.Withdraw (acctno, amount);
	if(acc!=NULL)
	{
	 cout << *acc;
	}
	else
	{
	 cout << endl << "Account Number not found"<<endl;
	}
}

void deleteAccount(long acctno, Bank& b)
{
	b.CloseAccount (acctno);
	cout << endl << "Account is Closed" << endl;
}

int main()
{
	Bank b;
	long acctno = openAccount("abcdef", "hijklmn", 12000, b);
	depositAmount(acctno, 1000,b); //testcase to check for depositing amount
	depositAmount(1234,11000,b); //test case for checking on entering wrong account number
	depositAmount(acctno,11000,b); //test case for not depositing morethan 10000 amount
	withdrawAmount(acctno,11500,b); //test case for withdrawing 90% of amount which doesnt allow
	deleteAccount(acctno,b);       //test case for deleting the account
	
	acctno = openAccount("jacob", "hijklmn", 15000, b);
	depositAmount(acctno, 1000,b);
	depositAmount(acctno,11000,b);
	withdrawAmount(acctno,11500,b);
	deleteAccount(acctno,b);
	return 0;
}
