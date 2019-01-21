#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include "Degree.h"
#include "Department.h"
#include "tasks.h" /////twice not
using namespace std;
#pragma warning(disable : 4996)

void Tab(Department &dep);
char* getTextInput(bool mustBeOnlyChar = false, int minLength = 1, int maxLength = 10);
double getNumInput(bool mustBePositive = true, int maxLength = 9, int minLength = 1, int maxVal = 99999999, int minVal = -99999999);;

void SubMenu_Add(Department &dep);
void SubMenu_Add_Sector(Department &dep);
void SubMenu_Add_Employee(Department &dep);
void SubMenu_Add_Post(Department &dep);
void SubMenu_Record_toFile(Department &dep);
void SubMenu_Read_fromFile(Department &dep);

void ShowMenu(Department &dep) {
	rewind(stdin);
	system("cls"); 
	int choice = 0;
	cout << "[Operations on Department \"" << dep.getDepartmentName() << "\"]\n" << endl << endl;
	cout << "1] Add elements." << endl;
	cout << "2] Table display." << endl;
	cout << "3] Simple display." << endl;
	cout << "4] Recording to file." << endl;
	cout << "5] Reading from file." << endl;
	cout << "6] Find by numeric field." << endl;
	cout << "7] Find by text field." << endl;
	cout << "8] Average salaries and posts." << endl;
	cout << "9] Exit." << endl;
	cout << "\nYour choice >>";
	if (scanf("%d", &choice) != 1) { ShowMenu(dep); }
	else {
		switch (choice) {
		case 1: {
			SubMenu_Add(dep);
			break;
		}
		case 2: {
			Tab(dep);
			cout << "\nPress any button to return in main Menu." << endl;
			_getch();
			ShowMenu(dep);
			break;
		}
		case 3: {
			dep.printDepartment();
			cout << "\nPress any button to return in main Menu." << endl;
			_getch();
			ShowMenu(dep);
			break;
		}
		case 4: {
			SubMenu_Record_toFile(dep);
			break;
		}
		case 5: {
			SubMenu_Read_fromFile(dep);
			break;
		}
		case 6: {
			double iTemp = 0;
			iTemp = getNumInput(false, 17);
			FindEverything(dep, iTemp);
			cout << "\nPress any button to return in main Menu." << endl;
			_getch();
			ShowMenu(dep);
			break;
		}
		case 7: {
			char* temp_c = new char[100];
			temp_c = getTextInput(false, 1, 20);
			FindEverything(dep, temp_c);
			//delete[] temp_c;
			//temp_c = nullptr;
			cout << "\nPress any button to return in main Menu." << endl;
			_getch();
			ShowMenu(dep);
			break;
		}
		case 8: {
			if (!dep.getSizeSect()) {
				cout << "There is no sectors." << endl;
			}
			else {
				double *ans = new double[2];
				ans = Average<Department, double>(dep);
				cout << "Average of all salaries in department \"" << dep.getDepartmentName() << "\" = " <<ans[0]<< endl; //середня з.п. усіх Робітників
				cout << "Average quantity of posts in department \"" << dep.getDepartmentName() << "\" = " <<ans[1]<< endl; //середня кількість посад по Секторам

			}
			cout << "\nPress any button to return in main Menu." << endl;
			_getch();
			ShowMenu(dep);
			break;
		}
		case 9: { break; }
		default: {ShowMenu(dep); }
		}
	}
}

void SubMenu_Add(Department &dep) {
	rewind(stdin);
	system("cls"); 
	int choice = 0;
	cout << "[Adding elements]" << endl << endl;
	cout << "1] Add Sector." << endl;
	cout << "2] Add Employee to existing Sector." << endl;
	cout << "3] Add Post to existing Sector." << endl;
	cout << "4] to previous Menu." << endl;
	cout << "\nYour choice >>";
	if (scanf("%d", &choice) != 1) { SubMenu_Add(dep); }
	else {
		switch (choice) {
		case 1: {
			SubMenu_Add_Sector(dep);
			break;
		}
		case 2: {
			SubMenu_Add_Employee(dep);
			break;
		}
		case 3: {
			SubMenu_Add_Post(dep);
			break;
		}
		case 4: {
			ShowMenu(dep);
			break;
		}
		default: {SubMenu_Add(dep); }
		}
	}
}

