/**
* @file DMVCounter.cpp
* @author Eric Park
* @Date   10/22/2017
* @version 1.0
*
* @brief <ENSC 251, HW2>
*
* @section DESCRIPTION
* Implements queue class to keep track of customer servicing
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
#include <iostream>
#include <ctime>
#include <cstddef>
#include <cstdlib>
#include "newQueue.h"

using namespace std;
using namespace newQueue;

namespace newQueue
{
	Queue::Queue() : front(NULL), back(NULL)
	{
		//Intentionally empty.
	}

	Queue::Queue(const Queue& aQueue)
	{
		if (aQueue.empty())
		{
			front = back = NULL;
		}
		else
		{
			QueueNodePtr oldTempPtr = aQueue.front;
			//oldTempPtr moves through the nodes
			//from front to back of aQueue.
			QueueNodePtr newTempPtr;
			//newTempPtr is used to create new nodes.

			front = new QueueNode;
			front->ticketNum = oldTempPtr->ticketNum;
			front->time = oldTempPtr->time;
			front->link = NULL;
			back = front;
			//First node created and filled with previous data.
			//New nodes are now added AFTER this node.

			oldTempPtr = oldTempPtr->link;
			//temp_ptr_old now points to second
			//node or NULL if there is no second node.

			while (oldTempPtr != NULL)
			{
				newTempPtr = new QueueNode;
				newTempPtr->ticketNum = oldTempPtr->ticketNum;
				newTempPtr->time = oldTempPtr->time;
				newTempPtr->link = NULL;
				back->link = newTempPtr;
				back = newTempPtr;
				oldTempPtr = oldTempPtr->link;
			}

		}
	}
		Queue::~Queue()
		{
			long *next;
			while (!empty())
			{
				next = remove();
				//remove calls delete
				delete[] next;
			}
		}

		void Queue::add(int queueNumber, long enterTime)
		{
			if (empty())
			{
				front = new QueueNode;
				front->ticketNum = queueNumber;
				front->time = enterTime;
				front->link = NULL;
				back = front;
			}
			else
			{
				QueueNodePtr tempPtr;
				tempPtr = new QueueNode;
				tempPtr->ticketNum = queueNumber;
				tempPtr->time = enterTime;
				tempPtr->link = NULL;
				back->link = tempPtr;
				back = tempPtr;
			}
		}

		long* Queue::remove()
		{
			if (empty())
			{
				cout << "Error: Removing an item from an empty queue.\n";
				exit(1);
			}

			long *result;
			result = new long[2];
			result[0] = front->ticketNum;
			result[1] = front->time;

			QueueNodePtr discard;
			discard = front;
			front = front->link;
			if (front == NULL)
			{
				back = NULL;
			}
			delete discard;

			return result;
		}

		bool Queue::empty() const
		{
			return (back == NULL); //front == NULL would also work 
		}

	}//newQueue

	long getTime();
	//Postcondition: returns number of seconds since Jan. 1, 1970

	/*
	* Main test function that implements Queue class
	*/
	int main()
	{
		//declare variables
		long timeEntered = 0;
		long *helpedCustomer;
		long prevTimes[3] = { 0, 0, 0 };
		long waitTime = 0;
		long estWaitTime = 0;
		int ticketNumber = 0;
		int choice = -1;
		Queue customerQueue;

		cout << "/------------------------------------------------\\\n"
			<< "| Department of Motor Vehicles customer counter   |\n"
			<< "\\------------------------------------------------/\n";

		while (true)
		{
			if (customerQueue.empty())
			{
				cout << "The line is empty." << endl;
			}
			cout << "Enter '1' to simulate a customer's arrival, \
'2' to help the next customer, or '3' to quit." << endl;
			if (!(cin >> choice))
			{
				//catch invalid inputs
				cout << "Invalid choice, try again" << endl;
				cin.clear();
				cin.sync();
				continue;
			}
			else if (choice > 3 || choice < 1)
			{
				//catch invalid inputs
				cout << "Invalid choice, try again" << endl;
				cin.clear();
				cin.sync();
				continue;
			}
			else if (choice == 1)
			{
				//add the customer to the queue
				ticketNumber++;
				timeEntered = getTime();
				customerQueue.add(ticketNumber, timeEntered);
				cout << "Customer " << ticketNumber << " entered the queue \
at time " << timeEntered << "." << endl;
				continue;
			}
			else if (choice == 2)
			{
				if (customerQueue.empty())
				{
					cout << "There are no customers to help." << endl;
					continue;
				}
				helpedCustomer = customerQueue.remove();
				waitTime = getTime() - helpedCustomer[1];

				cout << "Customer " << helpedCustomer[0] << " is being helped \
at time " << getTime() << "." << "Wait time = "
					<< waitTime << " seconds." << endl;

				//push forward the previous recorded times,
				//disregard oldest time
				prevTimes[2] = prevTimes[1];
				prevTimes[1] = prevTimes[0];
				prevTimes[0] = waitTime;

				estWaitTime = prevTimes[0] + prevTimes[1] + prevTimes[2];

				//divide by total number of prevTimes, which may be less than 3
				estWaitTime = estWaitTime /
					(helpedCustomer[0] > 3 ? 3 : helpedCustomer[0]);

				if (ticketNumber >= helpedCustomer[0] + 1)
				{
					cout << "The estimated wait time for customer "
						<< helpedCustomer[0] + 1 << " is " << estWaitTime
						<< " seconds." << endl;
				}

				delete[] helpedCustomer;
				continue;
			}
			else if (choice == 3)
			{
				cout << "Program is terminating" << endl;
				return 0;
			}

		}

		return 0;
	}

	long getTime()
	{
		return (static_cast<long>(time(NULL)));
	}