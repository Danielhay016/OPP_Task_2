#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include "Account.h"
#include <string.h>
#include <iostream>

using namespace std;

//C'tor
Transaction::Transaction(Account* s, Account* d, double amount, const char* date) : m_date(NULL)
{
	SetAmount(amount);
	SetDate(date);
	SetSource(s);
	SetDes(d);

}
//Copy C'tor
Transaction::Transaction(const Transaction& other) : m_date(NULL)
{
	SetAmount(other.GetAmount());
	SetDate(other.GetDate());
	SetSource(other.GetSource());
	SetDes(other.GetDes());

}
//Set account source 
void Transaction::SetSource(Account* src)
{
	m_source = src;
}
//Set account destination 
void Transaction::SetDes(Account* dst)
{
	m_destination = dst;
}
//Set the amount of the transaction
void Transaction::SetAmount(double amount)
{
	m_amount = amount;
}
//Set the date of the transaction
void Transaction::SetDate(const char* date) 
{
	if (this->m_date != nullptr)
	{
		delete m_date;
	}
	m_date = new char[strlen(date) + 1];
	strcpy(m_date, date);

}
//Returns the account from which the transaction was made ( OUT ) 
Account* Transaction::GetSource() const
{
	return m_source;
}
//Returns the account to which the transaction was made ( IN ) 
Account* Transaction::GetDes() const
{
	return m_destination;
}
//Retuen the amount of the transaction
double Transaction::GetAmount() const
{
	return m_amount;
}
//Return the date of the transaction
char* Transaction::GetDate() const
{
	return m_date;
}
