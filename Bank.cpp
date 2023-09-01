#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include<map>
#include"Bank.h"
using namespace std;
#define MIN_BALANCE 100

    
Account::Account()
{
}

long Account::getAccNo()
{
	return accountNumber;
}
string Account::getFirstName()
{
	return firstName;
}
string Account::getLastName()
{
	return lastName;
}
float Account::getBalance()
{
	return balance;
}


long Account::NextAccountNumber = 0;

int main()
{
    Bank b;
    Account *acc;
    int choice;
    string fname, lname;
    long accountNumber;
    float balance;
    float amount;
    cout << "Banking System" << endl;
    do
    {
        cout << "\n\tSelect one option below:";
        cout << "\n\t1 Open an Account";
        cout << "\n\t2 Balance Enquiry";
        cout << "\n\t3 Deposit";
        cout << "\n\t4 Withdrawal";
        cout << "\n\t5 Close an Account";
        cout << "\n\t6 Show All Accounts";
        cout << "\n\t7 Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
         case 1:
             cout << "Enter First Name: ";
             cin >> fname;
             cout << "Enter Last Name: ";
             cin >> lname;
             cout << "Enter initil Balance: ";
             cin >> balance;
             acc = b.OpenAccount (fname, lname, balance);
             cout << endl << "Congratulations Account is Created" << endl;
             cout << *acc;
             break;
 
         case 2:
             cout << "Enter Account Number:";
             cin >> accountNumber;
             acc = b.BalanceEnquiry (accountNumber);
			 if(acc!=NULL)
			 {
				 cout << endl << "Your Account Details" << endl;
				 cout << *acc;
			 }
			 else
			 {
				 cout << endl << "Account Number not found"<<endl;
			 }
             break;
             
         case 3:
             cout << "Enter Account Number:";
             cin >> accountNumber;
             cout << "Enter The Amount to Deposit:";
             cin >> amount;
             acc = b.Deposit (accountNumber, amount);
			 if(acc!=NULL)
			 {
				 cout << *acc;
			 }
			 else
			 {
				 cout << endl << "Account Number not found"<<endl;
			 }
             break;
             
         case 4:
             cout << "Enter Account Number:";
             cin >> accountNumber;
             cout << "Enter The amount to Withdraw:";
             cin >> amount;
             acc = b.Withdraw (accountNumber, amount);
			 if(acc!=NULL)
			 {
				 cout << *acc;
			 }
			 else
			 {
				 cout << endl << "Account Number not found"<<endl;
			 }
             break;
             
         case 5:
             cout << "Enter Account Number:";
             cin >> accountNumber;
             b.CloseAccount (accountNumber);
             cout << endl << "Account is Closed" << endl;
             
             
         case 6:
             b.ShowAllAccounts ();
             break;
             
         case 7:
             break;
             
         default:
             cout << "\nEnter corret choice";
             exit (0);
        }
		accountNumber= -1;
		balance = 0;
		amount =0;
    }
    while (choice != 7);
    return 0;
}
Account::Account (string fname, string lname, float balance)
{
    NextAccountNumber++;
    accountNumber = NextAccountNumber;
    firstName = fname;
    lastName = lname;
    this->balance = balance;
}
void Account::Deposit (float amount)
{
    balance += amount;
}
void Account::Withdraw (float amount)
{
	
	
    balance -= amount;
}
void Account::setLastAccountNumber (long accountNumber)
{
    NextAccountNumber = accountNumber;
}
long Account::getLastAccountNumber ()
{
    return NextAccountNumber;
}
ofstream & operator << (ofstream & ofs, Account & acc)
{
    ofs << acc.accountNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.balance << endl;
    return ofs;
}
ifstream & operator >> (ifstream & ifs, Account & acc)
{
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}
ostream & operator << (ostream & os, Account & acc)
{
    os << "First Name:" << acc.getFirstName () << endl;
    os << "Last Name:" << acc.getLastName () << endl;
    os << "Account Number:" << acc.getAccNo () << endl;
    os << "Balance:" << acc.getBalance () << endl;
    return os;
}
Bank::Bank ()
{
    Account *account;
    ifstream infile;
    infile.open ("Bank.data");
    if (!infile)
    {
        //cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    while (!infile.eof ())
    {
        infile >> *(account);
        accounts.insert (pair < long, Account* > (account->getAccNo (), account));
    }
    Account::setLastAccountNumber (account->getAccNo ());
    infile.close ();
}
Account* Bank::OpenAccount (string fname, string lname, float balance)
{
    ofstream outfile;
    Account *account = new Account(fname, lname, balance);
    accounts.insert (pair < long, Account* > (account->getAccNo (), account));
    outfile.open ("Bank.data", ios::trunc);
    map < long, Account* >::iterator itr;
    for (itr = accounts.begin (); itr != accounts.end (); itr++)
    {
        outfile << *(itr->second);
    }
    outfile.close ();
    return account;
}
Account* Bank::BalanceEnquiry (long accountNumber)
{
    map < long, Account* >::iterator itr = accounts.find (accountNumber);
	if(itr!=accounts.end())
		return itr->second;
	else
		return NULL;
}
Account* Bank::Deposit (long accountNumber, float amount)
{
    map < long, Account* >::iterator itr = accounts.find (accountNumber);
	if(itr!=accounts.end())
	{
		if(amount >=10000)
		{
			cout <<"A user cannot deposit more than $10,000 in a single transaction"<<endl;
			return itr->second;
		}
		itr->second->Deposit (amount);
		cout << endl << "Amount is Deposited" << endl;
		return itr->second;
	}
	else
		return NULL;
}
Account* Bank::Withdraw (long accountNumber, float amount)
{
    map < long, Account* >::iterator itr = accounts.find (accountNumber);
	if(itr!=accounts.end())
	{
		float balance = itr->second->getBalance();
		float bal =  balance * (90/100);
		if (balance - amount < MIN_BALANCE)
			throw InsufficientFunds ();
		else if (amount >= bal)
		{
			cout<<"A user cannot withdraw more than 90% of their total balance from an account in a single transaction." <<endl;
			return itr->second;
		}
	
		itr->second->Withdraw (amount);
		cout << endl << "Amount Withdrawn" << endl;
		return itr->second;
	}
	else
		return NULL;
}
void Bank::CloseAccount (long accountNumber)
{
    map < long, Account* >::iterator itr = accounts.find (accountNumber);
	if(itr!=accounts.end())
	{
		cout << endl << "Account Deletedis " << endl << *(itr->second);
		delete itr->second;
		accounts.erase (accountNumber);
	}
	else
		cout << endl << "Account Number not found"<<endl;
}
void Bank::ShowAllAccounts ()
{
    map < long, Account* >::iterator itr;
    for (itr = accounts.begin (); itr != accounts.end (); itr++)
    {
        cout << "Account " << itr->first << endl << *(itr->second) << endl;
    }
}
Bank::~Bank ()
{
    ofstream outfile;
    outfile.open ("Bank.data", ios::trunc);
    map < long, Account* >::iterator itr;
    for (itr = accounts.begin (); itr != accounts.end (); itr++)
    {
        outfile << *(itr->second);
		delete itr->second;
    }
    outfile.close ();
}
