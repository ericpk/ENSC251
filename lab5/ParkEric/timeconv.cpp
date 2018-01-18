/**
* @file timeconv.cpp
* @author Eric Park
* @Date   10/31/2017
* @version 1.0
*
* @brief <ENSC 251, lab5>
*
* @section DESCRIPTION
* converts 24-hour formatted time to 12-hour format
*
**/

// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Oct. 31
//
// 301319654
#include <iostream>
#include <string>

using namespace std;

//error class to be called when exception occurs
//the class essentially acts as a variable, since it does not
//matter what kind of error occurs
class TimeFormatMistake 
{
	public:
		TimeFormatMistake(); // empty default constructor
};

TimeFormatMistake::TimeFormatMistake()
{
	
}

int main()
{
	string inTime = "\0";
	bool errored = false;
	char zero = '0';
	int hour = 0;
	int minute = 0;
	char choice = '\0';
	while (true)
	{
		errored = false;
		hour = 0;
		minute = 0;
		cout << "Enter time in 24-hour notation (HH:MM):" << endl;
		cin.clear();
		cin.sync();
		cin >> inTime;

		try
		{
			//assumes that user enters HH:MM format, for example 01:23 instead of 1:23
			if (inTime.length() != 5)
			{
				throw TimeFormatMistake();
			}
			
			if (isdigit(inTime[0]) && isdigit(inTime[1]))
			{
				hour += (((int)inTime[0] - zero) * 10 + ((int)inTime[1]) - zero);
				if (hour < 0 || hour > 24)
				{
					throw TimeFormatMistake();
				}
			}
			else
			{
				throw TimeFormatMistake();
			}
			
			if (inTime[2] != ':')
			{
				throw TimeFormatMistake();
			}
			
			if (isdigit(inTime[3]) && isdigit(inTime[4]))
			{
				minute += (((int)inTime[3] - zero) * 10 + ((int)inTime[4]) - zero);
				if (minute < 0 || minute > 59)
				{
					throw TimeFormatMistake();
				}
			}
			
		}
		catch (TimeFormatMistake error)
		{
			cout << "There is no such time as " << inTime << endl;
			errored = true;

		}

		//convert the 24 hour notation to 12 hour, then output
		if (!errored)
		{
			cout << "That is the same as" << endl
			<< (hour > 12 ? hour - 12 : hour) << ":" << minute << (hour >= 12 ? " PM" : " AM") << endl;
		}
		
		while (true)
		{
			choice = '\0';
			cout << "Again?(y/n)" << endl;
			cin >> choice;
			cin.clear();
			cin.sync();
			if (choice == 'y')
			{
				break;
			}
			else if (choice == 'n')
			{
				cout << "End of program" << endl;
				return 0;
			}
			else
			{
				continue;
			}
		}

	}
	
	return 0;
} // end main