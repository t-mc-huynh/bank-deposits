#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct PERSON
{
	char Name[20];
	float Balance;
};

int linesOfData();
PERSON * readData(int & N);
string FindRichest(PERSON a[], int N);
void Deposit(string CustName, PERSON a[], int N);
void NewCopy(PERSON a[], int N);
void Display(PERSON a[], int N);

int main()
{
	int N = linesOfData();
	PERSON * personPtr;
	personPtr = readData(N);
	
	cout << "The customer with maximum balance is " << FindRichest(personPtr, N) << endl;

	string CustName;
	cout << "Enter your full name to deposit money: ";
	getline(cin, CustName);
	Deposit(CustName, personPtr, N);
	NewCopy(personPtr, N);
	Display(personPtr, N);
}

int linesOfData()
{
	fstream inFile;
	inFile.open("data.txt");
	int counter = 0;
	string temp;

	while (!inFile.eof())
	{
		getline(inFile, temp);
		counter++;
	}
	inFile.close();
	return counter;
}

PERSON * readData(int &N)
{
	PERSON * personPtr;
	personPtr = new PERSON[N];

	ifstream inFile;
	string dataFile = "data.txt";
	inFile.open("data.txt");

	//PERSON owner;
	string firstName, lastName;
	int i = 0;
	while (!inFile.eof())
	{
		inFile >> firstName >> lastName;
		inFile >> personPtr[i].Balance;
		string fullName = firstName + " " + lastName;
		strcpy(personPtr[i].Name, fullName.c_str()); // (string).c_str() turns a string into a character string
		i++;
	}

	return personPtr;
}

string FindRichest(PERSON a[], int N)
{
	// find max balance
	// Output:
	// The customer with maximum balance is Kimberly Macias
	int richest = 0;
	string name;
	for (int i = 0; i < N; i++)
	{
		if (a[i].Balance > richest)
		{
			richest = a[i].Balance;
			name = a[i].Name;
		}
	}
	return name;
}

void Deposit(string CustName, PERSON a[], int N)
{
	// Allow a customer to deposit money in his/her account.
	// Output:
	// Enter your full name to deposit money: Maria  Brown
	// Maria  Brown , how much would you like to deposit?  100
	// Now your new balance is 2200.90

	float deposit;
	cout << CustName << ", how much would you like to deposit?  ";
	cin >> deposit;

	for (int i = 0; i < N; i++)
	{
		if (strcmp(a[i].Name, CustName.c_str()) == 0)
		{
			a[i].Balance += deposit;
			cout << "Now your new balance is " << a[i].Balance << endl;
		}
	}
}

void NewCopy(PERSON a[], int N)
{
	ofstream outFile;
	outFile.open("data.txt");

	//  Copy array a in the same file
	for (int i = 0; i < N; i++)
	{
		outFile << a[i].Name << " ";
		outFile << a[i].Balance << endl;
	}

	cout << "File updated ... " << endl;
}

void Display(PERSON a[], int N)
{
	// 	Name           	  Balance
	// ----------------------------------------------
	// Maria  Brown  2100.90
	// Jeffrey  Jackson  200.20
	// Bernard  Smith  223.10
	// Matthew  Davenport  1630.20
	// Kimberly Macias  19100.90
	// Amber  Daniels  2400.40

	cout << "Name\t\t\tBalance" << endl;
	cout << "-----------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << left << setw(20) << a[i].Name << "\t";
		cout << "$" << fixed << setprecision(2) << setw(10) << a[i].Balance << endl;
	}
}