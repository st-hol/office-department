#pragma once
#include <fstream>
#include <time.h>

class Date {
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int day, int month, int year);
	Date(const Date &tmp);

	void validate(int day, int month, int year);
	void enterDate();

	bool operator == (const Date &d);
	bool operator < (const Date &d);

	void printDate();
	int getDay();
	int getMonth();
	int getYear();
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);

	Date & operator=(const Date & other);
	friend std::ostream & operator<< (std::ostream &s, Date &obj);
	friend std::istream & operator>> (std::istream &s, Date &obj);
	void app_binary(std::ostream &out);
	void read_binary(std::ifstream &in);
};



