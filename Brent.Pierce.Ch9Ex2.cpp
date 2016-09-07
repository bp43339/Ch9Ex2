/******************************
* Pierce, Brent
* Chapter 9: Records (structs), Programming Exercise #2
* CSIS 223 Object-Oriented Programming
* Fall 2016
* This program reads and outputs students' names followed by their test scores,
* and outputs the highest score and name of the student(s) with that score
***********************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int NO_OF_STUDENTS = 20;	//establishes array of 20 components (for number of students)

struct studentType				//defines the struct variable as studentType and declares the struct variables
{
	string studentFName;
	string studentLName;
	int testScore;
	char grade;
};

void getData(ifstream& inFile, studentType sList[], int listSize);				//function to get input file of student list
void calculateGrade(studentType sList[], int listSize);							//function to calculate grade
int highestScore(const studentType sList[], int listSize);						//function to calculate highest score
void printResult(ofstream& outFile, const studentType sList[], int listSize);	//function to output the highest score and
																				//name of the student(s) with that score

int main()
{
	ifstream inData;
	ofstream outData;
	studentType studentList[NO_OF_STUDENTS];

	inData.open("Ch9_Ex2Data.txt");			//open the input file & if there's not an input file then the program terminates
	if (!inData)
	{
		cout << "The input file does not exist. Program terminates!" << endl;
		return 1;
	}

	outData.open("Ch9_Ex2Out.txt");		//opens the output file & if there's not an output file  the program terminates
	if (!outData)
	{
		cout << "Cannot open the output file. Program terminates!" << endl;
		return 1;
	}

	getData(inData, studentList, NO_OF_STUDENTS);
	calculateGrade(studentList, NO_OF_STUDENTS);
	printResult(outData, studentList, NO_OF_STUDENTS);

	return 0;
}

void getData(ifstream& inFile, studentType sList[], int listSize)
{
	for (int i = 0; i < listSize; i++)
		inFile >> sList[i].studentFName >> sList[i].studentLName >> sList[i].testScore;
}

void calculateGrade(studentType sList[], int listSize)
{
	for (int i = 0; i < listSize; i++)
	{
		switch (sList[i].testScore / 10)
		{
		case 10:
		case 9:
			sList[i].grade = 'A';
			break;
		case 8:
			sList[i].grade = 'B';
			break;
		case 7:
			sList[i].grade = 'C';
			break;
		case 6:
			sList[i].grade = 'D';
			break;
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		case 0:
			sList[i].grade = 'F';
		}
	}
}

int highestScore(const studentType sList[], int listSize)
{
	int hScore = sList[0].testScore;

	for (int i = 1; i < listSize; i++)
		if (hScore < sList[i].testScore)
			hScore = sList[i].testScore;

	return hScore;
}

void printResult(ofstream& outFile, const studentType sList[], int listSize)
{
	int maxScore = highestScore(sList, listSize);
	int i;

	outFile << left << setw(23) << "Student Name" << right << setw(5) << "Test Score  " << setw(5) << "Grade" << endl;

	for (i = 0; i < listSize; i++)
		outFile << left << setw(25)
		<< sList[i].studentLName + ", " + sList[i].studentFName
		<< right << " " << setw(5) << sList[i].testScore
		<< setw(6) << " " << sList[i].grade << endl;

	outFile << endl << "Highest Test Score: " << maxScore << endl;
	outFile << "Students having the highest test score:" << endl;

	for (i = 0; i < listSize; i++)
		if (sList[i].testScore == maxScore)
			outFile << sList[i].studentLName + ", " + sList[i].studentFName
			<< endl;
}