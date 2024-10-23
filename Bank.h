#define _CRT_SECURE_NO_WARNINGS
#ifndef BANK_H
#define BANK_H
#include "Account.h"
#include <string.h>
#include <iostream>
using namespace std;


class Bank
{
public:
	//C'tor
	Bank();
	Bank(const char* name, int code);
	//D'tor
	~Bank();

	//Metods
public:
	void			SetBankName(const char* name);
	void			SetAccount(Account** account, int numbeOfAccounts);
	void			SetTotal(double total);
	void			SetCode(int code);
	const char*     GetBankName() const;
	Account**       GetAccounts() const;
	int				GetNumberOfAccounts() const;
	double			GetTotal() const;
	int				GetCode() const;

public:
	void AddAccount(const Account& account);
	void AddAccount(const Person& per, double amount);
	void AddPerson(const Person& newPerson, const Account& account, double amount);
	void DeleteAccount(const Account& account);
	void DeletePerson(const Person& p);

	//Data Members
private:
	char*       m_name;
	Account**   m_account;
	int			m_bankCode;
	int			m_numbeOfAccounts;
	double		m_totalBalance;
};
#endif // BANK_H
