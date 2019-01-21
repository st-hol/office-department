#pragma once
#undef max
#include <iostream>
#include <iomanip>
#include "Department.h"
using namespace std;



////12. шаблон функції (застосування)
////функція додавання елемента до динамічного масиву
//template<typename T>
//void PushBack(T *&arr, int &size, T val)
//{
//	T *new_array = new T[size + 1];
//	for (int i = 0; i < size; i++)
//	{
//		new_array[i] = arr[i];
//	}
//	new_array[size] = val;
//	size++;
//	delete[]arr;
//	arr = new_array;
//}

//6. застосування перевантажених операторів;
double operator + (double num, Employee &obj){
	return num + obj.getPost().getSalary();
}
unsigned char operator += (unsigned char &num, Department &obj){
	num += obj.getSizeSect();
	return num;
}
unsigned char operator += (unsigned char &num, Sector &obj) {
	num += obj.getSizeEmpls();
	return num;
}
unsigned short operator += (unsigned short &num, Sector &obj) {
	num += obj.getSizePosts();
	return num;
}

//11. визначення шаблону функції для підрахунку статистичної характеристики
template<class ClassType, typename T>
T* Average(ClassType &obj) {
	T SumAllSalariesOfSector = 0;
	//Sector *sec_tmp = dep.getSectors();
	unsigned char nSectors = 0, nEmpls = 0;
	unsigned short nPosts = 0;
	nSectors += obj;

	for (int i = 0; i < nSectors; i++)	{
		//8.застосування перевантаженого оператора індексування;
		//Employee *tmp_Empls = obj[i].getEmployees();

		for (int j = 0; j < obj[i].getSizeEmpls(); j++)	{
			//SumAllSalariesOfSector = SumAllSalariesOfSector + tmp_Empls[j];
			SumAllSalariesOfSector = SumAllSalariesOfSector + obj[i][j];
		}
		
		/*nPosts += obj[i].getSizePosts();
		nEmpls += obj[i].getSizeEmpls();*/
		nPosts += obj[i];
		nEmpls += obj[i];
	}

	T* answer = new T[2];
	answer[0] = SumAllSalariesOfSector / nEmpls;
	answer[1] = nPosts / nSectors;
	return answer;
}


const bool operator == (double &num, Date &date){
	if (num == date.getDay() || num == date.getMonth() || num == date.getYear())
		return true;
	return false;
}

const bool operator == (double &num, Person &pers){
	if (num == pers.getBithDate())
		return true;
	return false;
}
const bool operator == (char *text, Person &pers){
	if (strcmp(text, pers.getName()) == 0 || strcmp(text, pers.getSurname()) == 0)
		return true;
	return false;
}

const bool operator == (double &num, Employee &pers)
{
	if (num == pers.getBithDate() || num == pers.getExp() || num == pers.getPost().getSalary())
		return true;
	return false;
}

const bool operator == (char *text, Employee &pers)
{
	if (strcmp(text, pers.getName()) == 0 || strcmp(text, pers.getSurname()) == 0 || strcmp(text, pers.getDegree().getDegreeName()) == 0 || strcmp(text, pers.getPost().getPostName()) == 0)
		return true;
	return false;
}


const bool operator == (double &num, Post &post)
{
	if (num == post.getSalary())
		return true;
	return false;
}

const bool operator == (char *text, Post &post)
{
	if (strcmp(text, post.getPostName()) == 0)
		return true;
	return false;
}

const bool operator == (char *text, Sector &sec)
{
	if (strcmp(text, sec.getSectorName()) == 0)
		return true;
	return false;
}

const bool operator == (double &num, Sector &sec){return false;}

template<typename Type>
void FindEverything(Department &obj, Type &searched)
{
	bool flag = false;
	for (int i = 0; i < obj.getSizeSect(); i++) {
		if (searched == obj[i])
		{
			flag = true;
			cout << searched << " is a name of Sector[" << i << "]" << endl << endl;
		}
		if (searched == obj[i].getSectorBoss())
		{
			flag = true;
			cout << searched << " was found in Boss of Sector[" << i << "]:" << endl << obj[i].getSectorBoss() << endl << endl;
		}
		for (int j = 0; j < obj[i].getSizeEmpls(); j++)
		{
			if (searched == obj[i].getEmployees()[j]) {
				flag = true;
				cout << searched << " was found in Employee[" << j << "] of Sector[" << i << "]:" << endl << obj[i].getEmployees()[j] << endl << endl;
			}
		}
		for (int j = 0; j < obj[i].getSizePosts(); j++)
		{
			/*	if (searched == obj[i].getPosts()[j].getSalary()) {*/
			if (searched == obj[i].getPosts()[j]) {
				flag = true;
				cout << searched << " was found in Post[" << j << "] of Sector[" << i << "]:" << endl << obj[i].getPosts()[j] << endl << endl;
			}
		}
	}
	if (!flag) { cout << "Nothing was found." << endl; }
}




