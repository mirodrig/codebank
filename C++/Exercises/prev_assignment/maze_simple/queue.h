#ifndef QUEUE_H
#define QUEUE_H

// create an object for the location in the maze
struct Loc{
	int row;					// y coordinate
	int col;					// x coordinate
};

// create a queue object (without using queue STL)
class Queue{
public:
	Queue(int len);				// initialize queue with length
	~Queue();					// destructor
	void pushBack(Loc loc);		// add coordinate location to queue
	Loc popFront();				// return & remove oldest location in queue
	bool isEmpty();				// determines if queue is empty

private:
	Loc* contents;				// pointer to queue
	int tail;					// index of last free item at the end
	int head;					// index of first occupied location
};

#endif