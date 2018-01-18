/**
* @file grid.h
* @author Eric Park
* @Date   10/22/2017
* @version 1.0
*
* @brief <ENSC 251, HW2>
*
* @section DESCRIPTION
* Class definition for grid class, used to set up a square array that can
* act both as 1D and 2D array
*
**/

// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Oct. 22
//
// 301319654
#ifndef GRID_H
#define GRID_H
#include <iostream>

using namespace std;
namespace grids
{	
	class grid2D
	{
	public:
		//default constructor, initializes to 20*20 grid of 400 elements
		grid2D();
		//creates a grid of size*size elements
		grid2D(int dimen);
		//copy constructor
		grid2D(grid2D &aGrid);
		//destructor
		~grid2D();
		
		//displays the grid as 2D in cout
		void displayGrid();
		//sets value at pos, acts as 1D array
		void setValue(int pos, int value);
		//sets value at (x,y), acts as 2D array
		void setValue(int x, int y, int value);
		//returns the dimension of the grid
		int getSize();
		
		//returns X and Y position from given 1D index
		int getXPos(int pos);
		int getYPos(int pos);
		
		//returns the 1D index equivalent from 2D position
		int xyToIndex(int x, int y);
		//counts the number of 'valueToCount' stored in grid
		int countIndex(int valueToCount);
		//overloads round bracket, acts as square brackets for array
		int operator()(int pos);
		//overloads round bracket to act like 2D array
		int operator()(int x, int y);
	protected:
		int *index;
		int size;
	};
	
	grid2D::grid2D()
	{
		size = 20;
		int numIndex = 400;
		index = new int[numIndex];
		
		for (int i = 0; i < (numIndex); i++)
		{
			index[i] = 0;
		}
	}
	
	grid2D::grid2D(int dimen)
	{
		if (dimen <= 0)
		{
			dimen = 20;
		}
		int size = dimen;
		int numIndex = size * size;
		index = new int[numIndex];
		
		for (int i = 0; i < numIndex; i++)
		{
			index[i] = 0;
		}
	}
	
	grid2D::grid2D(grid2D &aGrid)
	{
		size = aGrid.size;
		int numIndex = size * size;
		index = new int[numIndex];
		
		for (int i = 0; i < numIndex; i++)
		{
			index[i] = aGrid.index[i];
		}
		
	}
	
	grid2D::~grid2D()
	{
		delete[] index;
	}
		
	void grid2D::displayGrid()
	{
		int numIndex = size * size;
		cout << endl;
		for (int i = 0; i < numIndex; i++)
		{
			cout << index[i];
			if ((i + 1) % size == 0)
			{
				cout << endl;
			}
		}
	}
	
	void grid2D::setValue(int pos, int value)
	{
		index[pos] = value;
	}
	
	void grid2D::setValue(int x, int y, int value)
	{
		if (x >= 0 && x < size && y >= 0 && y < size)
		{
			int pos = x + y * size;
			index[pos] = value;
		}
	}
	
	int grid2D::getSize()
	{
		return size;
	}
	
	int grid2D::getXPos(int pos)
	{
		return pos % size; 
	}
	
	int grid2D::getYPos(int pos)
	{
		return (pos - (pos % size)) / size;
		
	}
	
	int grid2D::xyToIndex(int x, int y)
	{
		if (x >= 0 && x < size && y >= 0 && y < size)
		{
			return x + y * size;
		}
		return -1;
	}
	
	int grid2D::countIndex(int valueToCount)
	{
		int numIndex = size * size;
		int count = 0;
		for (int i = 0; i < numIndex; i++)
		{
			count += (index[i] == valueToCount);
		}
		return count;
	}
	
	int grid2D::operator() (int pos)
	{
		if (pos >= (size * size) || pos < 0)
		{
			return -1;
		}
		return index[pos];
	}
		
	int grid2D::operator() (int x, int y)
	{
		if (x >= 0 && x < size && y >= 0 && y < size)
		{
			int pos = x + y * size;
			return index[pos];
		}
		return -1;
	}
}//grids

#endif //GRID_H