#include "History.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// Queue is full when the size equal to capacity
bool Queue::isFull(Queue* queue) {
	return (queue->size == queue->capacity);
}

// Empty when size is 0
bool Queue::isEmpty(Queue* queue) {
	return (queue->size == 0);
}

// Function to add an expression to the queue.
void Queue::enqueue(Queue* queue, string expression, float result) {

	if(queue->size == 0) { 
		queue->front = -1; // When queue is empty, reset the front to -1 again
		queue->back = -1; // Reset the back to -1 again
	}

	ostringstream ss;
	ss << result;
	string formattedResult(ss.str());
	expression = expression + " = " + formattedResult; // Combine the string expression with the int result into one string

	if(isFull(queue))
		return;

	else if(queue->front == -1) { 
		queue->front += 1; // Add +1 to make 'front' points the start of the array
	}

	queue->back = (queue->back + 1) % queue->capacity; // limit the shifting of back from one element to another in the array
	queue->array[queue->back] = expression; // Store the string expression into the array
	queue->size = queue->size + 1; // Increase the size as the expression is added
}

// Remove an expression done in history at a given position
void Queue::dequeue_At(Queue* queue, int pos) {
	if (isEmpty(queue)) {
		cout << "Error!! History not detected" << endl << endl;
		return;
	}

	if(pos > queue->size) {
		cout << "No History" << endl << endl;
		return;
	}

	//This loop serves to shift all the deleted element to the left
	for(int i = pos-1; i < (queue->size-1); i++) { 
    	queue->array[i] = queue->array[i+1];
	}
	queue->back = (queue->back - 1) % queue->capacity; // Decrease back by one as the element deleted
	queue->size = queue->size - 1; 

    if(queue->front == queue->back) {
		queue->front = -1; 	// Put -1 when front and back
		queue->back = -1; 	//is pointng at the same array element
		return;
	}

	else cout<<"History successfully cleared\n" << endl;
}

// Remove all expressions from queue
void Queue::dequeue_All(Queue* queue) {
	if (isEmpty(queue)) {
		cout << "Error! There is no History" << endl;
		return;
	}

	// Loop through the array and basically have the back "pointer" go back all the way to the front "pointer"
	int initialSize = queue->size;
	for(int i = 0; i < initialSize; i++) {
		queue->back = (queue->back - 1) % queue->capacity; //Use modulo to limit the shifting
		queue->size = queue->size - 1;

		if(queue->front == queue->back) { 	// If front and back is pointng at the same array element,
			queue->size = queue->size - 1;	//assign -1 to both and decrease size by -1
			queue->front = -1; 				//the size will be zero 
			queue->back = -1; 
			return;
		}
	}
}

void Queue::showHistory(Queue* queue) {

	cout << "|************* History of Calculator *************|\n" << endl;

	// Check if the array is empty
	if(isEmpty(queue)) {
		cout << "\t\t\tEmpty History\t\n" << endl;
	}else {
		for(int i = 0; i < queue->size; i++) {
			cout << i + 1 << ". " << queue->array[i] << "\n" << endl;
		}
	}
	cout << "|**************** END **************** |\n" << endl;
	return;
}