void SubMenu_Add_Sector(Department &dep) {
	rewind(stdin);
	system("cls");
	int choice = 0;
	cout << "[Adding Sector to Department \"" << dep.getDepartmentName() << "\"]" << endl << endl;
	cout << "1] Input Sector manually." << endl;
	cout << "2] Generate random Sector." << endl;
	cout << "3] to previous Menu." << endl;
	cout << "\nYour choice >>";
	if (scanf("%d", &choice) != 1) { SubMenu_Add_Sector(dep); }
	else {
		switch (choice) {
		case 1: {
			int nSects, nEmpl, nPosts;
			cout << "\nHow many Sectors you want to add ?" << "\" [1 < N < 10]"; //\nYour choice >> ";
			nSects = getNumInput(true, 9,1,10,1);
			Sector tmp_Sector;
			for (int i = 0; i < nSects; i++)
			{
				cout << "\n\nProcessing [" << i + 1 << "] Sector." << endl;
				cout << "\nHow many Employees will be in your Sector ?" << " [1 < N < 10]";
				nEmpl = getNumInput(true, 9, 1, 10, 1);
				cout << "\nHow many Posts will be in your Sector ?" << " [1 < N < 10]";
				nPosts = getNumInput(true, 9, 1, 10, 1);
				tmp_Sector.enterSector(nEmpl, nPosts);
				dep.addSect(tmp_Sector);
			}
			cout << "\n[" << nSects << "] Sectors  were added to your Department." << "\nPress any button to return in main Menu." << endl;
			_getch();
			ShowMenu(dep);
			break;
		}
		case 2: {
			int nSects, nEmpl, nPosts;
			cout << "\nHow many Sectors you want to generate ?" << "\" [1 < N < 10]"; //Your choice >>";
			nSects = getNumInput(true, 9, 1, 10, 1);
			Sector tmp_Sector;
			cout << "\nHow many Employees will be in your Sectors ?"<<" [1 < N < 10]";
			nEmpl = getNumInput(true, 9, 1, 10, 1);
			cout << "\nHow many Posts will be in your Sectors ?" << " [1 < N < 10]";
			nPosts = getNumInput(true, 9, 1, 10, 1);
			for (int i = 0; i < nSects; i++)
			{
				tmp_Sector.genSector(nEmpl, nPosts);
				dep.addSect(tmp_Sector);
			}
			cout << "[" << nSects << "] Sectors were generated and added to your Department." << "\nPress any button to return in main Menu." << endl;
			_getch();
			ShowMenu(dep);
			break;
		}
		case 3: {
			SubMenu_Add(dep);
			break;
		}
		default: { SubMenu_Add_Sector(dep); }
		}
	}
}

