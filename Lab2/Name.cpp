/**
* @file Name.cpp
* @author Eric Park
* @Date   9/20/2017
* @version 1.0
* @section DESCRIPTION 
*/
// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Sept. 20
//
// 301319654

#include <iostream>  
#include <string>
#include <cctype>
#include <ctype.h>

using namespace std; 

void toPigLatin(string& word);

int main()
{
	string firstName = "\0";
	string lastName = "\0";
	string fullName = "\0";
	char temp = '\0';

	
	//begin input of variables
	cout << "Enter your first name:";
	if (!cin >> firstName)
	{
		cout << "Error: input failed, terminating" << endl;
		return 1;
	}
	else
	{
		for (int i = 0; i < firstName.length(); i++)
		{
			if (firstName[i] == ' ' || firstName[i] == '	')
			{
				// Make sure name does not contain multiple words
				cout << "Error: Name must not contain any spaces or blanks, terminating" << endl;
				return 2;
			}
			else if (!isalpha(firstName[i]))
			{
				// Make sure name does not contain numbers/symbols/etc
				cout << "Error: Name must not contain non-letters, terminating" << endl;
				return 3;
			}
			else
			{
				// Convert strings into lowercase
				temp = firstName[i];
				firstName[i] = tolower(temp);
			}
		}
	}

	cout << "Enter your last name:";
	if (!cin >> lastName)
	{
		cout << "Error: input failed, terminating" << endl;
		return 1;
	}
	else
	{
		for (int i = 0; i < lastName.length(); i++)
		{
			if (lastName[i] == ' ' || lastName[i] == '	')
			{
				// Make sure name does not contain multiple words
				cout << "Error: Name must not contain any spaces or blanks, terminating" << endl;
				return 2;
			}
			else if (!isalpha(lastName[i]))
			{
				// Make sure name does not contain numbers/symbols/etc
				cout << "Error: Name must not contain non-letters, terminating" << endl;
				return 3;
			}
			else
			{
				// Convert strings into lowercase
				temp = lastName[i];
				lastName[i] = tolower(temp);
			}
		}
	}
	//convert names into Pig Latin
	toPigLatin(firstName);
	toPigLatin(lastName);
	
	
	//capitalize first letters
	firstName[0] = touper(firstName[0]);
	lastName[0] = toupper(lastName[0]);
	
	//combine first and last name
	fullName = firstName + " " + lastName;
	
	cout << "Your name in Pig Latin is: " << fullName << endl;
	cout << "terminating" << endl;
	
	return 0;
	
	

}

void toPigLatin(string& word)
{
	char temp = '\0';
	
	//begin vowel check for each word
	if (word[0] == 'a' || word[0] == 'e' || word[0] == 'i' || word[0] == 'o' || word[0] == 'u')
	{
		word += "way";
	}
	else
	{
		temp = word[0]; //first letter of word
		for (int i = 0; i < (word.length() - 1); i++)
		{
			word[i] = word[i+1]; //shift all elements one forward
		}
		word[word.length() - 1] = temp; //assign first letter to last element
		word += "ay"; //append 'ay'
	}
}
