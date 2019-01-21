#pragma once
#include "Degree.h"
#include "Post.h"
#include "Person.h"
#include "Employee.h"
#include "Sector.h"


#include <fstream>


class Sector
{
private:
	char* sectorName;
	Person sectorBoss;
	Employee *employees;
	int sizeEmpl;
	Post *posts;
	int sizePost;
public:
	Sector();
	Sector(char* sectorName, Person sectorBoss, Employee employees[], int sizeEmpl, Post posts[], int sizePost);
	Sector(const Sector & temp);
	~Sector();

	Post* getPosts();
	Employee* getEmployees();
	int getSizePosts();
	int getSizeEmpls();
	char* getSectorName();
	Person getSectorBoss();

	void setSectorName(char* sectorName);
	void setSectorBoss(Person sectorBoss);
	void setEmployees(Employee *employees);
	void setPosts(Post *posts);
	void setSizeEmpls(int sizeEmpl);
	void setSizePosts(int sizePost);

	void printSector();
	
	void addEmpl(Employee element);
	void addPost(Post element);
	void genSector(int nEmpls, int nPosts);
	void enterSector(int nEmpls, int nPosts);
	

	Sector & operator=(const Sector & other);
	friend std::ostream & operator<< (std::ostream &s, Sector &obj);
	friend std::istream & operator>> (std::istream &s, Sector &obj);

	
	Employee& operator[](int index);
	//void* operator[](int index);

	void app_binary(std::ostream &out);
	void read_binary(std::ifstream &in);
};

