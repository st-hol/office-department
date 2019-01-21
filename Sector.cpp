#include "MyExceptions.h"
#include "Date.h"
#include "Post.h"
#include "Degree.h"
#include "Person.h"
#include "Employee.h"
#include "Sector.h"
#include <iostream>
#include <fstream>
using namespace std;
#pragma warning(disable : 4996)

int randSalary();
char* randText();
char* getTextInput(bool mustBeOnlyChar = false, int minLength = 1, int maxLength = 10);
double getNumInput(bool mustBePositive = true, int maxLength = 9, int minLength = 1, int maxVal = 99999999, int minVal = -99999999);

Sector::Sector()
{
	sizeEmpl = 0;
	sizePost = 0;
	employees = new Employee[sizeEmpl];//
	posts = new Post[sizePost];//

	sectorName = new char[strlen("SectorName") + 1];
	strcpy(sectorName, "SectorName\0");
}
Sector::Sector(char* sectorName, Person sectorBoss, Employee employees[], int sizeEmpl, Post posts[], int sizePost)
{

	this->sectorName = new char[strlen(sectorName) + 1];
	strcpy(this->sectorName, sectorName);

	this->sectorBoss = sectorBoss;

	this->sizeEmpl = sizeEmpl;
	this->employees = new Employee[sizeEmpl];
	for (int i = 0; i < sizeEmpl; i++)
	{
		this->employees[i] = employees[i];
	}

	this->sizePost = sizePost;
	this->posts = new Post[sizePost];
	for (int i = 0; i < sizePost; i++)
	{
		this->posts[i] = posts[i];
	}
}

Sector::Sector(const Sector & tmp)
{
	this->sectorName = new char[strlen(tmp.sectorName) + 1];
	strcpy(sectorName, tmp.sectorName);
	this->sectorBoss = tmp.sectorBoss;
	this->sizeEmpl = tmp.sizeEmpl;
	this->sizePost = tmp.sizePost;

	this->employees = new Employee[sizeEmpl];
	for (int i = 0; i < sizeEmpl; i++)
	{
		this->employees[i] = tmp.employees[i];
	}

	this->posts = new Post[sizePost];
	for (int i = 0; i < sizePost; i++)
	{
		this->posts[i] = tmp.posts[i];
	}

}

Sector::~Sector()
{
	if (sectorName != nullptr)
	{
		delete[] sectorName;
		sectorName = nullptr;
	}
	if (employees != nullptr)
	{
		delete[] employees;
		employees = nullptr;
	}
	if (posts != nullptr)
	{
		delete[] posts;
		posts = nullptr;
	}
}

Post* Sector::getPosts()
{
	return posts;
}

Employee * Sector::getEmployees()
{
	return employees;
}

int Sector::getSizePosts()
{
	return sizePost;
}

int Sector::getSizeEmpls()
{
	return sizeEmpl;
}

char* Sector::getSectorName()
{
	return sectorName;
}

Person Sector::getSectorBoss()
{
	return sectorBoss;
}

void Sector::setSectorName(char* sectorName)
{
	this->sectorName = new char[strlen(sectorName) + 1];
	strcpy(this->sectorName, sectorName);
}
void Sector::setSectorBoss(Person sectorBoss)
{
	this->sectorBoss = sectorBoss;
}

void Sector::setEmployees(Employee * employees)
{
	//мб
	this->employees = new Employee[sizeEmpl];
	for (int i = 0; i < sizeEmpl; i++)
	{
		this->employees[i] = employees[i];
	}
}
void Sector::setPosts(Post * posts)
{
	//mb
	this->posts = new Post[sizePost];
	for (int i = 0; i < sizePost; i++)
	{
		this->posts[i] = posts[i];
	}
}

void Sector::setSizeEmpls(int sizeEmpl)
{
	this->sizeEmpl = sizeEmpl;
}

void Sector::setSizePosts(int sizePost)
{
	this->sizePost = sizePost;
}

