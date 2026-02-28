#include <iostream>
#include <cstring>
#include <cmath>
#define is_char(c) (c >= 'a' && c <= 'z')//used to check if the element is variable

const int MAX_SIZE = 1000; // Maximum size of the stack

//this struct is used to store the name and the value of the variable
struct var{
    char var_name;
    double value;

    var& operator=(double newValue) {
        value = newValue;
        return *this;
    }
};

//this stack is used to store the numbers, and it provided push, pop, and peek function.
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

//this stack is used to store the operators, and it provided the same function with the above one.
class oStack{
public:
    oStack();
    void push(char op);
    void pop();
    char peek();
    bool empty();
private:
    char arr[MAX_SIZE];
    int top;
};

using namespace std;

//this function assign value respective to the order of the variables
int op_priority(char c);

//implemented the calculation
double calculate(double a, double b, char c);

double shuntingYard(string s, var* variables);
int main(){
    string s;
    int ind = 0;
    var variables[100] = {};
    //intialize the elements in the element array
    for(int i = 0; i < 100; i++){
        variables[i].var_name = ' ';
        variables[i].value = 0;
    }
    
    //keep the users cin continuously until nothing is input.
    while(getline(cin, s) && s != ""){
        int init = -1;
        //verify the input format, if it is assignment statement do it.
        if(is_char(s[0])){
            variables[ind].var_name = s[0];//assign the name of the variable to the array that contains the informations of the variable
            //record the index of '=' and call the shunting yard algorithm with the substring without variable name and '=
            for(int i = 0; i < s.length(); i++){
                if(s[i] == '=')
                    init = i + 1;
            }
            if(init != -1){
                variables[ind].value = shuntingYard(s.substr(init, s.length() - 1), variables);
                cout << variables[ind].var_name << " = " << variables[ind].value << endl;
                ind++;
            }
        }
        else//do this if the input is arithmetic expression.
            cout << shuntingYard(s, variables) << endl;
    }
    
    return 0;
}

int op_priority(const char c){
    if(c == '+' || c == '-')
        return 1;
    if(c == '*' || c == '/')
        return 2;
    if(c == '^')
        return 3;
    return 0;
}

double calculate(double a, double b, char c){
    switch(c){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

double shuntingYard(string s, var* variables){
    nStack numbers;
    oStack ops;

    for(int i = 0; i < s.length(); i++){
        if (s[i] == ' ')
            continue;//if we faced with blank, ignoring it and check the next element
        else if(is_char(s[i])){
            for(int ind = 0; ind < 100; ind++){
                if(s[i] == variables[ind].var_name)
                    numbers.push(variables[ind].value);
            }
        }
        else if(isdigit(s[i])){
            double val = 0.0;

            while(i < s.length() && (isdigit(s[i]) || s[i] == '.')){
                //dealing with the numbers part
                if(s[i] == '.'){
                    double fractional = 0.1;
                    i++;
                    while(isdigit(s[i])){
                        val += (s[i] - '0') * fractional;//convert the data type to double
                        fractional /= 10;
                        i++;
                    }
                }
                else{
                    val = val * 10 + (s[i] - '0');
                    i++;
                }
            }
            numbers.push(val);
            i--;
        }
        else if(s[i] == ')'){
            //dealing with the part between ( and ) characters
            while(!ops.empty() && ops.peek() != '('){
                double val2 = numbers.peek();
                numbers.pop();
                double val1 = numbers.peek();
                numbers.pop();
                char op = ops.peek();
                ops.pop();
                numbers.push(calculate(val1, val2, op));
            }
            ops.pop();
        }
        else{
            if(ops.empty() || ops.peek() == '(' || op_priority(ops.peek()) < op_priority(s[i]))
                ops.push(s[i]);//store the first operator , ( and the operator with higher order than the one on the top of the stack
            else{
                while(!ops.empty() && op_priority(ops.peek()) >= op_priority(s[i])){
                    double val2 = numbers.peek();
                    numbers.pop();
                    double val1 = numbers.peek();
                    numbers.pop();
                    char op = ops.peek();
                    ops.pop();
                    numbers.push(calculate(val1, val2, op));
                }
                ops.push(s[i]);
            }
        }
    }
    //keep doing the calculation until the stack with operator is empty
    while(!ops.empty()){
        double val2 = numbers.peek();
        numbers.pop();
        double val1 = numbers.peek();
        numbers.pop();
        char op = ops.peek();
        ops.pop();
        numbers.push(calculate(val1, val2, op));
    }

    return numbers.peek();
}

nStack::nStack(){
    top = -1;//initialization.
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
        return -1.0;
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
        return ' ';
    }
    return arr[top];
}

bool oStack::empty(){
    return top == -1;
}