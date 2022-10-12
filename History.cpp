#include "History.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// Queue is full when the size equal to capacity
bool Queue::isFull(Queue* queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
bool Queue::isEmpty(Queue* queue)
{
	return (queue->size == 0);
}

// Function to add an expression to the queue.
void Queue::enqueue(Queue* queue, string expression, float result)
{

	if(queue->size == 0) { // If queue is empty, reset the front and rear to -1 again
		queue->front = -1;
		queue->rear = -1;
	}

	ostringstream ss;
	ss << result;
	string formattedResult(ss.str());
	expression = expression + " = " + formattedResult; // Concatenate the string expression with the int result into one string

	if(isFull(queue))
		return;

	else if(queue->front == -1) { // If front is -1 add +1 so that front is pointing to the beginning of the array
		queue->front += 1;
	}

	queue->rear = (queue->rear + 1) % queue->capacity; // limit the shifting of rear from one element to another in the array
	queue->array[queue->rear] = expression; // Store the string expression into the array
	queue->size = queue->size + 1; // Increase the size as the expression is added
}

// Remove an expression done in history at a given position
void Queue::dequeue_At(Queue* queue, int pos)
{
	if (isEmpty(queue)) {
		cout << "Error!! History not detected" << endl << endl;
		return;
	}

	if(pos > queue->size) {
		cout << "History does not exist" << endl << endl;
		return;
	}

	for(int i = pos-1; i < (queue->size-1); i++) //This loop serves to shift all the deleted element to the left
	{ 
    	queue->array[i] = queue->array[i+1];
	}
	queue->rear = (queue->rear - 1) % queue->capacity; // Decrease rear by one as the element deted
	queue->size = queue->size - 1; 

    if(queue->front == queue->rear) { // If front and rear is pointng at the same array element, assign -1 to both
		queue->front = -1;
		queue->rear = -1;
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

	// Loop through the array and basically have the rear "pointer" go back all the way to the front "pointer"
	int initialSize = queue->size;
	for(int i = 0; i < initialSize; i++) {
		queue->rear = (queue->rear - 1) % queue->capacity; // Modulo here is used to limit the shifting of front from one element to another in the array
		queue->size = queue->size - 1;

		if(queue->front == queue->rear) { // If front and rear is pointng at the same array element, assign -1 to both and decrease size by -1 so that the size will be zero
			queue->size = queue->size - 1;
			queue->front = -1;
			queue->rear = -1;
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
