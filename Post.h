#pragma once
#include <fstream>

class Post
{
private:
	char* postName;
	double salary;
public:
	Post();
	Post(char* postName, double salary);
	Post(const Post &tmp);
	~Post();

	void setPostName(char* postName);
	void setSalary(double salary);
	char* getPostName();
	double getSalary();
	void printPost();

	void enterPost();
	void genPost();

	Post & operator=(const Post & other);

	friend std::ostream & operator<< (std::ostream &s, Post &obj);
	friend std::istream & operator>> (std::istream &s, Post &obj);

	void app_binary(std::ostream &out);

	void read_binary(std::ifstream &in);
};

