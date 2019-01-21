#pragma once
#include <exception>
#include <iostream>

//10.застосування виключень, визначених як ієрархія класів
class InvalidDate :public std::exception {
private:
	int year, month, day;
	char* msg;
public:
	InvalidDate(char* _msg, int _day, int _month, int _year) : msg(_msg), day(_day), month(_month), year(_year) {}
	//virtual const char* what() const noexcept override
	const char* what() {return msg;}
	void showDataStatus(){ std::cout <<"\nDate which was entered: " << day << "/" << month << "/" << year << std::endl;}
};

class badSize :public std::exception
{
private:
	int size;
	char* msg;
public:
	badSize(char* _msg, int _size) : size(_size), msg(_msg) {};
	const char* what() {return msg;}
	void showDataStatus() { std::cout <<"\nSize which was entered: " <<"["<< size <<"]"<< std::endl; }
};

class badPath :public std::exception
{
private:
	char* msg;
public:
	badPath(char* _msg) : msg(_msg) {};
	const char* what() {return msg;}
};


