#include <iostream>
#include <cmath>
#include "Lists.h"
#include "History.h"
using namespace std;

//Calculate the Basic Operations
float basicOperator(float x, float y, char op) {
    if(op == '+') return (x + y);
    if(op == '-') return (x - y);
    if(op == '*') return (x * y);
    if(op == '/') return (x / y);
    if(op == '^') return pow(x, y);
    return 0;
}

float trigOperator(float x, char op) {
    if(op == 's') return sin(x);
    if(op == 'c') return cos(x);
    if(op == 't') return tan(x);
    if(op == 'q') return sqrt(x);
    if(op == 'l') return log10(x);
    if(op == 'e') return log(x);
    return 0;
}

int precedenceOperator(char op) {
    if(op == '+' || op == '-'){
        return 1;
    }else if (op == '*' || op == '/'){
        return 2; 
    }else if (op == 's' || op == 'c' || op == 't' || op == 'q' || op == 'l' || op == 'e'){
        return 3;
    }else if (op == '^'){
        return 4;  
    }else{
        return 0;
    }
}

// Erase the count lines
void eraseLines(int count) {
    count++;

    if (count > 0) {
        cout << "\x1b[2K"; 

        for (int i = 1; i < count; i++) {
            cout
            << "\x1b[1A" 
            << "\x1b[2K"; 
        }

        cout << "\r"; 
    }
}

void eraseWarning(string input) {
    cout << "\x1b[1A" << "\x1b[2K";
    cout << "\x1b[1A" << "\x1b[2K";
    cout << "\x1b[1A" << "\x1b[2K";

    cout << "\nEnter an expression:" << endl;
    cout << input << endl;
    
    cout << "\r";
}

