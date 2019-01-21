#include "Date.h"
#include "MyExceptions.h"
#include "Post.h"
#include "Degree.h"
#include "Person.h"
#include "Employee.h"
#include "Sector.h"
#include "Department.h"

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#pragma warning(disable : 4996)

char* getTextInput(bool mustBeOnlyChar = false, int minLength = 1, int maxLength = 10);

Department::Department()
{
	departmentName = new char[strlen("Unknown Dep.") + 1];
	strcpy(departmentName, "Unknown Dep.\0");
	sizeSect = 0;
	sectors = new Sector[sizeSect];
}

Department::Department(char* departmentName, Person departmentBoss, Sector sectors[], int sizeSect)
{
	this->departmentName = new char[strlen(departmentName) + 1];
	strcpy(this->departmentName, departmentName);

	this->departmentBoss = departmentBoss;
	this->sizeSect = sizeSect;

	this->sectors = new Sector[sizeSect];
	for (int i = 0; i < sizeSect; i++)
	{
		this->sectors[i] = sectors[i];
	}
}

Department::Department(const Department & tmp)
{
	this->departmentName = new char[strlen(tmp.departmentName) + 1];
	strcpy(departmentName, tmp.departmentName);

	this->departmentBoss = tmp.departmentBoss;

	this->sizeSect = tmp.sizeSect;
	this->sectors = new Sector[sizeSect];
	for (int i = 0; i < sizeSect; i++)
	{
		this->sectors[i] = tmp.sectors[i];
	}
}

Department::~Department()
{
	if (departmentName != nullptr) {
		delete[] departmentName;
		departmentName = nullptr;
	}
	if (sectors != nullptr) {
		delete[] sectors;
		sectors = nullptr;
	}
}

void Department::setDepartmentName(char* departmentName)
{
	this->departmentName = new char[strlen(departmentName) + 1];
	strcpy(this->departmentName, departmentName);
}

void Department::setDepartmentBoss(Person departmentBoss)
{
	this->departmentBoss = departmentBoss;
}

void Department::setSectors(Sector * sectors)
{
	// chk
	this->sectors = new Sector[sizeSect];
	for (int i = 0; i < sizeSect; i++)
	{
		this->sectors[i] = sectors[i];
	}
}

void Department::setSizeSect(int sizeSect)
{
	this->sizeSect = sizeSect;
}

void Department::printDepartment()
{
	cout << "--------------------Department Information---------------------\n" << endl;
	cout << "Department name : " << departmentName << endl;
	cout << "[Department boss]\n"; departmentBoss.printPerson();
	if (this->getSizeSect()){
		cout << "Sectors list : \n\n";
		for (int i = 0; i < sizeSect; i++)
		{
			cout << "\t  Sector #" << i + 1 << " of department \"" << this->getDepartmentName() << "\"" << endl;
			cout << "\t"; sectors[i].printSector();
			cout << endl;
		}
	}
}

void Department::addSect(Sector element)
{
	Sector* new_Sectors = new Sector[sizeSect + 1];

	for (int i = 0; i < sizeSect; i++)
	{
		new_Sectors[i] = sectors[i];
	}
	new_Sectors[sizeSect] = element;
	sizeSect++;
	delete[] sectors;
	sectors = nullptr;
	sectors = new_Sectors;

}

Sector* Department::getSectors()
{
	return sectors;
}

int Department::getSizeSect()
{
	return sizeSect;
}

Person Department::getDepartmentBoss()
{
	return departmentBoss;
}

char* Department::getDepartmentName()
{
	return departmentName;
}

Department & Department::operator=(const Department & other)
{
	if (this != &other) {

		if (this->departmentName != nullptr)
		{
			delete[] this->departmentName;
			departmentName = nullptr;
		}


		this->departmentName = new char[strlen(other.departmentName) + 1];
		strcpy(departmentName, other.departmentName);

		this->departmentBoss = other.departmentBoss;


		if (this->sectors != nullptr)
		{
			delete[] this->sectors;
			this->sectors = nullptr;
		}

		this->sizeSect = other.sizeSect;
		this->sectors = new Sector[sizeSect];
		for (int i = 0; i < sizeSect; i++)
		{
			this->sectors[i] = other.sectors[i];;
		}
	}
	return *this;
}

//7. визначення перевантаженого оператора індексування для внутрішнього динамічного масиву, для якого слід виділити мінімальну потрібну пам’ять;
Sector & Department::operator[](int index) {
	if (index < 0 || index > sizeSect - 1)
	{
		throw badSize("operator [] exception", index);
	}
	return sectors[index];
}



