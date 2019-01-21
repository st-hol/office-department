#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include "Degree.h"
#include "Department.h"
using namespace std;
#pragma warning(disable : 4996)

int randSalary()
{
	return 100 + rand() % 900 + 1;
}

char* randText()
{
	int size = 5 + rand() % 5;
	char *name = new char[size];
	name[0] = 'A' + rand() % 26;
	for (int i = 1; i < size - 1; i++)
	{
		name[i] = 'a' + rand() % 26;
	}
	name[size - 1] = '\0';
	return name;
}


void Tab(Department &obj) {
	int lenDep = 60, lenSec = 62, lenEmpl = 115, lenPost = 34;
	cout.setf(ios::right);

	for (int i = 0; i < lenDep; i++) { cout << '-'; }
	cout << "\n| Department Name |            Department BOSS             | \n";
	for (int i = 0; i < lenDep; i++) { cout << '-'; }cout << "\n";
	cout << "|" << setw(17) << obj.getDepartmentName() << "|" << obj.getDepartmentBoss() << "|\n";
	for (int i = 0; i < lenDep; i++) { cout << '-'; }cout << "\n";

	//cout << "\nList of sectors: " << "\n";
	for (int j = 0; j < obj.getSizeSect(); j++) {
		for (int i = 0; i < lenSec; i++) { cout << '-'; }
		cout << "\n|  N  | Sector Name |               Sector Boss              | \n";
		for (int i = 0; i < lenSec; i++) { cout << '-'; }cout << "\n";
		cout << "|" << setw(5) << j + 1 << "|" << setw(13) << obj[j].getSectorName() << "|" << obj[j].getSectorBoss() << "|\n";
		for (int i = 0; i < lenSec; i++) { cout << '-'; }cout << "\n";

		if (obj[j].getSizeEmpls())
		{
			cout << "\nList of employees for Sector[" << j + 1 << "]\n";
			for (int i = 0; i < lenEmpl; i++) { cout << '-'; }
			cout << "\n|  N  |                Employee                |    Post    | Salary | Scientific Degree | Experience | Empl.Date | \n";
			for (int i = 0; i < lenEmpl; i++) { cout << '-'; }cout << "\n";
			Employee* tmp_Emp = obj[j].getEmployees();
			for (int k = 0; k < obj[j].getSizeEmpls(); k++) {
				cout << "|" << setw(5) << k + 1 << "|" << (Person)tmp_Emp[k] << "|" << setw(12) << tmp_Emp[k].getPost().getPostName() << "|"
					<< setw(8) << tmp_Emp[k].getPost().getSalary() << "|"
					<< setw(18) << tmp_Emp[k].getDegree() << "|" << setw(12) << tmp_Emp[k].getExp() << "|" << setw(0) << tmp_Emp[k].getEmploymentDate() << "|\n";
			}
			for (int i = 0; i < lenEmpl; i++) { cout << '-'; }cout << "\n";
			cout << "\n";
		}
		if (obj[j].getSizePosts())
		{
			cout << "\nList of posts for Sector Number[" << j + 1 << "]\n";
			for (int i = 0; i < lenPost; i++) { cout << '-'; }
			cout << "\n|  N  |  Post Name  |   Salary   | \n";
			for (int i = 0; i < lenPost; i++) { cout << '-'; }cout << "\n";
			Post* tmp_Pst = obj[j].getPosts();
			for (int k = 0; k < obj[j].getSizePosts(); k++) {
				cout << "|" << setw(5) << k + 1 << "|" << setw(13) << tmp_Pst[k].getPostName() << "|" << setw(12) << tmp_Pst[k].getSalary() << "|\n";
			}
			for (int i = 0; i < lenPost; i++) { cout << '-'; }cout << "\n";
			cout << "\n";
		}
		for (int i = 0; i < lenEmpl; i++) { cout << '_'; }cout << "\n\n";
	}
	cout << "\n";
}


bool correct(char symbol)
{
	if (symbol >= 65 && symbol <= 90 || symbol >= 97 && symbol <= 122 || symbol == 45 || symbol == 39) {
		return true;
	}
	return false;
}


char* getTextInput(bool mustBeOnlyChar = false, int minLength = 1, int maxLength = 10)
{
	rewind(stdin);
	bool flag;
	char* temp_c = new char[maxLength+2];// +1 for \0 and +1 to check if it >max
	do
	{
		flag = true;
		cout << "\nYour value " << "(Length: from " << minLength << " to " << maxLength << ") ";
		if (mustBeOnlyChar) { cout << "(Only A-Z, a-z, -, ')"; }
		cout << " >>";

		cin.getline(temp_c, maxLength+2);
		cin.clear();
		//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (strlen(temp_c) > maxLength){
			//rewind(stdin);
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (mustBeOnlyChar) {
			for (int i = 0; i < strlen(temp_c); i++) {
				if (!correct(temp_c[i])) {
					flag = false;
					break;
				}
			}
		}
	} while (strlen(temp_c) > maxLength || strlen(temp_c) < minLength || flag == false);
	return temp_c;
}

double getNumInput(bool mustBePositive = true, int maxLength = 9, int minLength = 1, int maxVal = 99999999, int minVal = -99999999) {
	
	string inp;
//	int res;
	bool flag;
	double val;
	do
	{
		rewind(stdin);
		flag = true;
		cout << "\nYour value >>";
		if (cin >> val) {}
		else
		{
			//cout << "\nWrong input.\n" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (mustBePositive) if (val < 0) flag = false;
		inp = to_string(val);
		//cout << "LENGTH: " << inp << " is " << inp.length() << endl;
	} while (inp.length() > maxLength || inp.length() < minLength || !flag || val > maxVal || val < minVal);
	return val;
}

int getCurYear() {
	time_t t;
	time(&t);
	return localtime(&t)->tm_year + 1900;
}