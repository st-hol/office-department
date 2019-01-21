#pragma once
#include <fstream>
class Degree
{
private:
	char* degree;
public:
	Degree();
	Degree(char* degree);
	Degree(const Degree & tmp);
	~Degree();

	void setDegreeName(char* degree);
	char* getDegreeName();
	void enterDegree();
	void printDegree();

	Degree & operator=(const Degree & other);
	friend std::ostream & operator<< (std::ostream &s, Degree &obj);
	friend std::istream & operator>> (std::istream &s, Degree &obj);
	void app_binary(std::ostream &out);
	void read_binary(std::ifstream &in);
};

