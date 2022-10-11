#include <iostream>
#include <cmath>
#include "Lists.h"
#include "HistoryCalc.h"
using namespace std;

// Basic Operator
float basicOperator(float x, float y, char op){
    if(op == '+') return (x + y);
    if(op == '-') return (x - y);
    if(op == '*') return (x * y);
    if(op == '/') return (x / y);
    if(op == '^') return pow(x, y);
    return 0;
}

// Trigonometry function
float trigOperator(float x, char op){
    if(op == 's') return sin(x);
    if(op == 'c') return cos(x);
    if(op == 't') return tan(x);
    if(op == 'q') return sqrt(x);
    if(op == 'l') return log10(x);
    if(op == 'e') return log(x);
    return 0;
}

int precedenceOperator(char op){
       if(op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2; 
    else if (op == 's' || op == 'c' || op == 't' || op == 'q' || op == 'l' || op == 'e')
        return 3;
    else if (op == '^')
        return 4;  
    else
        return 0;
}

// Erase line
void erase(int count){
    count++;
    if (count > 0){
         cout << "\x1b[2K"; //delete current line

        for (int i = 1; i < count; i++) {
            cout
            << "\x1b[1A" //move up one line
            << "\x1b[2K"; //delete current line
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

float inputResult(string input, Vals* valsHead, Vals* valsTail, Ops* opsHead, Ops* opsTail){
    bool lastDigit = false;

    for(int i = 0;i < input.length();i++){
        if(input[i] == ' '){
            continue;
        }

        // Push front bracket to ops list
        else if(input[i] == '('){
            opsHead->pushTail(&opsHead, &opsTail, input[i]);
            lastDigit = false;
        }

        // Push sin, cos, tan, sqrt, log, to ops list
        else if(isalpha(input[i])) {
            lastDigit = false;

            if(input[i] == 's'){
                if(i < input.length() - 2 && input[i + 1] == 'i' && input[i + 2] == 'n') {
                    opsHead->pushTail(&opsHead, &opsTail, 's');
                    i += 2;
                }
                else if(i < input.length() - 3 && input[i + 1] == 'q' && input[i + 2] == 'r' && input[i + 3] == 't') {
                    opsHead->pushTail(&opsHead, &opsTail, 'q');
                    i += 3;
                } else {
                    return NAN;
                }
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
                } else {
                    return NAN;
                }
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
                } else 
                    return NAN;
            } 
            else return NAN;
        }

        // Calculate inside the parentheses
        else if(input[i] == ')'){
            while(opsHead != NULL && opsTail->data != '('){
                char tailOp = opsTail-> data;

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

            // Push operators to ops list and calculete the previous ops if it is lower or equal
            else {
                if(opsHead != NULL && lastDigit) {
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
                    lastDigit = false;
                }
                opsHead->pushTail(&opsHead, &opsTail, input[i]);
            }      
            else return NAN; 
         }
    } 

    // Calculate the remaining operations
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

// Main Menu
int mainMenu(){
    int menu;
     cout << "=================================" << endl;
    cout << "\t    MAIN MENU\t\t" << endl;
    cout << "=================================" << endl << endl;
    cout << "1. Open the Calculator"  << endl;
    cout << "2. Check History"  << endl;
    cout << "0. Exit program"  << endl << endl;

    cout << "Choose the option: ";
    cin >> menu;
    getchar();
    system("cls");
    return menu;
}

// Calculator Menu
int main(){
    Vals* valsHead = NULL, *valsTail = NULL;
    Ops* opsHead = NULL, *opsTail = NULL;
    Queue* history = new Queue(1000);

    // Obtain the values from user
    int menu = mainMenu();
    while(menu != 0){
        if(menu == 1){
            cout << "====================================================================" << endl;
            cout << "\t\t\tSCIENTIFIC CALCULATOR\t" << endl;
            cout << "====================================================================" << endl;
            cout << "Available operators:" << endl;
            cout << "Basic operators [+, -, *, /, ^, (, )]" << endl;
            cout << "Trigonometry and advanced operators [sin, cos, tan, sqrt, log, ln]" << endl;
            cout << "Please enter your expression(s)! (type 'back' to return to main menu)" << endl << endl << endl;
        
            string input;
            cout << "Input an equation: " << endl;
            getline(cin, input);
            while(input.compare("back") != 0){
                static int error = 0;
                float result = inputResult(input, valsHead, valsTail, opsHead, opsTail);

                if(isnan(result)) {
                    if(error == 0) error++;
                    erase(3);
                    cout << "Warning::Input the equation correctly." << endl;
                }
                else {
                    if(error > 0) {
                        eraseWarning(input);
                        error = 0;
                    }
                    cout << "= " << result << endl << endl;
                    history->enqueue(history, input, result);
                }
                
                cout << "Input the equation:" << endl;
                getline(cin, input);
            }
        }

        // History Menu
        else if(menu == 2){
            cout << "=====================================" << endl;
            cout << "\tCALCULATOR HISTORY\t" << endl;
            cout << "=====================================" << endl;
            cout << "1. Show history list" << endl;
            cout << "2. Pick a history to delete" << endl;
            cout << "3. Delete whole history" << endl;
            cout << "0. Back to main menu" << endl << endl;

            int option;

            cout << "Input the number: ";
            cin >> option;
            while(option != 0){
                if(option == 1){
                    history->showHistory(history);
                }
                else if(option == 2){
                    int index;
                    cout << "Input by number to delete the history: ";
                    cin >> index;
                    history->dequeue_At(history, index);
                }

                else if(option == 3){
                    char answer;
                    cout << "Do you want to delete the whole history (Y/N)? ";
                    cin >> answer;

                    switch(tolower(answer)) {
                        case 'y': 
                        history->dequeue_All(history);
                        if(!history->isEmpty(history)){
                            cout << "All history successfully deleted" << endl;
                            break;
                        }
                        case 'n': cout << "History deletion cancelled" << endl; 
                        break;
                }
                cout << endl;
            }
            cout << "Enter the option: ";
            cin >> option;
            }
        }
        system("cls");
        menu = mainMenu(); 
    }
    exit(0);
    return 0;
}



