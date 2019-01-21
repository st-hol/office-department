#include "Date.h"
#include "MyExceptions.h"
#include <iostream>
#include <iomanip>

using namespace std;
#pragma warning(disable : 4996)
char* getTextInput(bool mustBeOnlyChar = false, int minLength = 1, int maxLength = 10);
double getNumInput(bool mustBePositive = true, int maxLength = 9, int minLength = 1, int maxVal = 99999999, int minVal = -99999999);
int getCurYear();

Date::Date() {
	day = 1;
	month = 1;
	year = 1970;
}
Date::Date(int day, int month, int year) {
	validate(day, month, year);
	this->day = day;
	this->month = month;
	this->year = year;
}
Date::Date(const Date &tmp) {
	this->day = tmp.day;
	this->month = tmp.month;
	this->year = tmp.year;
}

//перевірка високосного року 
//і поточного року
void Date::validate(int day, int month, int year)
{
	int monthArray[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		monthArray[1] = 29;// Якщо так, то 29 днів, якщо немає, то 28
		//рік ділиться на 400->високосний->кінець;
		//рік ділиться на 100 - »не високосний->кінець;
		//рік ділиться на 4->високосний->кінець;
	}

	if (day <= 0 || month <= 0 || year <= 0 || month > 12)
	{
		throw InvalidDate("<Non-existent Date Exception>\n", day, month, year);
	}

	if (day > monthArray[month - 1])
	{
		throw InvalidDate("<Non-existent Date Exception>\n", day, month, year);
	}
	//if (year > getCurYear()) //Дата нарождення/Дата влаштування на роботу < актуального року
	//{
	//	throw InvalidDate("<Not real Date Exception>\n", day, month, year);
	//}
}

void Date::printDate() {
	cout << day << "/" << month << "/" << year << endl;
}

int Date::getDay() {
	return day;
}
int Date::getMonth() {
	return month;
}
int Date::getYear() {
	return year;
}

void Date::setDay(int day)
{
	if ((day <= 0) || (day >= 32)) {
		cerr << "Day is limited between 1 and 31, you entered: " << day << endl;
		this->day = month = year = 0;
		return;
	}
	this->day = day;
}

void Date::setMonth(int month)
{
	if ((month <= 0) || (month >= 13)) {
		cerr << "Month is limited between 1 and 12, you entered: " << month << endl;
		day = this->month = year = 0;
		return;
	}
	this->month = month;
}

void Date::setYear(int year)
{
	if ((year <= 1899) || (year >= 2019)) {
		cerr << "year is limited between 1900 and 2018, you entered: " << year << endl;
		day = month = this->year = 0;
		return;
	}
	this->year = year;
}

//4.один з методів змінення з обмеженням можливих значень полів класу
void Date::enterDate()
{
	int iTemp;
	cout << "\n[Day]";
	iTemp = getNumInput(true, 9, 1, 31, 1);
	this->setDay(iTemp);
	cout << "\n[Month]";
	iTemp = getNumInput(true, 9, 1, 12, 1);
	this->setMonth(iTemp);
	cout << "\n[Year]";
	iTemp = getNumInput(true, 11, 1, getCurYear(), 1970);
	this->setYear(iTemp);
}

bool Date::operator == (const Date &d)
{
	return (day == d.day && month == d.month && year == d.year);
}

bool Date::operator<(const Date & d)
{
	if (year < d.year) return true;
	if (year > d.year) return false;
	if (month < d.month) return true;
	if (month > d.month) return false;
	return day < d.day;
}

Date & Date::operator=(const Date & other)
{
	if (this != &other) {
		this->day = other.day;
		this->month = other.month;
		this->year = other.year;
	}
	return *this;
}

void Date::app_binary(std::ostream & out)
{
	int iTemp;
	//boss date
	iTemp = this->getDay();
	out.write((char*)&iTemp, sizeof(iTemp));
	iTemp = this->getMonth();
	out.write((char*)&iTemp, sizeof(iTemp));
	iTemp = this->getYear();
	out.write((char*)&iTemp, sizeof(iTemp));
}

void Date::read_binary(std::ifstream & in)
{
	int iTemp;
	in.read((char*)&iTemp, sizeof(iTemp));
	this->day = iTemp;
	in.read((char*)&iTemp, sizeof(iTemp));
	this->month = iTemp;
	in.read((char*)&iTemp, sizeof(iTemp));
	this->year = iTemp;
}

std::ostream & operator<<(std::ostream &s, Date &obj) {
	s << setw(2) << obj.getDay() << " " << setw(2) << obj.getMonth() << " " << setw(4) << obj.getYear() << " ";
	return s;
}

istream & operator>>(istream &s, Date &obj) {
	int iTemp;
	s >> iTemp;
	obj.setDay(iTemp);
	s >> iTemp;
	obj.setMonth(iTemp);
	s >> iTemp;
	obj.setYear(iTemp);
	return s;
}

//void Date::setDate(int day, int month, int year)
//{
//	if ((day <= 0) || (day >= 32)) {
//		cerr << "Day is limited between 1 and 31, you entered: " << day << endl;
//		return;
//	}
//	this->day = day;
//	if ((month <= 0) || (month >= 13)) {
//		cerr << "Month is limited between 1 and 12, you entered: " << month << endl;
//		return;
//	}
//	this->month = month;
//	if ((year <= 1899) || (year >= 2019)) {
//		cerr << "year is limited between 1900 and 2018, you entered: " << year << endl;
//		return;
//	}
//	this->year = year;
//}


//
//void Date::readDate(void) {
//	char date1[11];
//	cout << "Enter a date in the form of dd/mm/yy\n";
//	cin.getline(date1, 11);
//	unsigned length = strlen(date1);
//	for (unsigned i = 0; i < length; ++i) {
//		if (isalpha(date1[i])) {
//			cerr << "Error: Alphabet character found: " << date1[i] << endl;
//			return;
//		}
//		if ((ispunct(date1[i])) && (date1[i] != '/')) {
//			cerr << "Illegal character: " << date1[i] << endl;
//			return;
//		}
//	}
//	convertDate(date1);
//}
//
//void Date::convertDate(char *date1) {
//	char *result;
//	result = strtok(date1, "/");
//	day = strtol(result, nullptr, 10);
//	result = strtok(nullptr, "/");
//	month = strtol(result, nullptr, 10);
//	result = strtok(nullptr, "/");
//	year = strtol(result, nullptr, 10);
//
//	if ((day <= 0) || (day >= 32)) {
//		cerr << "Day is limited between 1 and 31, you entered: " << day << endl;
//		day = month = year = 0;
//		return;
//	}
//	if ((month <= 0) || (month >= 13)) {
//		cerr << "Month is limited between 1 and 12, you entered: " << month << endl;
//		day = month = year = 0;
//		return;
//	}
//	if ((year <= 1899) || (year >= 2019)) {
//		cerr << "year is limited between 1900 and 2018, you entered: " << year << endl;
//		day = month = year = 0;
//		return;
//	}
//}
