#define _CRT_SECURE_NO_WARNINGS
#ifndef PERSON_H
#define PERSON_H
#include <string.h>
#include <iostream>
using namespace std;


class Person
{
	//C'tor && D'tor
public:
	Person();
	Person(const char* name, int id);
	Person(const Person& other);
	~Person();

	//Metods
public:
	void	SetName(const char* newName);
	void	SetId(int newId);
	char*   GetName() const;
	int		GetId() const;

	//Data Members
private:
	char*   m_name;
	int		m_id;
};
#endif // !PERSON_H
