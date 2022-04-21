#define _CRT_SECURE_NO_WARNINGS
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Person.h"
#include "Transaction.h"
//#include "Transaction.h"
using namespace std;


class Transaction;
class Account
{
	//C'tor && D'tor
public:
	Account();
	Account(Person** persons, int count, double balance);
	Account(const Person& person, double balance);
	Account(const Account& other);
	//~Account();

	//Metods
public:
	void SetPersons(Person** persons, int count);
	void SetAccountNumber(int number);
	void SetBalance(double balance);
	void SetTransactions(Transaction** newTransaction, int count);
	Transaction** GetTransactions();
	int GetNumOfTransactions();
	Person** GetPersons() const;
	int	GetTotalPersons()const;
	int	GetAccountNumber() const;
	double GetBalance() const;

public:
	void Withdraw(double amount, const char* date);
	void Deposit(double amount, const char* date);
	void AddPerson(const Person& newPerson, double	amount);
	void DeletePerson(const Person& oldPerson);
	void AddTransaction(const Transaction& newTransaction);

private:
	void clearTransactions();
	void clearPersons();

	//Data members
private:
	Transaction**   m_transactionList;
	int				m_numberOfTransaction;
	Person**        m_persons;
	int				m_totalPersons;
	int				m_accountNumber;
	double			m_balance;
};

#endif //Account.h