float inputResult(string input, Vals* valsHead, Vals* valsTail, Ops* opsHead, Ops* opsTail) {
    bool lastIsDigit = false;

    for(int i = 0; i < input.length(); i++) {
        
        if(input[i] == ' ') {
            continue;
        }
        
        else if(input[i] == '(') {
            opsHead->pushTail(&opsHead, &opsTail, input[i]);
            lastIsDigit = false;
        }

     
        else if(isalpha(input[i])) {
            lastIsDigit = false;

            if(input[i] == 's') {
              
                if(i < input.length() - 2 && input[i + 1] == 'i' && input[i + 2] == 'n') {
                    opsHead->pushTail(&opsHead, &opsTail, 's');
                    i += 2;
                }
                else if(i < input.length() - 3 && input[i + 1] == 'q' && input[i + 2] == 'r' && input[i + 3] == 't') {
                    opsHead->pushTail(&opsHead, &opsTail, 'q');
                    i += 3;
                }
               
                else return NAN;
            }

            else if(i < input.length() - 2 && input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's') {
                opsHead->pushTail(&opsHead, &opsTail, 'c');
                i += 2;
            }

            else if(i < input.length() - 2 && input[i] == 't' && input[i + 1] == 'a' && input[i + 2] == 'n') {
                opsHead->pushTail(&opsHead, &opsTail, 't');
                i += 2;
            }

            else if(input[i] == 'l') {
                if(i < input.length() - 2 && input[i + 1] == 'o' && input[i + 2] == 'g') {
                    opsHead->pushTail(&opsHead, &opsTail, 'l');
                    i += 2;
                }

                else if(i < input.length() - 1 && input[i + 1] == 'n') {
                    opsHead->pushTail(&opsHead, &opsTail, 'e');
                    i++;
                }
                else return NAN;
            }

            else return NAN;
        }

        // Push Number Value to list
        else if(isdigit(input[i])) {
            float temp = 0;

            while(i < input.length() && isdigit(input[i])) {
                temp = (temp * 10) + (input[i] - '0');
                i++;
            }
            i--;

             // Check Unary Operators
            if(!lastIsDigit && (opsHead != NULL || valsHead != NULL)) {
                if(opsTail->data == '+') {
                    opsHead->deleteTail(&opsHead, &opsTail);
                    valsHead->pushTail(&valsHead, &valsTail, temp);
                }
                else if(opsTail->data == '-') {
                    opsHead->deleteTail(&opsHead, &opsTail);
                    valsHead->pushTail(&valsHead, &valsTail, (-1) * temp);
                }
                else valsHead->pushTail(&valsHead, &valsTail, temp);
            }

            else valsHead->pushTail(&valsHead, &valsTail, temp);
            
            lastIsDigit = true;
        }

       //Calculate the paranthesis
        else if(input[i] == ')') {
            while(opsHead != NULL && opsTail->data != '(') {
                char tailOp = opsTail->data;

                if(valsHead == NULL || ((tailOp == '+' || tailOp == '-' || tailOp == '*' || tailOp == '/' || tailOp == '^') && valsHead->next == NULL)) {
                    return NAN;
                }

                else if(tailOp == 's' || tailOp == 'c' || tailOp == 't' || tailOp == 'q' || tailOp == 'l' || tailOp == 'e') {
                    float x = valsTail->data;
                    valsHead->deleteTail(&valsHead, &valsTail);

                    char op = opsTail->data;
                    opsHead->deleteTail(&opsHead, &opsTail);

                    float result = trigOperator(x, op);
                    valsHead->pushTail(&valsHead, &valsTail, result);
                }

                else {
                    float b = valsTail->data;
                    valsHead->deleteTail(&valsHead, &valsTail);

                    float a = valsTail->data;
                    valsHead->deleteTail(&valsHead, &valsTail);

                    char op = opsTail->data;
                    opsHead->deleteTail(&opsHead, &opsTail);

                    float result = basicOperator(a, b, op);
                    valsHead->pushTail(&valsHead, &valsTail, result);
                }
            }

            if(opsHead != NULL) opsHead->deleteTail(&opsHead, &opsTail);
        }
        
        else {
            if(opsHead != NULL && lastIsDigit) {
                while(opsHead != NULL && precedenceOperator(input[i]) <= precedenceOperator(opsTail->data)) {
                    char tailOp = opsTail->data;

                    if(valsHead == NULL || ((tailOp == '+' || tailOp == '-' || tailOp == '*' || tailOp == '/' || tailOp == '^') && valsHead->next == NULL)) {
                        return NAN;
                    }

                    else if(tailOp == 's' || tailOp == 'c' || tailOp == 't' || tailOp == 'q' || tailOp == 'l' || tailOp == 'e') {
                        float x = valsTail->data;
                        valsHead->deleteTail(&valsHead, &valsTail);

                        char op = opsTail->data;
                        opsHead->deleteTail(&opsHead, &opsTail);

                        float result = trigOperator(x, op);
                        valsHead->pushTail(&valsHead, &valsTail, result);
                    }

                    else {
                        float b = valsTail->data;
                        valsHead->deleteTail(&valsHead, &valsTail);

                        float a = valsTail->data;
                        valsHead->deleteTail(&valsHead, &valsTail);

                        char op = opsTail->data;
                        opsHead->deleteTail(&opsHead, &opsTail);

                        float result = basicOperator(a, b, op);
                        valsHead->pushTail(&valsHead, &valsTail, result);
                    }
                }
            }
            
            if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^' ||
               input[i] == 's' || input[i] == 'c' || input[i] == 't' || input[i] == 'q' || input[i] == 'l' || input[i] == 'e') {
                if(input[i] != '+' && input[i] != '-') {
                    lastIsDigit = false;
                }

                opsHead->pushTail(&opsHead, &opsTail, input[i]);
            }
               
            else return NAN; 
        }
    }

    while(opsHead != NULL) {
        char tailOp = opsTail->data;

        if(valsHead == NULL || ((tailOp == '+' || tailOp == '-' || tailOp == '*' || tailOp == '/' || tailOp == '^') && valsHead->next == NULL)) {
            return NAN;
        }

        else if(tailOp == 's' || tailOp == 'c' || tailOp == 't' || tailOp == 'q' || tailOp == 'l' || tailOp == 'e') {
            float x = valsTail->data;
            valsHead->deleteTail(&valsHead, &valsTail);

            char op = opsTail->data;
            opsHead->deleteTail(&opsHead, &opsTail);

            float result = trigOperator(x, op);
            valsHead->pushTail(&valsHead, &valsTail, result);
        }

        else {
            float b = valsTail->data;
            valsHead->deleteTail(&valsHead, &valsTail);

            float a = valsTail->data;
            valsHead->deleteTail(&valsHead, &valsTail);

            char op = opsTail->data;
            opsHead->deleteTail(&opsHead, &opsTail);

            float result = basicOperator(a, b, op);
            valsHead->pushTail(&valsHead, &valsTail, result);
        }
    }

    return valsTail->data; //return final result
}