void SubMenu_Add_Employee(Department &dep) {
	rewind(stdin);
	system("cls"); //ClearScreen(); 
	int choice = 0;
	cout << "[Adding Employee to existing Sector]" << endl << endl;
	cout << "1] Input Employee manually." << endl;
	cout << "2] Generate random Employee." << endl;
	cout << "3] to previous Menu." << endl;
	cout << "\nYour choice >>";
	if (scanf("%d", &choice) != 1) { SubMenu_Add_Employee(dep); }
	else {
		switch (choice) {
		case 1: {
			int indSect = 0, nEmpl = 0;
			if (!dep.getSizeSect())
			{
				cerr << "There is no sectors to add employees. You shold firstly create Sector!\n" << "\nPress any button to return in main Menu." << endl;
				_getch();
				ShowMenu(dep);
				break;
			}
			try
			{
				cout << "\nEnter Sector index(from 0) >>";
				//cin >> indSect;
				indSect = getNumInput(true, 14);
				cout << "\nHow many Employees you want Add to Sector \"" << dep[indSect].getSectorName() << "\" [1 < N < 10]";// << "?\nYour choice >>";
				//cin >> nEmpl;
				nEmpl = getNumInput(true, 9, 1, 10, 1);
				for (int i = 0; i < nEmpl; i++)
				{
					Employee tmp_Emp;
					tmp_Emp.enterEmpl();
					dep[indSect].addEmpl(tmp_Emp);
				}
				cout << "\n[" << nEmpl << "] Employees were generated and added to your Department." << "\nPress any button to return in main Menu." << endl;
			}
			catch (badSize except)
			{
				cerr << except.what();
				cerr << "\nThere isn't Sector with your Index.\n"; except.showDataStatus();
				cout << "\nPress any button to return in main Menu." << endl;
			}
			_getch();
			ShowMenu(dep);
			break;
		}
		case 2: {
			int indSect = 0, nEmpl = 0;
			if (!dep.getSizeSect())
			{
				cerr << "There is no sectors to add employees. You shold firstly create Sector!\n" << "\nPress any button to return in main Menu." << endl;
				_getch();
				ShowMenu(dep);
				break;
			}
			try
			{
				cout << "\nEnter Sector index(from 0)";
				indSect = getNumInput(true, 14);
				cout << "\nHow many Employees you want Add to Sector \"" << dep[indSect].getSectorName() <<"\" [1 < N < 10]";// << "?\nYour choice >>";
				nEmpl = getNumInput(true, 9, 1, 10, 1);
				for (int i = 0; i < nEmpl; i++)
				{
					Employee tmp_Emp;
					tmp_Emp.genEmpl();
					dep[indSect].addEmpl(tmp_Emp);
				}
				cout << "\n[" << nEmpl << "] Employees were generated and added to your Department." << "\nPress any button to return in main Menu." << endl;
			}
			catch (badSize except)
			{
				cerr << except.what();
				cerr << "\nThere isn't Sector with your Index.\n"; except.showDataStatus();
				cout << "\nPress any button to return in main Menu." << endl;
			}
			_getch();
			ShowMenu(dep);
			break;
		}
		case 3: {
			SubMenu_Add(dep);
			break;
		}
		default: { SubMenu_Add_Employee(dep); }
		}
	}
}
void SubMenu_Add_Post(Department &dep) {
	rewind(stdin);
	system("cls"); //ClearScreen(); 
	int choice = 0;
	cout << "[Adding Post to existing Sector]" << endl << endl;
	cout << "1] Input Post manually." << endl;
	cout << "2] Generate random Post." << endl;
	cout << "3] to previous Menu." << endl;
	cout << "\nYour choice >>";
	if (scanf("%d", &choice) != 1) { SubMenu_Add_Post(dep); }
	else {
		switch (choice) {
		case 1: {
			int indSect = 0, nPosts = 0;
			if (!dep.getSizeSect())
			{
				cerr << "There is no sectors to add employees. You shold firstly create Sector!\n" << "\nPress any button to return in main Menu." << endl;
				_getch();
				ShowMenu(dep);
				break;
			}
			try
			{
				cout << "\nEnter Sector index(from 0) >>";
				indSect = getNumInput(true, 14);
				cout << "\nHow many Posts you want Add to Sector \"" << dep[indSect].getSectorName() << "\" [1 < N < 10]"; 
				nPosts = getNumInput(true, 9, 1, 10, 1);
				for (int i = 0; i < nPosts; i++)
				{
					Post tmp_Post;
					tmp_Post.enterPost();
					dep[indSect].addPost(tmp_Post);
				}
				cout << "\n[" << nPosts << "] Posts were generated and added to your Department." << "\nPress any button to return in main Menu." << endl;
			}
			catch (badSize except)
			{
				cerr << except.what();
				cerr << "\nThere isn't Sector with your Index.\n"; except.showDataStatus();
				cout << "\nPress any button to return in main Menu." << endl;
			}

			ShowMenu(dep);
			break;
		}
		case 2: {
			int indSect = 0, nPosts = 0;
			if (!dep.getSizeSect())
			{
				cerr << "There is no sectors to add employees. You shold firstly create Sector!\n" << "\nPress any button to return in main Menu." << endl;
				_getch();
				ShowMenu(dep);
				break;
			}
			try
			{
				cout << "\nEnter Sector index(from 0) >>";
				indSect = getNumInput(true, 14);
				cout << "\nHow many Posts you want Add to Sector \"" << dep[indSect].getSectorName() << "\" [1 < N < 10]";
				nPosts = getNumInput(true, 9, 1, 10, 1);
				for (int i = 0; i < nPosts; i++)
				{
					Post tmp_Post;
					tmp_Post.genPost();
					dep[indSect].addPost(tmp_Post);
				}
				cout << "\n[" << nPosts << "] Posts were generated and added to your Department." << "\nPress any button to return in main Menu." << endl;
			}
			catch (badSize except)
			{
				cerr << except.what();
				cerr << "\nThere isn't Sector with your Index.\n"; except.showDataStatus();
				cout << "\nPress any button to return in main Menu." << endl;
			}
			_getch();
			ShowMenu(dep);
			break;
		}
		case 3: {
			SubMenu_Add(dep);
			break;
		}
		default: { SubMenu_Add_Post(dep); }
		}
	}
}

