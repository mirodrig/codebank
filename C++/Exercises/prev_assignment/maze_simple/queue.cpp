#include "queue.h"

// constructor for the queue object
// parameter: length of the queue
Queue::Queue(int len){
	contents = new Loc[len];			// create pointer to loc array
	head = 0;							// initialize head & tail
	tail = 0;
}

Queue::~Queue(){
	delete[] contents;					// delete pointer to array
}

void Queue::pushBack(Loc loc){
	contents[tail] = loc;				// set last item of queue to value
	tail++;								// increment tail of queue
}

Loc Queue::popFront(){
	Loc oldLoc = contents[head];		// set value to head of queue
	head++;								// increment head (doesn't act. delete)
	return oldLoc;
}

bool Queue::isEmpty(){
	return head == tail;				// if head & tail are in same pos, empty
}