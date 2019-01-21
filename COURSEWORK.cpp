#include <iostream>
#include "Department.h"

void ShowMenu(Department &dep);
int main()
{
	//Date d;
	//d.setMonth(13);
	//d.printDate();
	//d.setMonth(11);
	//d.printDate();
	//system("pause");
	//system("mode con cols=150 lines=40");
	//system("pause");
	Department department;
	department.setDepartmentName("My_Dprt");
	department.setDepartmentBoss(Person("Stanislav", "Holovachuk", Date(20, 4, 2000)));
	ShowMenu(department);
	return 0;
}