void Sector::printSector()
{
	cout << "--------------------Sector Information---------------------\n" << endl;
	cout << "Sector name : " << sectorName << endl;
	cout << "[Sector boss]\n"; sectorBoss.printPerson();
	if (this->getSizeEmpls()) {
		cout << "\n\t[Employee list] : \n\n";
		for (int i = 0; i < sizeEmpl; i++)
		{
			cout << "\t  Employee #" << i + 1 << endl;
			employees[i].printEmployee();
			cout << endl;
		}
	}

	if (this->getSizePosts())
	{
		cout << "\n\t[Posts list] : \n\n";
		for (int i = 0; i < sizePost; i++)
		{
			cout << "\t  Post #" << i + 1 << endl;
			posts[i].printPost();
			cout << endl;
		}
	}
}

void Sector::addEmpl(Employee element)
{
	Employee* new_Empls = new Employee[sizeEmpl + 1];

	for (int i = 0; i < sizeEmpl; i++)
	{
		new_Empls[i] = employees[i];
	}
	new_Empls[sizeEmpl] = element;
	sizeEmpl++;
	delete[] employees;
	employees = nullptr;
	employees = new_Empls;
}


void Sector::addPost(Post element)
{
	Post* new_Posts = new Post[sizePost + 1];

	for (int i = 0; i < sizePost; i++)
	{
		new_Posts[i] = posts[i];
	}
	new_Posts[sizePost] = element;
	sizePost++;
	delete[] posts;
	posts = nullptr;
	posts = new_Posts;
}

void Sector::genSector(int nEmpls, int nPosts)
{
	this->setSectorName(randText());
	Employee tmp_Empl;
	tmp_Empl.genEmpl();
	this->setSectorBoss(tmp_Empl);
	this->setSizeEmpls(nEmpls);
	Employee *tmp_Empls = new Employee[sizeEmpl];
	for (int i = 0; i < sizeEmpl; i++)
	{
		tmp_Empls[i].genEmpl();
	}
	//tmp_Empls[0].genEmpl();
	this->setEmployees(tmp_Empls);

	this->setSizePosts(nPosts);
	Post *tmp_Posts = new Post[sizePost];
	for (int i = 0; i < sizePost; i++)
	{
		tmp_Posts[i].genPost();
	}
	//tmp_Posts[0].genPost();
	this->setPosts(tmp_Posts);
}

void Sector::enterSector(int nEmpls, int nPosts)
{
	cout << "\n[Entering Sector]:\n";
	cout << "\nEnter Sector name:\n";
	char* temp_c = new char[100];
	temp_c = getTextInput(false,1,10);
	this->setSectorName(temp_c);
	delete[] temp_c;

	cout << "\n[Entering Sector boss]:\n";
	Person tmp_Boss;
	tmp_Boss.enterPerson();
	this->setSectorBoss(tmp_Boss);

	this->setSizeEmpls(nEmpls);
	Employee *tmp_Empls = new Employee[sizeEmpl];
	for (int i = 0; i < sizeEmpl; i++)
	{
		tmp_Empls[i].enterEmpl();
	}
	this->setEmployees(tmp_Empls);

	this->setSizePosts(nPosts);
	Post *tmp_Posts = new Post[sizePost];
	for (int i = 0; i < sizePost; i++)
	{
		tmp_Posts[i].enterPost();
	}
	this->setPosts(tmp_Posts);
}


Employee& Sector::operator[](int index) {
	if (index < 0 || index > sizeEmpl - 1)
	{
		throw badSize("operator [] exception", index);
	}
	return employees[index];
}




//void* Sector::operator[](int i) {
//	void *ptr;
//	if (i==0)
//	{
//		ptr = employees;
//	}
//	else
//	{
//		ptr = posts;
//	}
//	return ptr;
//}


