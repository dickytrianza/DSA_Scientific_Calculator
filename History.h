#ifndef HISTORYH
#define HISTORYH
#include <string>
using namespace std;

// build a structure of a queue
class Queue {
	public:
		int front = -1;
		int back = -1;
		int size; // Size elements of array
		unsigned capacity; // Size of array
		string* array; // Pointer of array
	
	// constructor of a queue
		Queue(unsigned capacity) {
			this->capacity = capacity; //declare there is a capacity of queue
			this->front = size = 0;//then initializes the queue size is 0

			// the enqueue
			this->back = capacity - 1; 
			this->array = new string[capacity]; // make n-capacity size of array
	}

	bool isFull(Queue* queue);
	bool isEmpty(Queue* queue);
	void enqueue(Queue* queue, string expression, float result);
	void dequeue_At(Queue* queue, int pos);
	void dequeue_All(Queue* queue);
	void showHistory(Queue* queue);
};

#endif