//FUNCTION FOR MAIN MENU
// Main Menu
int mainMenu() {
    int menu;
    cout << "=> Welcome to Scientific Calculator <=" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "|\tCALCULATOR MAIN MENU\t|" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "| => 1. Scientific Calculator\t|" << endl;
    cout << "| => 2. Open History\t\t|" << endl;
    cout << "| => 0. Exit Program\t\t|" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "Choose the option: ";
    cin >> menu;
    getchar();
    system("cls");
    return menu;
}

// Main Function
int main() {
    Vals* valsHead = NULL, *valsTail = NULL;
    Ops* opsHead = NULL, *opsTail = NULL;
    Queue* history = new Queue(1000);
    
    // Calculator Menu
    int menu = mainMenu();
    while(menu != 0) {
        if(menu == 1) {
            cout << "========================> INSTRUCTIONS <========================" << endl;
            cout << "+---------------------------------------------------------------+" << endl;
            cout << "|\t\t\tCALCULATOR\t\t\t\t|" << endl;
            cout << "+---------------------------------------------------------------+" << endl;
            cout << "| => Basic Operators: +, -, *, /, ^, (, )\t\t\t|" << endl;
            cout << "| => Basic Trigonometry Function: sin, cos, tan, sqrt, log, ln\t|" << endl;
            cout << "| => Input the equation properly!\t\t\t\t|" << endl;
            cout << "| => Type 'back' to return into main menu.\t\t\t|" << endl;
            cout << "+---------------------------------------------------------------+" << endl;

            string input;
            cout << "Input the equation: ";
            getline(cin, input);
            while(input.compare("back") != 0) {
                static int error = 0;
                float result = inputResult(input, valsHead, valsTail, opsHead, opsTail);

                if(isnan(result)) {
                    if(error == 0) error++;
                    eraseLines(3);
                    cout << "Warning::Invalid equation!" << endl;
                } else {
                    if(error > 0) {
                        eraseWarning(input);
                        error = 0;
                    }
                    cout << "= " << result << endl << endl;
                    history->enqueue(history, input, result);
                }
                cout << "Input the equation: ";
                getline(cin, input);
            }
        }

//HISTORY MENU
        else if(menu == 2) {
            cout << "+---------------------------------------+" << endl;
            cout << "|\tCALCULATOR HISTORY\t\t|" << endl;
            cout << "+---------------------------------------+" << endl;
            cout << "| => 1. Show history list\t\t|" << endl;
            cout << "| => 2. Choose a history to delete\t|" << endl;
            cout << "| => 3. Clear all the history\t\t|" << endl;
            cout << "| => 0. Go back to main menu\t\t|" << endl;
            cout << "+---------------------------------------+" << endl;
            int option;
            cout << "Input your option: ";
            cin >> option;
            while(option != 0) {
                if(option == 1) {
                    history->showHistory(history);
                } else if(option == 2) {
                    int index;
                    cout << "Delete history according to the number: ";
                    cin >> index;
                    history->dequeue_At(history, index);
                } else if(option == 3) {
                    char answer;
                    cout << "Clear all the history! (y/n) ";
                    cin >> answer;
                    switch(tolower(answer)) {
                        case 'y': history->dequeue_All(history);
                                  if(!history->isEmpty(history))
                                      cout << "History Deleted" << endl;
                                  break;
                        case 'n': cout << "Canceled Delete History." << endl; break;
                    }
                    cout << endl;
                }
                cout << "Input your option: ";
                cin >> option;
            }
        }
        system("cls"); 
        menu = mainMenu();
    }
    exit(0);
    return 0;
}

