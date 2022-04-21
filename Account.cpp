#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"
#include "Account.h"
#include "Transaction.h"

using namespace std;



//Default C'tor
Account::Account()
{
    m_transactionList = NULL;
    m_numberOfTransaction = 0;
    m_persons = NULL;
    m_totalPersons = 0;
    m_accountNumber = 0;
    m_balance = 0;
}
//C'tor
Account::Account(Person** persons, int count, double balance) : m_persons(NULL) , m_transactionList(NULL)
{
    m_transactionList = nullptr;
    m_numberOfTransaction = 0;
    SetBalance(balance);
    m_accountNumber = 0;
    SetPersons(persons, count);
    for (int i = 0; i < m_totalPersons; i++)
    {
        m_accountNumber += persons[i]->GetId();
    }
}
//C'tor of one person
Account::Account(const Person& person, double balance) : m_persons(NULL) , m_transactionList(NULL)
{
    m_transactionList = nullptr;
    m_numberOfTransaction = 0;
    m_totalPersons = 1;
    m_persons = new Person * [m_totalPersons];
    m_persons[0] = new Person(person);
    SetAccountNumber(person.GetId());
    SetBalance(balance);
   
}
//Copy C'tor
Account::Account(const Account& other) : m_persons(NULL) , m_transactionList(NULL)
{
    this->SetAccountNumber(other.m_accountNumber);
    this->SetBalance(other.m_balance);
    this->SetTransactions(other.m_transactionList , other.m_numberOfTransaction);
    this->SetPersons(other.m_persons ,other.m_totalPersons);
}
//D'tor
Account::~Account()
{
        clearPersons();
     //   clearTransactions();
   
}
//Defines the array of actions that belong to the account 
void Account::SetTransactions(Transaction** newTransaction, int count)
{    
    clearTransactions();
    m_numberOfTransaction = count;
    m_transactionList = new Transaction * [count];

    for (int k = 0; k < m_numberOfTransaction; k++)
    {
        // NewArr_persons[k] = m_persons[k];
        m_transactionList[k] = new Transaction(*newTransaction[k]);
    }
    


}
//Defines the array of people who belong to the account 
void Account::SetPersons(Person** persons, int count)
{
    clearPersons();
    m_totalPersons = count;
    m_persons = new Person * [count];

    for (int k = 0; k < m_totalPersons; k++)
    {
        // NewArr_persons[k] = m_persons[k];
        m_persons[k] = new Person(*persons[k]);
    }
    
    
    
}
//Set the account number 
void Account::SetAccountNumber(int number) 
{
      m_accountNumber = number;
}
//Set the balance 
void Account::SetBalance(double balance)
{
    m_balance = balance;
}
//Return the array of actions that belong to the account
Transaction** Account::GetTransactions()
{
    return m_transactionList;
}
//Return the number of the Transactions
int Account::GetNumOfTransactions()
{
    return m_numberOfTransaction;
}
//Return the array of people who belong to the account
Person** Account::GetPersons() const
{
    return m_persons;
}
//Return the number of the person
int Account::GetTotalPersons()const
{
    return m_totalPersons;
}
//Return the account number
int Account::GetAccountNumber() const
{
    return m_accountNumber;
}
//Return the balance
double Account::GetBalance() const
{
    return m_balance;
}
//Add Transaction of Withdraw
void Account::Withdraw(double amount, const char* date)
{
    m_balance -= amount;
    Transaction* NewTrans = new Transaction(this, this, amount, date);
    AddTransaction(*NewTrans);
    //delete NewTrans;

}
//Add Transaction of Deposit
void Account::Deposit(double amount, const char* date)
{
    m_balance += amount;
    Transaction* NewTrans = new Transaction(this, this, amount, date);
    AddTransaction(*NewTrans);
    //delete NewTrans;
}
//Add new person to the list of persons that related  to the account 
void Account::AddPerson(const Person& newPerson, double	amount)
{
            
            bool res = false;
            for (int i = 0; i < m_totalPersons; i++)
            {
                if (m_persons[i]->GetId() == newPerson.GetId())
                {
                    res = true;
                }
            }
            if (res == false)
            {
                m_balance += amount;
                Person** NewArr_persons = new Person * [m_totalPersons + 1];
                for (int k = 0; k < m_totalPersons; k++)
                {
                   // NewArr_persons[k] = m_persons[k];
                    NewArr_persons[k] = new Person(*m_persons[k]);
                }
                NewArr_persons[m_totalPersons] = new Person(newPerson);
                m_totalPersons++;
                delete[] m_persons;
                m_persons = NewArr_persons;
                m_accountNumber += newPerson.GetId();

            }

  
    
}
//Delete a person form the list of person that related to the account
void Account::DeletePerson(const Person& oldPerson)
{
     
        for (int i = 0; i < m_totalPersons ; i++)
        {    

            if (m_persons[i]->GetId() == oldPerson.GetId())
            {   
               
                if (m_totalPersons == 1)
                {
                    clearPersons();
                    m_totalPersons--;
                }
                else
                {
                    int counter = 0;
                    Person** NewArr_persons = new Person * [m_totalPersons - 1];
                    for (int k = 0; k < (m_totalPersons - 1); k++)
                    {
                        if (counter == i)
                        {
                            continue;
                        }
                        else
                        {
                            NewArr_persons[k] = m_persons[k];
                            //NewArr_persons[k] = new Person(*m_persons[k]);
                            counter++;
                        }
                    }
                    m_totalPersons--;
                    delete[] m_persons;
                    m_persons = NewArr_persons;

                }
            }
        }
}
//Add new Transaction to the Transaction list 
void Account::AddTransaction(const Transaction& newTransaction)
{
    int newArraySize = newTransaction.GetSource()->GetNumOfTransactions();
    Transaction** NewArr_Transaction = new Transaction * [newArraySize + 1];
    for (int k = 0; k < newArraySize; k++)
    {

        NewArr_Transaction[k] = new Transaction(*newTransaction.GetSource()->GetTransactions()[k]);

    }
    NewArr_Transaction[newArraySize] = new Transaction(newTransaction);
   
    newTransaction.GetSource()->SetTransactions(NewArr_Transaction, newTransaction.GetSource()->GetNumOfTransactions() + 1 );

   
    newTransaction.GetDes()->SetBalance(newTransaction.GetDes()->GetBalance() + newTransaction.GetAmount());
    newTransaction.GetSource()->SetBalance(newTransaction.GetSource()->GetBalance() - newTransaction.GetAmount());
 
    if (newTransaction.GetDes()->GetAccountNumber() == newTransaction.GetSource()->GetAccountNumber()) 
    {
        return;

    }
    else
    {
        int newArraySize2 = newTransaction.GetDes()->GetNumOfTransactions();
        Transaction** NewArr_Transaction2 = new Transaction * [newArraySize2 + 1];
        for (int k = 0; k < newArraySize2; k++)
        {

            NewArr_Transaction2[k] = new Transaction(*newTransaction.GetDes()->GetTransactions()[k]);

        }
        NewArr_Transaction2[newArraySize2] = new Transaction(newTransaction);
       
        newTransaction.GetDes()->SetTransactions(NewArr_Transaction2, newTransaction.GetDes()->GetNumOfTransactions() + 1);
    }
}
//Clear transactions list
void Account::clearTransactions()
{
    for (int i = 0; i < m_numberOfTransaction; i++)
    {

        delete(m_transactionList[i]->GetDate());
    }
    delete[] m_transactionList;
}
//Clear persons list
void Account::clearPersons()
{
    for (int i = 0; i < m_totalPersons; i++)
    {
        (m_persons[i])->~Person();
    }
    delete[]m_persons;
    
   
}