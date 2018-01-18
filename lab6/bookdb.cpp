/**
* @file bookdb.cpp
* @author Eric Park
* @Date   11/17/2017
* @version 1.0
*
* @brief <ENSC 251, lab3>
*
* @section DESCRIPTION
* stores and sorts a database of books containing its title, author, and date
*
**/

// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Nov. 17, 2017
//
// 301319654

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/*
* Class that stores book information
*/
class book
{
public:
	//default constructor, won't be used
	book();
	//constructor for proper input
	//user is expected to input comprehensible data
	book(string authorName, string bookName, string bookDate);
	
	void printBook() const;
	
	//used for sorting the books based on title
	//NOTE: it uses sorting based ASCII alphabetical order,
	//numbers will not be properly sorted numerically
	bool operator< (const book &comp) const;
private:
	string name;
	string title;
	string date;
};

book::book() 
{
	name = "Unknown";
	title = "An Unnamed Book";
	date = "Beginning of History";
}

book::book(string authorName, string bookName, string bookDate) 
{
	name = authorName;
	title = bookName;
	date = bookDate;
}

void book::printBook() const
{
	cout << name << ". " << title << ". " << date << "." << endl;
}

bool book::operator< (const book &comp) const
{
	return (name.compare(comp.name) < 0);
}

//main function begin
int main()
{
	book* newBook;
	vector<book> bookList;
	vector<book>::iterator books;
	string inputName = "\0";
	string inputAuthor = "\0";
	string inputDate = "\0";
	char choice = '\0';

	cout << "/------------------------------------------------\\\n"
		<< "| Book Database Manager                          |\n"
		<< "| Please choose from the following actions:      |\n"
		<< "|                                                |\n"
		<< "| 1 - Add new book to database                   |\n"
		<< "| 2 - Print listing sorted by author             |\n"
		<< "| 3 - Cancel and Exit                            |\n"
		<< "\\------------------------------------------------/\n";
	while(true)
	{
		cout << "\nEnter your choice: ";
		cin.clear();
		cin.sync();
		cin >> choice;
		if (choice == '3')
		{
			cout << "Terminating\n";
			return 1;
		}
		else if (choice == '1')
		{
			cout << "Enter title:\n";
			cin.get();
			getline(cin, inputName);
			cout << "Enter author:\n";
			getline(cin, inputAuthor);
			cout << "Enter date:\n";
			getline(cin, inputDate);
			
			newBook = new book(inputAuthor, inputName, inputDate);
			bookList.push_back(*newBook);

			sort(bookList.begin(), bookList.end());
			continue;
		}
		else if (choice == '2')
		{
			cout << "Books in database are:" << endl;
			
			for (books = bookList.begin(); books != bookList.end(); books++)
			{
				books->printBook();
			}
			continue;
		}
		else
		{
			cout << "ERROR: Invalid action, please try again\n";
			continue;

		}
	}
	return 0;
}

