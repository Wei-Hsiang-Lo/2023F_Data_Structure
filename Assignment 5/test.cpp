#include <iostream>

using namespace std;

const int MAX_SIZE = 100; // Maximum size of the stack

class nStack{
public:
    nStack();
    void push(double value);
    void pop();
    double peek();
private:
    double arr[MAX_SIZE];
    int top;
};

class oStack{
public:
    oStack();
    void push(char op);
    void pop();
    char peek();
private:
    char arr[MAX_SIZE];
    int top;
};


int main() {
    nStack myStack;
    oStack ops;

    myStack.push(10.0);
    myStack.push(20.0);
    myStack.push(30.0);
    myStack.pop();
    myStack.pop();
    ops.push('+');

    // Displaying the content of the stack
    cout << myStack.peek() << endl;
    cout << ops.peek() << endl;

    return 0;
}

nStack::nStack(){
    top = -1;
}

void nStack::push(double value){
    if (top == MAX_SIZE - 1) {
        cout << "Stack overflow! Cannot push element " << value << endl;
        return;
    }
    arr[++top] = value;
}

void nStack::pop(){
    if (top == -1) {
        cout << "Stack underflow! Cannot pop from an empty stack." << endl;
        return;
    }
    --top;
}

double nStack::peek(){
    if (top == -1) {
        cout << "Stack is empty. Cannot peek." << endl;
        return -1.0; // Assuming -1.0 is not a valid value in the stack
    }
    return arr[top];
}

oStack::oStack(){
    top = -1;
}

void oStack::push(char op){
    if (top == MAX_SIZE - 1) {
        cout << "Stack overflow! Cannot push element " << op << endl;
        return;
    }
    arr[++top] = op;
}

void oStack::pop(){
    if (top == -1) {
        cout << "Stack underflow! Cannot pop from an empty stack." << endl;
        return;
    }
    --top;
}

char oStack::peek(){
    if (top == -1) {
        cout << "Stack is empty. Cannot peek." << endl;
        return -1.0; // Assuming -1.0 is not a valid value in the stack
    }
    return arr[top];
}