std::ostream & operator<<(std::ostream &s, Department &obj) {
	s << " " << obj.getDepartmentName() << " " << obj.getDepartmentBoss() << " ";
	s << " " << obj.getSizeSect();
	for (int i = 0; i < obj.getSizeSect(); i++)
	{
		s << " " << obj.getSectors()[i];
	}
	return s;
}

std::istream & operator>>(std::istream &s, Department &obj) {
	char* temp_c = new char[100];
	s >> temp_c;
	obj.setDepartmentName(temp_c);
	delete[] temp_c;

	Person tmp_Boss;
	s >> tmp_Boss;
	obj.setDepartmentBoss(tmp_Boss);

	int iTemp;
	s >> iTemp;
	obj.setSizeSect(iTemp);

	//chk
	Sector *tmp_Sectors = new Sector[obj.getSizeSect()];
	for (int i = 0; i < obj.getSizeSect(); i++)
	{
		s >> tmp_Sectors[i];
	}
	obj.setSectors(tmp_Sectors);

	delete[] tmp_Sectors;
	return s;

}

bool Department::writeData_txt() {
	char* path = new char[100];
	cout << "Enter file's namein format [***.txt]\n" << endl;
	path = getTextInput(false, 1, 20);
	ofstream out(path);
	char* ext = strrchr(path, '.');
	if (!out.is_open() || !ext || strcmp(ext, ".txt") != 0)
	{
		throw badPath("Your file name can't be reached.\n");
	}
	out << *this;
	out.close();
	return 1;
}


bool Department::readData_txt()
{
	char* path = new char[100];
	cout << "Enter file's name in format [***.txt]\n" << endl;
	path = getTextInput(false, 1, 20);
	ifstream in(path);
	char* ext = strrchr(path, '.');
	if (!in.is_open() || !ext || strcmp(ext, ".txt") != 0)
	{
		throw badPath("Your file name can't be reached.\n");
	}
	char* buff = new char[100];
	while (!in.eof()) {
		in >> *this;
		break;
	}
	in.close();
	return 1;
}


bool Department::serialize() {
	char* path = new char[100];
	cout << "Enter file's name in format [***.dat]\n" << endl;
	path = getTextInput(false, 1, 20);
	ofstream out;
	out.open(path, ios::out | ios::binary);
	char* ext = strrchr(path, '.');
	if (!out.is_open() || !ext || strcmp(ext, ".dat") != 0)
	{
		throw badPath("Your file name can't be reached.\n");
	}
	int iTemp;

	//Department name
	iTemp = strlen(this->departmentName);
	out.write((char*)&iTemp, sizeof(iTemp));//розмір назви
	out.write(this->departmentName, iTemp + 1);//сама назва

	//Department boss
	this->departmentBoss.app_binary(out);

	iTemp = sizeSect;
	out.write((char*)&sizeSect, sizeof(sizeSect)); // записали розмір секторів

	for (int j = 0; j < sizeSect; j++)
	{
		sectors[j].app_binary(out);
	}

	out.close();
	return 1;
}


bool Department::deserialize() {
	char* path = new char[100];
	cout << "Enter file's name in format [***.dat]\n" << endl;
	path = getTextInput(false, 1, 20);
	ifstream in;
	in.open(path, ios::in | ios::binary);
	char* ext = strrchr(path, '.');
	if (!in.is_open() || !ext || strcmp(ext, ".dat") != 0)
	{
		throw badPath("Your file name can't be reached.\n");
	}
	int iTemp;
	//Department name
	in.read((char*)&iTemp, sizeof(iTemp));
	char *temp_c = new char[iTemp + 1];
	in.read((char*)temp_c, iTemp + 1);
	this->setDepartmentName(temp_c);

	delete[] temp_c;
	temp_c = nullptr;

	//Department boss
	Person tmpBoss;
	tmpBoss.read_binary(in);
	this->setDepartmentBoss(tmpBoss);

	//Department sectors
	in.read((char*)&sizeSect, sizeof(sizeSect));//size

	if (sectors)
	{
		delete[] sectors;
		sectors = nullptr;
	}
	sectors = new Sector[sizeSect];

	for (int j = 0; j < sizeSect; j++)
	{
		sectors[j].read_binary(in);
	}

	in.close();
	return 1;
}

