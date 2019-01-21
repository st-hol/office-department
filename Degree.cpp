#include "Degree.h"
#include <iostream>
using namespace std;
#pragma warning(disable : 4996)

void Degree::enterDegree() {
	int choice, res;
	do
	{
		cout << "Enter Scientific Degree\n{1 - Candidate}\n{2 - Professor}\n{3 - Senior Researcher}\n{4 - Leading Researcher}\nYour choice >>";
		res = scanf("%d", &choice);
		while (getchar() != '\n');
		switch (choice)
		{//clean
		case 1:
			degree = new char[strlen("Candidate") + 1];
			strcpy(degree, "Candidate\0");
			break;
		case 2:
			degree = new char[strlen("Professor") + 1];
			strcpy(degree, "Professor\0");
			break;
		case 3:
			degree = new char[strlen("Senior Researcher") + 1];
			strcpy(degree, "Senior Researcher\0");
			break;
		case 4:
			degree = new char[strlen("Leading Researcher") + 1];
			strcpy(degree, "Leading Researcher\0");
			break;
		}
	} while (res != 1 || choice > 4 || choice <= 0);
}

Degree::Degree()
{
	degree = new char[strlen("Default") + 1];
	strcpy(degree, "Default\0");
}

Degree::Degree(char* degree)
{
	this->degree = new char[strlen(degree) + 1];
	strcpy(this->degree, degree);

}

Degree::Degree(const Degree & tmp)
{
	this->degree = new char[strlen(tmp.degree) + 1];
	strcpy(degree, tmp.degree);
}

Degree::~Degree()
{
	if (degree != nullptr)
	{
		delete[] degree;
		degree = nullptr;
	}
}

void Degree::setDegreeName(char* degree)
{
	this->degree = new char[strlen(degree) + 1];
	strcpy(this->degree, degree);
}

char* Degree::getDegreeName()
{
	return degree;
}

void Degree::printDegree()
{
	cout << " Scientific Degree : " << degree << endl;
}
Degree & Degree::operator=(const Degree & other)
{
	if (this != &other) {
		if (this->degree != nullptr)
		{
			//here
			delete[] this->degree;
			this->degree = nullptr;
		}

		this->degree = new char[strlen(other.degree) + 1];
		strcpy(degree, other.degree);
	}
	return *this;
}

void Degree::app_binary(std::ostream & out)
{
	int iTemp;
	iTemp = strlen(this->getDegreeName());
	out.write((char*)&iTemp, sizeof(iTemp));
	out.write(this->getDegreeName(), iTemp + 1);
}

void Degree::read_binary(std::ifstream & in)
{
	int iTemp;
	in.read((char*)&iTemp, sizeof(iTemp));
	char *temp_c = new char[iTemp + 1];
	in.read((char*)temp_c, iTemp + 1);
	this->setDegreeName(temp_c);
	delete[] temp_c;
	temp_c = nullptr;
}



/////////////
std::ostream & operator<<(std::ostream &s, Degree &obj) {
	s << obj.getDegreeName() << " ";
	return s;
}

std::istream & operator>>(std::istream &s, Degree &obj) {
	char* temp_c = new char[100];
	s >> temp_c;
	obj.setDegreeName(temp_c);
	delete[] temp_c;
	return s;
}