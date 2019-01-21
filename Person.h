#pragma once
#include "Date.h"
#include <fstream>
class Person
{
protected:
	char* name;
	char* surname;
	Date bdate;
public:
	Person();
	Person(char* name, char* surname, Date bdate);
	Person(const Person& tmp);
	~Person();

	void setName(char* name);
	void setSurname(char* surname);
	void setBirthDate(Date bdate);

	char* getName() const;
	char* getSurname() const;
	Date getBithDate() const;

	void enterPerson();
	void printPerson();
	Person & operator=(const Person & other);
	friend std::ostream & operator<< (std::ostream &s, Person &obj);
	friend std::istream & operator>> (std::istream &s, Person &obj);
	void app_binary(std::ostream &out);
	void read_binary(std::ifstream &in);
};

