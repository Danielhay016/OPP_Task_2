#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"
#include <string.h>
#include <iostream>
using namespace std;





//C'tor
Bank::Bank()
{
	  m_name = NULL;
	  m_account = NULL;
	  m_bankCode = 0;
	  m_numbeOfAccounts= 0 ;
	  m_totalBalance = 0;
}
//C'tor
Bank::Bank(const char* name, int code) : m_name(NULL)
{
	SetBankName(name);
    SetCode(code);
}
//D'tor
Bank::~Bank()
{
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		delete m_account[i];
		
	}
	delete[]  m_account;

	delete m_name;
}
//Set name of the bank
void			Bank::SetBankName(const char* name)
{
	if (this->m_name != nullptr)
	{
		delete[] m_name;
	}
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
}
 //Set accounts
void			Bank::SetAccount(Account** account, int numbeOfAccounts)
{	

		for (int i = 0; i < m_numbeOfAccounts; i++)
		{
			delete m_account[i];
		}
		delete[]  m_account;
		m_account = account;
		m_numbeOfAccounts = numbeOfAccounts;
	
}
//Set balance 
void			Bank::SetTotal(double total)
{
	m_totalBalance = total;
}
//Set bank code 
void			Bank::SetCode(int code)
{
	m_bankCode = code;
} 
//Return bank name 
const char* Bank::GetBankName() const
{
	return m_name;
}
//Return accounts array 
Account** Bank::GetAccounts() const
{
	return m_account;
}
//Return numbers of accounts
int				Bank::GetNumberOfAccounts() const
{
	return m_numbeOfAccounts;
}
//Return balance
double			Bank::GetTotal() const
{
	return m_totalBalance;
}
//Return bank's code
int				Bank::GetCode() const
{
	return m_bankCode;
}
//Add account
void Bank::AddAccount(const Account& account)
{
	
        bool res = false;
        for (int i = 0; i < m_numbeOfAccounts; i++)
        {
			if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
            {
                res = true;
            }
        }
        if (res == false)
        {    
			m_totalBalance += account.GetBalance();
			Account** NewArr_Account = new Account * [m_numbeOfAccounts + 1];
            for (int k = 0; k < m_numbeOfAccounts; k++)
            {
				//NewArr_Account[k] = m_account[k];
				NewArr_Account[k] = new Account(*m_account[k]);
            }
			NewArr_Account[m_numbeOfAccounts] = new Account(account);
			m_numbeOfAccounts++;
            delete[] m_account;
			m_account = NewArr_Account;
			
        }

    

}
//Add account
void Bank::AddAccount(const Person& per, double amount)
{
	Account new_account(per, amount);
	AddAccount(new_account);

}
//Add a person from the account
void Bank::AddPerson(const Person& newPerson, const Account& account, double amount)
{
	for (int i = 0; i < m_numbeOfAccounts  ; i++)
	{
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
		{
			m_account[i]->AddPerson(newPerson, amount);
			
		}

	}
}
//Deletes an account
void Bank::DeleteAccount(const Account& account)
{

	m_totalBalance -= account.GetBalance();
	
	for (int i = 0; i <	m_numbeOfAccounts ; i++)
	{    
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
		{   
			if (m_numbeOfAccounts ==  1 )
			{

				
				for (int i = 0; i < m_numbeOfAccounts; i++)
				{
					delete m_account[i];

				}
				delete[]  m_account;

			}
			else {
				int counter = 0;
				Account** NewArr_account = new Account * [m_numbeOfAccounts - 1];
				for (int k = 0; k < (m_numbeOfAccounts - 1); k++)
				{
					if (counter == i)
					{
						continue;
					}
					else
					{
						NewArr_account[k] = new Account(*m_account[k]);
						counter++;
					}
				}
				m_numbeOfAccounts--;
				delete[] m_account;
				m_account = NewArr_account;
			}

		}
	}
}
//Deletes a person from the account
void Bank::DeletePerson(const Person& p)
{
	
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		for (int k = 0; k < m_account[i]->GetTotalPersons(); k++)
		{
			m_account[i]->DeletePerson(p);

			if (m_account[i]->GetTotalPersons() == 0)
			{
				DeleteAccount(*m_account[i]);
				break;
			}
		}
	}

}