Sector & Sector::operator=(const Sector & other)
{
	if (this != &other) {
		if (this->sectorName != nullptr)
		{
			delete[] this->sectorName;
			this->sectorName = nullptr;
		}

		this->sectorName = new char[strlen(other.sectorName) + 1];
		strcpy(sectorName, other.sectorName);

		this->sectorBoss = other.sectorBoss;

		//.......................................
		if (this->employees != nullptr) {
			delete[] this->employees;
			this->employees = nullptr;
		}
		this->sizeEmpl = other.sizeEmpl;
		this->employees = new Employee[sizeEmpl];
		for (int i = 0; i < sizeEmpl; i++)
		{
			this->employees[i] = other.employees[i];;
		}

		///////////////////////////////////////////////////////

		if (this->posts != nullptr) {
			delete[] this->posts;
			this->posts = nullptr;
		}
		this->sizePost = other.sizePost;
		this->posts = new Post[sizePost];
		for (int i = 0; i < sizePost; i++)
		{
			this->posts[i] = other.posts[i];
		}
	}

	return *this;
}



std::ostream & operator<<(std::ostream &s, Sector &obj) {
	s << " " << obj.getSectorName() << " " << obj.getSectorBoss() << " ";

	s << " " << obj.getSizeEmpls() << " ";
	for (int i = 0; i < obj.getSizeEmpls(); i++)
	{
		s << " " << obj.getEmployees()[i];
	}
	s << " " << obj.getSizePosts() << " ";
	for (int i = 0; i < obj.getSizePosts(); i++)
	{
		s << " " << obj.getPosts()[i];
	}
	return s;
}


std::istream & operator>>(std::istream &s, Sector &obj) {
	char* temp_c = new char[100];
	s >> temp_c;
	obj.setSectorName(temp_c);
	delete[] temp_c;

	Person tmp_Boss;
	s >> tmp_Boss;
	obj.setSectorBoss(tmp_Boss);

	int iTemp;
	s >> iTemp;
	obj.setSizeEmpls(iTemp);

	//............................
	Employee *tmp_Empls = new Employee[obj.getSizeEmpls()];
	for (int i = 0; i < obj.getSizeEmpls(); i++)
	{
		s >> tmp_Empls[i];
	}
	obj.setEmployees(tmp_Empls);
	delete[] tmp_Empls;

	s >> iTemp;
	obj.setSizePosts(iTemp);
	Post *tmp_Posts = new Post[obj.getSizePosts()];
	for (int i = 0; i < obj.getSizePosts(); i++)
	{
		s >> tmp_Posts[i];
	}
	obj.setPosts(tmp_Posts);
	delete[] tmp_Posts;
	return s;

}

void Sector::app_binary(ostream &out) {
	int iTemp;
	//name
	iTemp = strlen(this->sectorName);
	out.write((char*)&iTemp, sizeof(iTemp));
	out.write(this->sectorName, iTemp + 1);
	//boss
	this->sectorBoss.app_binary(out);
	//empls
	iTemp = sizeEmpl;
	out.write((char*)&sizeEmpl, sizeof(sizeEmpl)); // записали розмір 
	for (int i = 0; i < sizeEmpl; i++)
	{
		employees[i].app_binary(out);
	}
	////posts
	iTemp = sizePost;
	out.write((char*)&sizePost, sizeof(sizePost)); // записали розмір 
	for (int i = 0; i < sizePost; i++)
	{
		posts[i].app_binary(out);
	}
}

void Sector::read_binary(ifstream &in) {
	int iTemp;

	//name
	in.read((char*)&iTemp, sizeof(iTemp));
	char *temp_c = new char[iTemp + 1];
	in.read((char*)temp_c, iTemp + 1);
	this->setSectorName(temp_c);

	delete[] temp_c;
	temp_c = nullptr;

	//boss
	Person tmpBoss;
	tmpBoss.read_binary(in);
	this->setSectorBoss(tmpBoss);

	//empls
	in.read((char*)&sizeEmpl, sizeof(sizeEmpl)); //sizeE
	if (employees)
	{
		delete[]employees;
		employees = nullptr;
	}
	employees = new Employee[sizeEmpl];
	for (int i = 0; i < sizeEmpl; i++)
	{
		employees[i].read_binary(in);
	}


	in.read((char*)&sizePost, sizeof(sizePost)); //sizeP
	if (posts)
	{
		delete[]posts;
		posts = nullptr;
	}
	//HERE WAS BUG
	posts = new Post[sizePost];
	for (int i = 0; i < sizePost; i++)
	{
		posts[i].read_binary(in);
	}

}
