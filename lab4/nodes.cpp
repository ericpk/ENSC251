/**
* @file nodes.cpp
* @author Eric Park
* @Date   10/04/2017
* @version 1.0
*
* @brief <ENSC 251, HW1>
*
* @section DESCRIPTION
* inserts, modifies, and deletes a node using class Node
*
**/

// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Oct. 4
//
// 301319654
#include <iostream>
#include <string>

using namespace std;

class Node
{
	public:
		Node(); // default constructor, name and link will be NULL
		Node(string nameIn, Node *linkIn); // constructor with name and link
		
		//member functions
		void setName(string nameIn); //sets the name in Node
		void attachNodes(Node *linkIn); //attaches a new link at the end
		void insertNodes(Node *linkIn); //inserts a new link in between
		string getName() const; //gets name stored in node
		Node* getLink() const; //gets link stored in node
		
	private:
		//stores the name and the link to next node
		string name;
		Node *link;
};

Node::Node()
{
	name = '\0';
	link = NULL;
}

Node::Node(string nameIn, Node *linkIn)
{
	name = nameIn;
	link = linkIn;
	
}
		
void Node::setName(string nameIn)
{
	name = nameIn;
}

void Node::attachNodes(Node *linkIn)
{
	link = linkIn;
}

void Node::insertNodes(Node *linkIn)
{
	Node* temp = link;
	link = linkIn;
	linkIn->attachNodes(temp);
}

string Node::getName() const
{
	return name;
}

Node* Node::getLink() const
{
	return link;
}

//function that displays all data within it and its nodes
void displayNodes(Node* node)
{
	Node* linkNext = node;
	while (linkNext != NULL)
	{
		cout << linkNext->getName() << endl;
		linkNext = linkNext->getLink();

	}
	cout << endl; 
}

typedef Node* NodePtr;

int main()
{
	//this part does identical things as original code, moved to class
	NodePtr listPtr, tempPtr, newPtr;
	listPtr = new Node("Emily", NULL);
	newPtr = new Node("James", NULL);
	listPtr->attachNodes(newPtr);
	tempPtr = new Node("Joules", NULL);
	newPtr->attachNodes(tempPtr);
	
	//begin node operation, some steps may be hardcoded
	//display output, then add Joshua to nodes
	displayNodes(listPtr);
	tempPtr = new Node("Joshua", NULL);
	newPtr->insertNodes(tempPtr);
	//display output, then delete Joules
	displayNodes(listPtr);
	tempPtr = newPtr->getLink();
	tempPtr = tempPtr->getLink();
	delete tempPtr;
	tempPtr = newPtr->getLink();
	tempPtr->attachNodes(NULL);
	//display then delete all nodes
	displayNodes(listPtr);
	listPtr->attachNodes(NULL);
	delete newPtr;
	delete listPtr;

	return 0;
} // end main