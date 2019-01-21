#pragma once
#include "Person.h"
#include <fstream>

//1.приклад успадковування
class Employee : public Person {
private://2.приклад агрегації
	Post post;
	Degree degree;
	int exp;
	Date employmentDate;
public:
	Employee();
	Employee(char* name, char* surname, Date bdate, Post post, Degree degree, int exp, Date employmentDate);
	Employee(const Employee & tmp);
	~Employee();

	void setPost(Post post);
	void setDegree(Degree degree);
	void setExp(int exp);
	void setEmploymentDate(Date employmentDate);
	void enterEmpl();
	void genEmpl();

	Post getPost();
	Degree getDegree();
	int getExp();
	Date getEmploymentDate();

	Employee & operator=(const Employee & other);
	void printEmployee();
	friend std::ostream & operator<< (std::ostream &s, Employee &obj);
	friend std::istream & operator>> (std::istream &s, Employee &obj);
	void app_binary(std::ostream &out);
	void read_binary(std::ifstream &in);
};
