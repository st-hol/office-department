#include "Date.h"
#include "Person.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#pragma warning(disable : 4996)
char* getTextInput(bool mustBeOnlyChar = false, int minLength = 1, int maxLength = 10);
double getNumInput(bool mustBePositive = true, int maxLength = 9, int minLength = 1, int maxVal = 99999999, int minVal = -99999999);
Person::Person()
{
	name = new char[strlen("Name") + 1];
	strcpy(name, "Name\0");
	surname = new char[strlen("Surname") + 1];
	strcpy(surname, "Surname\0");
	//bdate by default;
}

Person::Person(char* name, char* surname, Date bdate)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->surname = new char[strlen(surname) + 1];
	strcpy(this->surname, surname);
	this->bdate = bdate;
}

Person::Person(const Person & tmp)
{
	this->name = new char[strlen(tmp.name) + 1];
	strcpy(name, tmp.name);
	this->surname = new char[strlen(tmp.surname) + 1];
	strcpy(surname, tmp.surname);
	this->bdate = tmp.bdate;

}

Person::~Person()
{
	if (name != nullptr)
	{
		delete[] name;
		name = nullptr;
	}
	if (surname != nullptr)
	{
		delete[] surname;
		surname = nullptr;
	}
}

char*  Person::getName() const { return name; }
char*  Person::getSurname() const { return surname; }
Date Person::getBithDate() const { return bdate; }

void Person::enterPerson()
{
	cout << "\nEnter Person's name:\n";
	char* temp_c = new char[100];
	temp_c = getTextInput(true,1, 9);
	this->setName(temp_c);
	delete[] temp_c;
	cout << "\nEnter Person's surname:\n";
	temp_c = new char[100];
	temp_c = getTextInput(true, 1, 9);
	this->setSurname(temp_c);
	delete[] temp_c;
	cout << "\nEnter Person's birth-Date.\n";
	Date tmp_Date;
	tmp_Date.enterDate();
	this->setBirthDate(tmp_Date);
}


void Person::printPerson()
{
	cout << " Name : " << name << endl;
	cout << " Surname : " << surname << endl;
	cout << " Birth date : "; bdate.printDate();
}


void Person::setName(char*  name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
void Person::setSurname(char*  surname)
{
	this->surname = new char[strlen(surname) + 1];
	strcpy(this->surname, surname);
}
void Person::setBirthDate(Date bdate)
{
	this->bdate = bdate;
}

Person & Person::operator=(const Person & other)
{
	if (this != &other) {
		if (this->name != nullptr)
		{
			delete[] this->name;
		}
		if (this->surname != nullptr)
		{
			delete[] this->surname;
		}

		this->name = new char[strlen(other.name) + 1];
		strcpy(name, other.name);

		this->surname = new char[strlen(other.surname) + 1];
		strcpy(surname, other.surname);

		this->bdate = other.bdate;
	}
	return *this;
}

void Person::app_binary(std::ostream & out)
{
	int iTemp;
	// name/surname
	iTemp = strlen(this->getName());
	out.write((char*)&iTemp, sizeof(iTemp));
	out.write(this->getName(), iTemp + 1);
	iTemp = strlen(this->getSurname());
	out.write((char*)&iTemp, sizeof(iTemp));
	out.write(this->getSurname(), iTemp + 1);
	this->getBithDate().app_binary(out);
}

void Person::read_binary(std::ifstream & in)
{
	int iTemp;
	//name
	in.read((char*)&iTemp, sizeof(iTemp));
	char *temp_c1 = new char[iTemp + 1];
	in.read((char*)temp_c1, iTemp + 1);
	this->setName(temp_c1);
	delete[] temp_c1;
	temp_c1 = nullptr;
	//surname
	in.read((char*)&iTemp, sizeof(iTemp));
	char *temp_c2 = new char[iTemp + 1];
	in.read((char*)temp_c2, iTemp + 1);
	this->setSurname(temp_c2);
	delete[] temp_c2;
	temp_c2 = nullptr;
	Date tmpDate;
	tmpDate.read_binary(in);
	this->bdate = tmpDate;
}


std::ostream & operator<<(std::ostream &s, Person &obj) {
	s <<" "<< setw(12) << obj.getName() <<" "<< setw(13) << obj.getSurname() <<" "<< obj.getBithDate() << " ";
	return s;
}

std::istream & operator>>(std::istream &s, Person &obj) {
	char* temp_c = new char[100];
	s >> temp_c;
	obj.setName(temp_c);
	delete[] temp_c;

	temp_c = new char[100];
	s >> temp_c;
	obj.setSurname(temp_c);
	delete[] temp_c;

	Date tmp_Date;
	s >> tmp_Date;
	obj.setBirthDate(tmp_Date);
	return s;
}