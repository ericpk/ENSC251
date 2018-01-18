/**
* @file quick_sort.cpp
* @author Eric Park
* @Date   9/26/2017
* @version 1.0
*
* @brief <ENSC 251, lab3>
*
* @section DESCRIPTION
* fixed quick sort algorithm for input.txt
*
**/

/*quick sort algorithm */ 

//Read Quick Sort Algorithm from wikipedia
/*
The code is close but it has some errors so it is not doing 
what it is supposed to do. Read the Quick Sort Algorithm 
and debug the code to print the correct output.

Also write the code for reading the numbers from the file "input.txt" 
provided in the folder "prob2" 
NOTE:- DO NOT hardcode the size of the file . Create a constant variable 
max_length = 200, which will be the maximum size of the file.
//---------------------------------------------------------------
NOTE: DO NOT ADD ANY COUT STATEMENTS IN THE FINAL SUBMISSION 
OF THE CODE. ALSO, DO NOT MODIFY THE SEQUENCE OF THE INPUT, OR 
CHANGE THE INPUT 
//---------------------------------------------------------------
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std; 

void print_array(int array[], int low, int hi) 
{ 
	cout<< "quick sort partition steps: ";
	for (int j=low; j<=hi;j++) 
		cout <<" "<< array[j]; 
	cout << endl;
}//end of print_array 

// swap is a preexisting function - std::swap
// rename it to arraySwap and all its instances
// also, move it above partition function
void arraySwap (int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
	
	//arr[i] = arr[j];
	//arr[j] = arr[i];
	// original swap implementation - this overwrites original values
	
	return;
}

int partition (int arr[], int low, int hi)
{
	int pivot = arr[hi];
	int i = low - 1;
	// int i = low; - this 
	
	for (int j = low; j < hi; j++)
	{
		// if (arr[j] <= pivot) - ORIGINAL
		if (arr[j] < pivot)
		{
			// i++; is moved from after swap() to before
			i++;
			arraySwap(arr, i, j);
		}
	}
	print_array(arr, low, hi); 
	// arr[hi + 1] -  hi + 1 is incorrect, may access out-of-index values
	if (arr[hi] < arr[i + 1])
	{
		//swap(arr, i, hi); - ORIGINAL
		arraySwap(arr, i + 1, hi);
	}
	//return i; - returning i will not work
	return i + 1;
}
		
void quick_sort(int arr[], int low, int high) 
{ 
	int pivot;
	
	//if (low < hi) - hi is not defined
	if (low < high)
	{
		pivot = partition(arr, low, high);
		quick_sort(arr, low, pivot-1);
		//quicksort(arr, pivot+1, high) - quicksort is undefined
		quick_sort(arr, pivot+1, high);
	}
	
	return;
}
	
	int main() 
	{ 
		const int MAX_SIZE = 200;
	
		int size;
		ifstream inputFile;
		//DECLARE YOUR ARRAY HERE:
		int array[MAX_SIZE] = {0};
		
		inputFile.open("input.txt");
		if (inputFile.fail())
		{
			//cout << "ERROR READING input.txt" << endl;
			return 1;
		}

		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (!(inputFile >> array[i]))
			{
				if (inputFile.eof())
				{
					inputFile.close();
					size = i;
					break;
				}
				//cout << "ERROR READING VALUES" << endl;
				inputFile.close();
				return 2;
			}
		}
		//function was originally called with incorrect number of arguments
		print_array(array, 0, size - 1); 
		quick_sort(array, 0, size - 1); 
		print_array(array, 0, size - 1); 
		return 0;
	}//end of main
