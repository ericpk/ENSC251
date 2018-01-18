#ifndef NEWQUEUE_H
#define NEWQUEUE_H
namespace newQueue
{
	struct QueueNode
	{
		int ticketNum;
		long time;
		QueueNode *link;
	};
	typedef QueueNode* QueueNodePtr;
	
	class Queue
	{
	public:
		Queue();
		//Initializes the object to an empty queue.
		Queue(const Queue& aQueue);
		//copy constructor
		~Queue();
		//destructor
		void add(int queueNumber, long enterTime);
		//Postcondition: ticketNum and enterTime has been 
		//added to the back of the queue.
		long* remove();
		//Precondition: The queue is not empty.
		//Returns an array of items at the front of the queue and
		//removes that item from the queue.
		bool empty() const;
		//Returns true if the queue is empty. Returns false otherwise
	private:
		
		QueueNodePtr front; //Points to the head of a linked list.
							//Items are removed at the head
		QueueNodePtr back;  //Points to the node at the other end of the 
							//linked list. Items are added at this end.
	};
}//newQueue

#endif //NEWQUEUE_H