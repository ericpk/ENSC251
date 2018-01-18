/**
* @file POSTNET.cpp
* @author Eric Park
* @Date   9/25/2017
* @version 1.0
*
* @brief <ENSC 251, HW1>
*
* @section DESCRIPTION
* Contains postNet class that Encodes and decodes zip code using POSTNET
* format, and a test function that utilizes this class
*
**/

// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Sept. 25
//
// 301319654

#include <iostream>  
#include <string>
#include <cctype>
#include <cmath>


using namespace std;

/*
* Class that stores POSTNET-formatted zip codes
* the post code is stored internally as barcode string
*/
class postNet
{
public:
	postNet();
	postNet(string);
	postNet(int);
	string encode();
	//Precondition: input should be an integer, 5 digits long unless starting
	// with zeros, if so, input should start at the first non-zero value
	// this is due to limitation with integer input
	//Postcondition: output will be 27-digit bar code represented in 
	// 0 for short bars, 1 for long bars
	int decode();
	//Precondition: input will be 27-digit bar code represented in 
	// 0 for short bars, 1 for long bars - will be checked for errors
	// internally
	//Postcondition: output will be 5 or less digits of integer, depending
	// on if value starts at zero - output will have to be formatted to be 5
	// digits if so
private:
	string input;
	void checkInput(int);
	void checkInput(string);
	string convert(int);
	int backConvert(string);
};

/*
* This constructor takes in barcode input directly
*/
postNet::postNet(string barInput)
{
	checkInput(barInput);
	input = barInput;
}

/*
* This constructor takes in integer input, converts it to binary
*/
postNet::postNet(int zipInput)
{
	checkInput(zipInput);
	input = convert(zipInput);
}

/*
* For debug only
*/
postNet::postNet()
{
	input = "null";
}


/*
* Main test function that implements postNet class
* This function does not format less-than-5 digit
* postal code output, nor does it check if
* postal code input is 5 digits long
*/
int main()
{
	string inputStr = "\0";
	string outputStr = "\0";
	int inputInt = 0;
	int outputInt = 0;
	char choice = '\0';

	cout << "/------------------------------------------------\\\n"
		<< "| POSTNET zip code converter                     |\n"
		<< "| Please choose from the following actions:      |\n"
		<< "|                                                |\n"
		<< "| 1 - Decode a zip code from barcode             |\n"
		<< "| 2 - Encode a zip code into barcode             |\n"
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
			cout << "Enter the 27 digit barcode\n"
				<< "represented in binary, no spaces:\n";
			cin.clear();
			cin.sync();
			cin.get();
			getline(cin, inputStr);
			postNet postCode(inputStr);
			outputInt = postCode.decode();
			cout << "The decoded zip code is: " << outputInt << endl;
			continue;
		}
		else if (choice == '2')
		{
			cout << "Enter the 5 digit zip code, no spaces:\n";
			// input is not validated in this function, assume
			// user inputs correct number
			cin.clear();
			cin.sync();
			cin >> inputInt;
			postNet postCode(inputInt);
			outputStr = postCode.encode();
			cout << "The encoded barcode is: " << outputStr << endl;
			continue;
		}
		else
		{
			cout << "ERROR: Invalid action, please try again\n";
			continue;

		}
	}
}

/*
* "Encodes" the postal code into binary barcode string,
* but since this is already done internally, just return
* the input
*/
string postNet::encode()
{
	return(input);
}

/*
* Decodes the postal code back to human-readable numbers
*/
int postNet::decode()
{
	return(backConvert(input));
}


/*
* Checks validity of the zip code integer input
* it cannot check the number of digits due to the
* input being an integer
*/
void postNet::checkInput(int inputInt)
{
	if (inputInt > 99999 || inputInt < 0)
	{
		cout << "ERROR: Zip code is out of range!\nTerminating\n";
		exit(EXIT_FAILURE);
	}
}

/*
* Checks validity of the barcode input:
* Make sure the input is exactly 27 characters long,
* first and last letters start with 1, and rest of the input
* contains only 0's and 1's, and the sum of 1's for each groups 
* of characters do not exceed 2
*/
void postNet::checkInput(string inputStr)
{
	int count = 0;

	if (inputStr.length() != 27)
	{
		cout << "ERROR: Barcode has incorrect length!\nTerminating\n";
		exit(EXIT_FAILURE);
	}
	else if (inputStr[0] != '1' || inputStr[26] != '1')
	{
		cout << "ERROR: Barcode not starting/ending with 1!\nTerminating\n";
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i < 26; i++)
	{
		if (inputStr[i] == '1')
		{
			count++;
		}
		else if (inputStr[i] != '0')
		{
			cout << "ERROR: Barcode contains incorrect values!\nTerminating\n";
			exit(EXIT_FAILURE);
		}
		if ((i % 5) == 0)
		{
			if (count != 2)
			{
				cout << "ERROR: Barcode value out of range!\nTerminating\n";
				exit(EXIT_FAILURE);
			}
			else
			{
				count = 0;
			}
		}
	}

}

/*
* Converts 5-digit integer input into barcode to be stored internally
*/
string postNet::convert(int postInt)
{
	string temp = "\0";
	string tempVal = "\0";
	string output = "\0";
	temp = to_string(postInt);
	int stringLength = temp.length();

	// Check if zip codes start with zeros,
	// as integer input cannot take account for this
	// if so, append zeros before input
	for (int i = 0; i < 5 - stringLength; i++)
	{
		tempVal.append("0");
	}
	tempVal.append(temp);

	output.append("1"); // barcodes always start and end with ones

	for(int i = 0; i < 5; i++)
	{
		switch(tempVal[i])
		{
		case '0': 
			{
				output.append("11000");
				continue;
			}
		case '1':
			{
				output.append("00011");
				continue;
			}
		case '2':
			{
				output.append("00101");
				continue;
			}
		case '3': 
			{
				output.append("00110");
				continue;
			}
		case '4': 
			{
				output.append("01001");
				continue;
			}
		case '5': 
			{
				output.append("01010");
				continue;
			}
		case '6': 
			{
				output.append("01100");
				continue;
			}
		case '7': 
			{
				output.append("10001");
				continue;
			}
		case '8': 
			{
				output.append("10010");
				continue;
			}
		case '9':
			{
				output.append("10100");
				continue;
			}
		}
	}

	output.append("1");
	return output;
}

/*
* Decodes the binary barcode stored internally back to integer output
*/
int postNet::backConvert(string postStr)
{
	int temp = 0;
	int output = 0;

	for(int i = 0; i < 5; i++)
	{
		temp = 0;
		temp += (static_cast<int>(postStr[1+(5*i)]) - static_cast<int>('0'))
			* 7;
		temp += (static_cast<int>(postStr[2+(5*i)]) - static_cast<int>('0'))
			* 4;
		temp += (static_cast<int>(postStr[3+(5*i)]) - static_cast<int>('0'))
			* 2;
		temp += (static_cast<int>(postStr[4+(5*i)]) - static_cast<int>('0'))
			* 1;
		if (temp == 11)
		{
			continue;
		}
		temp *= static_cast<int>(pow(10, (4-i)));
		output += temp;
	}

	return output;
}