void SubMenu_Record_toFile(Department & dep) {
	rewind(stdin);
	system("cls"); //ClearScreen(); 
	int choice = 0;
	cout << "[Recording to File]" << endl << endl;
	cout << "1] Record to text File." << endl;
	cout << "2] Record to binary File." << endl;
	cout << "3] to previous Menu." << endl;
	cout << "\nYour choice >>";
	if (scanf("%d", &choice) != 1) { SubMenu_Record_toFile(dep); }
	else {
		switch (choice) {
		case 1: {
			try
			{
				dep.writeData_txt();
				cout << "Information stored to text File.\nPress any button to return in main Menu." << endl;
			}
			catch (badPath except)
			{
				cerr << except.what();
				cerr << "Process failed.\nPress any button to return in main Menu." << endl;
			}
			_getch();
			ShowMenu(dep);
			break;
		}
		case 2: {
			try
			{
				dep.serialize();
				cout << "Information stored to binary File.\nPress any button to return in main Menu." << endl;
			}
			catch (badPath except)
			{
				cerr << except.what();
				cerr << "Process failed.\nPress any button to return in main Menu." << endl;
			}
			_getch();
			ShowMenu(dep);
			break;
		}
		case 3: {
			ShowMenu(dep);
			break;
		}
		default: {SubMenu_Record_toFile(dep); }
		}
	}
}

void SubMenu_Read_fromFile(Department &dep) {
	rewind(stdin);
	system("cls"); //ClearScreen(); 
	int choice = 0;
	cout << "[Recording from File]" << endl << endl;
	cout << "1] Read from text File." << endl;
	cout << "2] Read from binary File." << endl;
	cout << "3] to previous Menu." << endl;
	cout << "\nYour choice >>";
	if (scanf("%d", &choice) != 1) { SubMenu_Read_fromFile(dep); }
	else {
		switch (choice) {
		case 1: {
			try
			{
				dep.readData_txt();
				cout << "Information  has been read from text File.\nPress any button to return in main Menu." << endl;
			}
			catch (badPath &except)
			{
				cerr << except.what();
				cerr << "Process failed.\nPress any button to return in main Menu." << endl;
			}
			_getch();
			ShowMenu(dep);
			break;
		}
		case 2: {
			try
			{
				dep.deserialize();
				cout << "Information has been read from binary File.\nPress any button to return in main Menu." << endl;
			}
			catch (badPath &except)
			{
				cerr << except.what();
				cerr << "Process failed.\nPress any button to return in main Menu." << endl;
			}
			_getch();
			ShowMenu(dep);
			break;
		}
		case 3: {
			ShowMenu(dep);
			break;
		}
		default: {SubMenu_Read_fromFile(dep); }
		}
	}
}