//void findNumber(Department &obj, double searched)
//{
//	bool flag = false;
//	//if (searched == obj.getDepartmentBoss())
//	//{
//	//	flag = true;
//	//	cout << searched << " was found in Department Boss:" << endl << obj.getDepartmentBoss() << endl << endl;
//	//}
//	for (int i = 0; i < obj.getSizeSect(); i++) {
//		//if (searched == obj[i].getSectorBoss())
//		//{
//		//	flag = true;
//		//	cout << searched << " was found in Boss of Sector[" << i << "]:" << endl << obj[i].getSectorBoss() << endl << endl;
//		//}
//		for (int j = 0; j < obj[i].getSizeEmpls(); j++)
//		{
//			if (searched == obj[i].getEmployees()[j]) {
//				flag = true;
//				cout << searched << " was found in Employee[" << j << "] of Sector[" << i << "]:" << endl << obj[i].getEmployees()[j] << endl << endl;
//			}
//		}
//		for (int j = 0; j < obj[i].getSizePosts(); j++)
//		{
//			/*	if (searched == obj[i].getPosts()[j].getSalary()) {*/
//			if (searched == obj[i].getPosts()[j]) {
//				flag = true;
//				cout << searched << " was found in Post[" << j << "] of Sector[" << i << "]:" << endl << obj[i].getPosts()[j] << endl << endl;
//			}
//		}
//	}
//	if (!flag) { cout << "Nothing was found." << endl; }
//}
//
//void findText(Department &obj, char* searched)
//{
//	bool flag = false;
//	//if (strcmp(searched, obj.getDepartmentName()) == 0)
//	//{
//	//	flag = true;
//	//	cout << searched << " is a name of Department" << endl << endl;
//	//}
//	//if (searched == obj.getDepartmentBoss())
//	//{
//	//	flag = true;
//	//	cout << searched << " was found in Department Boss:" << endl << obj.getDepartmentBoss() << endl << endl;
//	//}
//	for (int i = 0; i < obj.getSizeSect(); i++) {
//
//		//if (strcmp(searched, obj[i].getSectorName()) == 0)
//		//{
//		//	flag = true;
//		//	cout << searched << " is a name of Sector[" << i << "]" << endl << endl;
//		//}
//		/*if (searched == obj[i].getSectorBoss())
//		{
//			flag = true;
//			cout << searched << " was found in Boss of Sector[" << i << "]:" << endl << obj[i].getSectorBoss() << endl << endl;
//		}*/
//		for (int j = 0; j < obj[i].getSizeEmpls(); j++)
//		{
//			if (searched == obj[i].getEmployees()[j]) {
//				flag = true;
//				cout << searched << " was found in Employee[" << j << "] of Sector[" << i << "]:" << endl << obj[i].getEmployees()[j] << endl << endl;
//			}
//		}
//		for (int j = 0; j < obj[i].getSizePosts(); j++)
//		{
//			/*if (strcmp(searched, obj[i].getPosts()[j].getPostName()) == 0) {*/
//			if (searched == obj[i].getPosts()[j]) {
//				flag = true;
//				cout << searched << " was found in Post[" << j << "] of Sector[" << i << "]:" << endl << obj[i].getPosts()[j] << endl << endl;
//			}
//		}
//	}
//	if (!flag) { cout << "Nothing was found." << endl; }
//}





//template <typename Type>
//const bool operator == (Type searched, Employee &pers)
//{
//	if (typeid(searched).name() == typeid(double).name())
//	{
//		double* new_d = dynamic_cast<double>(searched); // downcast
//
//		if (searched == pers.getExp() || searched == pers.getPost().getSalary())
//			return true;
//		return false;
//	}
//	if (typeid(searched).name() == typeid(char*).name())
//	{
//		if (strcmp(searched, pers.getName()) == 0 || strcmp(searched, pers.getSurname()) == 0 || strcmp(searched, pers.getDegree().getDegreeName()) == 0 || strcmp(searched, pers.getPost().getPostName()) == 0)
//			return true;
//		return false;
//	}
//}
//template <typename Type>
//const bool operator == (Type searched, Post &post)
//{
//	if (typeid(searched).name() == typeid(double).name())
//	{
//		if (searched == post.getSalary())
//			return true;
//		return false;
//	}
//	if (typeid(searched).name() == typeid(char*).name())
//	{
//		if (strcmp(searched, post.getPostName()) == 0)
//			return true;
//		return false;
//	}
//}
