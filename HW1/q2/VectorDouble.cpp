/**
* @file VectorDouble.cpp
* @author Eric Park
* @Date   10/01/2017
* @version 1.0
*
* @brief <ENSC 251, HW1>
*
* @section DESCRIPTION
* Contains test program that tests VectorDouble class
*
**/

// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Oct. 1
//
// 301319654
#include <iostream>  
#include "VectorDouble.h"

using namespace std;

/*
* Main test function that implements VectorDouble class
* all descriptions of test performed are commented as cout
*/
int main()
{
	int vectorSize = 0;
	double vectorInput = 0.0;
	int vectorIndex = 0;
	
	
	
	cout << "/------------------------------------------------\\\n"
		<< "| VectorDouble test program                      |\n"
		<< "\\------------------------------------------------/\n";
		
	cout << "\ntest vector1 creation, size and capacity function" << endl;
	VectorDouble vector1(10);
	cout << "VectorDouble vector1(10);" << endl;
	cout << "vector1 has " << vector1.size() << " size and "
	<< vector1.capacity() << " capacity." << endl;
	vector1.resize(5);
	cout << "vector1.resize(5);" << endl;
	cout << "vector1 has " << vector1.size() << " size and "
	<< vector1.capacity() << " capacity." << endl;
	vector1.resize(7, 1.234);
	cout << "vector1.resize(7, 1.234);" << endl;
	cout << "vector1 has " << vector1.size() << " size and "
	<< vector1.capacity() << " capacity." << endl;
	vector1.reserve(20);
	cout << "vector1.reserve(20);" << endl;
	cout << "vector1 has " << vector1.size() << " size and "
	<< vector1.capacity() << " capacity." << endl;
	
	cout << "\noutput all elements in vector1" << endl;
	for (unsigned int i = 0; i < vector1.size(); i++)
	{
		cout << i << " index: " << vector1.value_at(i) << endl;
	}
	
	cout << "\ninitialize vector2 from input" << endl;
	cout << "Enter the size for initializing vector2: ";
	cin.clear();
	cin.sync();
	cin >> vectorSize;
	
	VectorDouble vector2(vectorSize);
	
	cout << "vector2 has " << vector2.size() << " size and "
	<< vector2.capacity() << " capacity." << endl;
		
	cout << "\ninput values to vector2, test push_back function"
		<< endl;
	while (vectorInput != -1.0)
	{
		cout << "\nEnter the values to input into the vector\n"
		<< " Enter -1.0 to stop input" << endl;
		cin.clear();
		cin.sync();
		cin >> vectorInput;
		if (vectorInput != -1.0)
		{
			vector2.push_back(vectorInput);
			cout << "vector2.push_back(vectorInput);" << endl;
		}
	}
	
	cout << "vector2 has " << vector2.size() << " size and "
	<< vector2.capacity() << " capacity." << endl;
		
	for (unsigned int i = 0; i < vector2.size(); i++)
	{
		cout << i << " index: " << vector2.value_at(i) << endl;
	}
	
	cout << "\nreplace values in vector2, test change_value_at"
		<< endl;
	while (vectorIndex != -1)
	{
		cout << "Enter the index to replace for vector2\n"
		<< " Enter -1 to stop input and ignore" << endl;
		cin.clear();
		cin.sync();
		cin >> vectorIndex;
		if (vectorIndex == -1)
		{
			continue;
		}
		if (vectorIndex >= (int)vector2.size() || vectorIndex < -1)
		{
			cout << "index out of bounds, try again" << endl;
			continue;
		}
		cin.clear();
		cin.sync();
		cout << "Enter the value to replace at index in vector2\n" << endl;
		cin >> vectorInput;
		vector2.change_value_at(vectorInput, vectorIndex);
		cout << "vector2.change_value_at(vectorInput, vectorIndex);" << endl;
		
		cout << "Your value in vector2 at index " << vectorIndex 
		<< " is " << vector2.value_at(vectorIndex) << endl;
	}
	cout << "\noutput changes to vector2" << endl;
	cout << "vector2 has " << vector2.size() << " size and "
	<< vector2.capacity() << " capacity." << endl;
	for (unsigned int i = 0; i < vector2.size(); i++)
	{
		cout << i << " index vector2: " << vector2.value_at(i) << endl;
	}


	cout << "\ntest resize function" << endl;
	cout << "Enter new size for vector2" << endl;
	cin.clear();
	cin.sync();
	cin >> vectorSize;
	cout << "Enter values to initialize with" << endl;
	cin.clear();
	cin.sync();
	cin >> vectorInput;

	cout << "vector2.resize(vectorSize, vectorInput);" << endl;
	vector2.resize(vectorSize, vectorInput);

	cout << "vector2 has " << vector2.size() << " size and "
	<< vector2.capacity() << " capacity." << endl;
	
	cout << "\ntest reserve function" << endl;
	cout << "Enter new capacity for vector2" << endl;
	cin.clear();
	cin.sync();
	cin >> vectorSize;
	vector2.reserve(vectorSize);
	cout << "vector2.reserve(vectorSize);" << endl;

	cout << "vector2 has " << vector2.size() << " size and "
	<< vector2.capacity() << " capacity." << endl;
	

	cout << "\ntest equality and assignnment operation" << endl;
	cout << "if (vector1 == vector2)" << endl;
	if (vector1 == vector2)
	{
		cout << "vector1 and vector2 is the same" << endl;
	}
	else 
	{
		cout << "vector1 and vector2 is different" << endl;
	}
	

	vector1 = vector2;
	cout << "vector1 = vector2;" << endl;
	
	if (vector1 == vector2)
	{
		cout << "vector1 and vector2 is the same" << endl;
	}
	else 
	{
		cout << "vector1 and vector2 is different" << endl;
	}

	cout << "\nresize vector1, test resize shrink" << endl;
	vector1.resize(2);
	cout << "vector1.resize(2);" << endl;
	for (unsigned int i = 0; i < vector1.size(); i++)
	{
		cout << i << " index vector1: " << vector1.value_at(i) << endl;
	}
	
	cout << "\ntest copy constructor" << endl;
	VectorDouble vector3 = vector2;
	cout << "VectorDouble vector3 = vector2;" << endl;

	for (unsigned int i = 0; i < vector3.size(); i++)
	{
		cout << i << " index vector2: " << vector3.value_at(i) << endl;
	}

	cout << endl;
	
	for (unsigned int i = 0; i < vector3.size(); i++)
	{
		cout << i << " index vector3: " << vector3.value_at(i) << endl;
	}

	cout << "\ntest complete" << endl;
		
	return 0;
}