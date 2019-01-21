#include "Date.h"
#include "Post.h"
#include "Degree.h"
#include "Person.h"
#include "Employee.h"
#include <iostream>
#include <fstream>
using namespace std;
#pragma warning(disable : 4996)

int randSalary();
char* randText();
char* getTextInput(bool mustBeOnlyChar = false, int minLength = 1, int maxLength = 10);
double getNumInput(bool mustBePositive = true, int maxLength = 9, int minLength = 1, int maxVal = 99999999, int minVal = -99999999);

Employee::Employee()
{
	exp = 0;
}

Employee::Employee(char* name, char* surname, Date bdate, Post post, Degree degree, int exp, Date employmentDate) :Person(name, surname, bdate)
{
	this->post = post;
	this->degree = degree;
	this->exp = exp;
	this->employmentDate = employmentDate;
}

Employee::Employee(const Employee & tmp)
{

	this->name = new char[strlen(tmp.name) + 1];
	strcpy(name, tmp.name);

	this->surname = new char[strlen(tmp.surname) + 1];
	strcpy(surname, tmp.surname);


	this->bdate = tmp.bdate;

	this->post = tmp.post;
	this->degree = tmp.degree;
	this->exp = tmp.exp;

	this->employmentDate = tmp.employmentDate;
}

Employee::~Employee()
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

void Employee::setPost(Post post)
{
	this->post = post;
}

void Employee::setDegree(Degree degree)
{
	this->degree = degree;
}

void Employee::setExp(int exp)
{
	if (exp < 0) {
		cerr << "Exp. can't be negative: " << exp << endl;
		exp = 0;
		return;
	}	
}


void Employee::setEmploymentDate(Date employmentDate)
{
	this->employmentDate = employmentDate;
}

void Employee::enterEmpl()
{
	cout << "\n[Entering Employee]:\n";
	cout << "\nEnter Employee's name:\n";
	char* temp_c = new char[100];
	temp_c = getTextInput(true, 1, 9);
	this->setName(temp_c);
	delete[] temp_c;
	cout << "\nEnter Employee's surname:\n";
	temp_c = new char[100];
	temp_c = getTextInput(true, 1, 9);
	this->setSurname(temp_c);
	delete[] temp_c;
	cout << "\nEnter Employee's birth-Date.\n";
	Date tmp_Date;
	tmp_Date.enterDate();
	this->setBirthDate(tmp_Date);

	Post tmp_Post;
	tmp_Post.enterPost();
	this->setPost(tmp_Post);

	Degree tmp_Deg;
	tmp_Deg.enterDegree();
	this->setDegree(tmp_Deg);
	cout << "\nEnter Employee's experience:\n";
	int iTemp;
	iTemp = getNumInput(true, 9);
	this->setExp(iTemp);
	cout << "\nEnter Employee's employment-Date.\n";
	Date tmp_Date1;
	tmp_Date1.enterDate();
	this->setEmploymentDate(tmp_Date1);
}

void Employee::genEmpl()
{
	this->setName(randText());
	this->setSurname(randText());
	this->setDegree(randText());
	this->setPost(Post(randText(), randSalary()));
	this->setDegree(Degree(randText()));
	this->setBirthDate(Date(1 + rand() % 20, 1 + rand() % 10, 1970 + rand() % 49));
	this->setEmploymentDate(Date(1 + rand() % 20, 1 + rand() % 10, 1970 + rand() % 49));
	this->setExp(rand() % 40);
}

Post Employee::getPost()
{
	return this->post;
}

Degree Employee::getDegree()
{
	return this->degree;
}

int Employee::getExp()
{
	return this->exp;
}

Date Employee::getEmploymentDate()
{
	return employmentDate;
}

void Employee::printEmployee() {
	Person::printPerson();
	post.printPost();
	degree.printDegree();

	cout << " Working experience : " << exp << endl;
	cout << " Employment date : "; employmentDate.printDate();
}

Employee & Employee::operator=(const Employee & other)
{
	if (this != &other) {
		if (this->name != nullptr)
		{
			delete[] this->name;
			this->name = nullptr;
		}
		if (this->surname != nullptr)
		{
			delete[] this->surname;
			this->surname = nullptr;
		}
		this->name = new char[strlen(other.name) + 1];
		strcpy(name, other.name);
		this->surname = new char[strlen(other.surname) + 1];
		strcpy(surname, other.surname);
		this->bdate = other.bdate;
		this->post = other.post;
		this->degree = other.degree;
		this->exp = other.exp;
		this->employmentDate = other.employmentDate;
	}
	return *this;
}

void Employee::app_binary(std::ostream &out) {
	int iTemp;
	// name
	iTemp = strlen(this->getName());
	out.write((char*)&iTemp, sizeof(iTemp));
	out.write(this->getName(), iTemp + 1);
	//surname
	iTemp = strlen(this->getSurname());
	out.write((char*)&iTemp, sizeof(iTemp));
	out.write(this->getSurname(), iTemp + 1);
	//bDate
	this->getBithDate().app_binary(out);
	//degree
	this->getDegree().app_binary(out);
	//exp
	iTemp = exp;
	out.write((char*)&iTemp, sizeof(iTemp));
	//post
	this->getPost().app_binary(out);
	//eDate
	this->getEmploymentDate().app_binary(out);
}


void Employee::read_binary(std::ifstream &in) {
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

	//bDate
	Date tmpDate;
	tmpDate.read_binary(in);
	this->bdate = tmpDate;
	//degree
	Degree tmpDeg;
	tmpDeg.read_binary(in);
	this->setDegree(tmpDeg);
	//exp
	in.read((char*)&iTemp, sizeof(iTemp));
	this->exp = iTemp;
	//post
	Post tmpPost;
	tmpPost.read_binary(in);
	this->post = tmpPost;
	//eDate
	Date tmpDate1;
	tmpDate1.read_binary(in);
	this->employmentDate = tmpDate1;
}



std::ostream & operator<<(std::ostream &s, Employee &obj) {
	s <<" "<< obj.getName() <<" "<< obj.getSurname() <<" "<< obj.getBithDate() <<" "<< obj.getPost() <<" "<< obj.getDegree() <<" "<< obj.getExp() <<" "<< obj.getEmploymentDate()<<" ";
	return s;
}

std::istream & operator>>(std::istream &s, Employee &obj) {
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

	Post tmp_Post;
	s >> tmp_Post;
	obj.setPost(tmp_Post);

	Degree tmp_Degree;
	s >> tmp_Degree;
	obj.setDegree(tmp_Degree);

	int iTemp;
	s >> iTemp;
	obj.setExp(iTemp);

	Date tmp_eDate;
	s >> tmp_eDate;
	obj.setBirthDate(tmp_eDate);

	return s;
}