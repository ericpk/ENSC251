/**
* @file gradeHistogram.cpp
* @author Eric Park
* @Date   9/26/2017
* @version 1.0
*
* @brief <ENSC 251, lab3>
*
* @section DESCRIPTION
* outputs a histogram from an input of student grades
*
**/

// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Sept. 26
//
// 301319654

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//main function begin
int main()
{
	const int MAX_GRADE = 100;
	int histoIndex = 0;
	int input = 0;
	int prevGrade = 0;
	int *histogram;
	vector<int> grades;
	
	cout << "/------------------------------------------------\\\n"
		<< "| Grade Histogram maker                          |\n"
		<< "| Please enter the student's grades in           |\n"
		<< "| integer format                                 |\n"
		<< "| Enter -1 to end input                          |\n"
		<< "\\------------------------------------------------/\n";
	while (true)
	{
		//do some error checks before entering values
		if (!(cin >> input))
		{
			cout << "ERROR READING VALUES, terminating" << endl;
			return 1;
		}
		
		if (input < -1)
		{
			cout << "ERROR - grade cannot be negative, terminating" << endl;
			return 2;
		}
		else if (input > MAX_GRADE)
		{
			cout << "ERROR - grade cannot be >100, terminating" << endl;
			return 3;
		}
		if (input == -1)
		{
			break;
		}
		grades.push_back(input);
	}
	
	sort(grades.begin(), grades.end());
	
	//maximum number of elements in histogram is number of elements in grades
	histogram = new int[grades.size()];
	
	//initialize histogram array
	for (unsigned int j = 0; j < grades.size(); j++)
	{
		histogram[j] = {0};
	}
	
	prevGrade = -1;
	
	//begin histogram computation
	for (unsigned int i = 0; i < grades.size(); i++)
	{
		if (!(prevGrade == -1))
		{
		histogram[histoIndex]++;
		}
		
		if (prevGrade != grades[i] && prevGrade != -1)
		{
			cout << "Number of " << prevGrade << "'s: " 
			<< histogram[histoIndex] << endl;
			histoIndex++;
		}
		//special case when at the last element
		//needed to display the proper last grade
		if (i == grades.size() - 1)
		{
			histogram[histoIndex]++;
			cout << "Number of " << grades[i] << "'s: " 
			<< histogram[histoIndex] << endl;
			break;
		}
		prevGrade = grades[i];
	}
	
	delete [] histogram;
	histogram = NULL;
	
	return 0;

}
