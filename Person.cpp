#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"
#include <string.h>
#include <iostream>
using namespace std;


//Default C'tor
Person::Person()
{
	m_id = 0;
	m_name = NULL;
}

//C'tor
Person::Person(const char* name, int id) : m_name(NULL)
{
	SetId(id);
	SetName(name);

}

//Copy C'tor
Person::Person(const Person& other) : m_name(NULL)
{
	
	SetId(other.GetId());
	SetName(other.GetName());
}

//Deletes the dynamic assignment
Person::~Person()
{
	delete m_name;
}

//Set new name 
void Person::SetName(const char* newName) 
{
	if (this->m_name != nullptr)
	{
		delete m_name;
	}
	m_name = new char[strlen(newName) + 1];
	strcpy(m_name, newName);
}

//Set new ID 
void Person::SetId(int newId)
{
	m_id = newId;
}

//Return name 
char* Person::GetName() const
{
	return m_name;
}

//Return ID 
int Person::GetId() const
{
	return m_id;
}


