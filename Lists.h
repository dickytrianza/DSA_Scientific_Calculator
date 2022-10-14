#ifndef LISTSH
#define LISTSH
#include <stddef.h>

// Here, we are defining the class for both scenarios since we want to take into account two 
// separate lists, one for value and one for operator.

// Defining the Class for value
class Vals {
    public:
        float data;
        Vals* next;

        Vals(float x) {
            data = x;
            next = NULL;
        }

// Function defined inside the class
        void pushTail(Vals** headRef, Vals** tailRef, float newData);
        void deleteTail(Vals** headRef, Vals** tailRef);
        void printList(Vals* valsHead);
};

// Defining the Class for operator
class Ops {
    public:
        char data;
        Ops* next;

        Ops(char c) {
            data = c;
            next = NULL;
        }

// Function defined inside the class
        void pushTail(Ops** headRef, Ops** tailRef, char newData);
        void deleteTail(Ops** headRef, Ops** tailRef);
        void printList(Ops* valsHead);
};

// determine the end the if condition
#endif



