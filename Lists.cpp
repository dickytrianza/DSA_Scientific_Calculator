#include "Lists.h"
#include <iostream>
using namespace std;

// Open a new node in terminal to show the list based on the user input
// For two types of function that are listed in List.h, Vals and Ops
void Vals::pushTail(Vals** head_ref, Vals** tail_ref, float new_data) { // Double pointer which points to head (or start) pointer of linked list
    Vals* newNode = new Vals(new_data); // Allocate the node
    if(*head_ref == NULL) *head_ref = newNode; // Move the head to point to the new node
    else(*tail_ref)->next = newNode; // Link the old list off the new node
    (*tail_ref) = newNode;
}

void Ops::pushTail(Ops** head_ref, Ops** tail_ref, char new_data) {
    Ops* newNode = new Ops(new_data);
    if(*head_ref == NULL) *head_ref = newNode;
    else(*tail_ref)->next = newNode;
    (*tail_ref) = newNode;
}

// Back
void Vals::deleteTail(Vals** head_ref, Vals** tail_ref) {
    if(*head_ref == NULL)
        return;
    if((*head_ref)->next == NULL) {
        (*head_ref) = (*head_ref)->next;
        return;
    }
    Vals* temp = (*head_ref);
    while(temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    (*tail_ref) = temp;
}

void Ops::deleteTail(Ops** head_ref, Ops** tail_ref) {
    if(*head_ref == NULL)
        return;
    if((*head_ref)->next == NULL) {
        (*head_ref) = (*head_ref)->next;
        return;
    }
    Ops* temp = (*head_ref);
    while(temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    (*tail_ref) = temp;
}

// Print linked list
void Vals::printList(Vals* valsHead) {
    while(valsHead != NULL) {
        cout << valsHead->data << " ";
        valsHead = valsHead->next;
    }
}

void Ops::printList(Ops* opsHead) {
    while(opsHead != NULL) {
        cout << opsHead->data << " ";
        opsHead = opsHead->next;
    }
}