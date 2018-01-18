/**
* @file VectorDouble.h
* @author Eric Park
* @Date   10/01/2017
* @version 1.0
*
* @brief <ENSC 251, HW1>
*
* @section DESCRIPTION
* Contains VectorDouble class that behaves like std::vector objects
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
#ifndef VECTORDOUBLE_H
#define VECTORDOUBLE_H

/*
* Class for VectorDouble, stores a dynamically
* allocated, automatically changing array of doubles
*/
class VectorDouble
{
public:
	VectorDouble();
	VectorDouble(int numArguments);
	VectorDouble(const VectorDouble &original);
	~VectorDouble();
	
	void operator= (const VectorDouble &input);
	bool operator== (const VectorDouble &input);
	
	void push_back(double input);
	void reserve(unsigned int newSize);
	void resize(unsigned int newSize);
	void resize(unsigned int newSize, double initValue);
	void change_value_at(double val, unsigned int index);
	double value_at(unsigned int index) const;
	unsigned int capacity() const;
	unsigned int size() const;

private:
	double *doubles;
	unsigned int max_count;
	unsigned int count;
	
	void increase_capacity();
	void increase_capacity(int newSize);
};

/*
* Initializes with 50 indexes by default, all elements to zero
*/
VectorDouble::VectorDouble()
{
	doubles = new double[50];
	count = 0;
	max_count = 50;
	
	for (int i = 0; i < 50; i++)
	{
		doubles[i] = 0;
	}
	
}

/*
* Initializes with numArguments elements, if provided
* all elements to zero
*/
VectorDouble::VectorDouble(int numArguments)
{
	doubles = new double[numArguments];
	count = 0;
	if (numArguments <= 0)
	{
		numArguments = 50;
	}
	max_count = numArguments;
	
	for (int i = 0; i < numArguments; i++)
	{
		doubles[i] = 0;
	}
}

// copy constructor
VectorDouble::VectorDouble(const VectorDouble &original)
{
	unsigned int newLength = original.capacity();
	doubles = new double[newLength];
	for (unsigned int i = 0; i < newLength; i++)
	{
		doubles[i] = original.value_at(i);
	}
	max_count = newLength;
	count = original.size();
}

// destructor
VectorDouble::~VectorDouble()
{
	delete []doubles;
}

// assignment operator for VectorDouble
// if input vector is larger, make new array with same size
void VectorDouble::operator= (const VectorDouble &input)
{
	unsigned int inLength = input.capacity();
	if (inLength > max_count)
	{
		max_count = inLength;
		delete []doubles;
		doubles = new double[max_count];
	}
	
	for (unsigned int i = 0; i < inLength; i++)
	{

		doubles[i] = input.value_at(i);

	}

	count = input.size();
}

// equality operator for VectorDouble
// true iff input1/input2 has same count/elements in array
bool VectorDouble::operator== (const VectorDouble &input)
{
	if (input.size() != count)
	{
		return false;
	}
	for (unsigned int i = 0; i < count; i++)
	{
		if (input.value_at(i) != doubles[i])
		{
			return false;
		}
	}
	return true;
}

// same behaviour as vector::push_back
// adds an element at the end, resize array if needed
// resized array will have twice the capacity
void VectorDouble::push_back(double input)
{
	if (count == max_count)
	{
		increase_capacity();
	}
	doubles[count] = input;
	count++;
}

// same behaviour as vector::reserve
// if current capacity is less than newSize
// reallocate array to newSize elements
void VectorDouble::reserve(unsigned int newSize)
{
	if (max_count < newSize)
	{
		increase_capacity(newSize);
	}
	return;
}

// same behaviour as vector::resize
// if newSize is less than count, shrink count
// if newSize is greater than count but less than capacity
// do not expand the array
void VectorDouble::resize(unsigned int newSize)
{
	if (count > newSize)
	{
		count = newSize;
		return;
	}
	if (count < newSize && newSize <= max_count)
	{
		for (unsigned int i = count; i < newSize; i++)
		{
			doubles[i] = 0;
		}
		count = newSize;
		return;
	}
	if (newSize > max_count)
	{
		increase_capacity(newSize);
		count = newSize;
		return;
	}
	return;
}

// same behaviour as vector::resize
// do the same but initialize values to initValue rather than 0
void VectorDouble::resize(unsigned int newSize, double initValue)
{
	int oldSize = count;
	
	if (count > newSize)
	{
		count = newSize;
		return;
	}
	if (count < newSize && newSize <= max_count)
	{
		for (unsigned int i = count; i < newSize; i++)
		{
			doubles[i] = initValue;
		}
		count = newSize;
		return;
	}
	if (newSize > max_count)
	{
		increase_capacity(newSize);
		for (unsigned int j = oldSize; j < newSize; j++)
		{
			doubles[j] = initValue;
		}
		count = newSize;
		return;
	}
	return;
}

// writes value at the given index
// doing so with std::vector with square brackets would throw out_of_range
// exception, but do nothing for VectorDouble
void VectorDouble::change_value_at(double val, unsigned int index)
{
	if (index >= count)
	{
		return; // element out of index
	}
	else
	{
		doubles[index] = val;
		return;
	}
}

// reads value at the given index
// doing so with std::vector with square brackets would throw out_of_range
// exception, but do nothing for VectorDouble
double VectorDouble::value_at(unsigned int index) const
{
	if (index >= count)
	{
		return NULL; //element out of index
	}
	else
	{
		return doubles[index];
	}
	
}

// same behaviour as vector::capacity
// returns the total allocated space for the vector
unsigned int VectorDouble::capacity() const
{
	return max_count;
}

// same behaviour as vector::size
// returns the total used space for the vector
unsigned int VectorDouble::size() const
{
	return count;
}

// resize array to twice of the size as before
void VectorDouble::increase_capacity()
{
	max_count *= 2;
	double *temp;
	temp = new double[max_count];
	for (unsigned int i = 0; i < count; i++)
	{
		temp[i] = doubles[i];
	}
	for (unsigned int i = count; i < max_count; i++)
	{
		temp[i] = 0;
	}
	delete []doubles;
	doubles = new double[max_count];
	
	for (unsigned int i = 0; i < max_count; i++)
	{
		doubles[i] = temp[i];
	}
	delete []temp;
}

// resize array to specified size newSize
void VectorDouble::increase_capacity(int newSize)
{
	max_count = newSize;
	double *temp;
	temp = new double[max_count];
	for (unsigned int i = 0; i < count; i++)
	{
		temp[i] = doubles[i];
	}
	for (unsigned int i = count; i < max_count; i++)
	{
		temp[i] = 0;
	}
	delete []doubles;
	doubles = new double[max_count];
	
	for (unsigned int i = 0; i < max_count; i++)
	{
		doubles[i] = temp[i];
	}
	delete []temp;
}

#endif //VECTORDOUBLE_H