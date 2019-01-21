#pragma once
#include "MyExceptions.h"
#include "Person.h"
#include "Sector.h"
#include <fstream>

class Department
{
private:
	char* departmentName;
	Person departmentBoss;
	int sizeSect;
	Sector *sectors;
public:
	Department();
	Department(char* departmentName, Person departmentBoss, Sector sectors[], int sizeSect);
	Department(const Department& tmp);
	~Department();

	void setDepartmentName(char* departmentName);
	void setDepartmentBoss(Person departmentBoss);
	void setSectors(Sector *sectors);
	void setSizeSect(int sizeSect);

	void printDepartment();
	void addSect(Sector element);

	Sector* getSectors();
	int getSizeSect();
	Person getDepartmentBoss();
	char* getDepartmentName();

	//7. визначення перевантаженого оператора індексування для внутрішнього динамічного масиву, для якого слід виділити мінімальну потрібну пам’ять;
	Sector & operator[](int index);

	friend std::ostream & operator<< (std::ostream &s, Department &obj);
	friend std::istream & operator>> (std::istream &s, Department &obj);

	Department & operator=(const Department & other);


	bool writeData_txt();
	bool readData_txt();
	bool serialize();
	bool deserialize();

};




