// Young0Bin Byun
// FSUID: YB23E
// EMPLID: 201093220

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <iterator>
#include <map>

using namespace std;

class Identifier{
public:
    Identifier(){
        name  = "";
        value = 0;
    }
    Identifier(string n, double v){
        name = n;
        value = v;
    }

    void setName(string n){
        name = n;
    }
    void setValue(double v){
        value = v;
    }

    string getName() const{
        return name;
    }
    double getValue() const{
        return value;
    }

    friend ostream &operator<<( ostream &output, const Identifier &I){
        output << I.getName() << I.getValue() << "\n";
        return output;
    }

    friend istream &operator>>( istream &in, Identifier &I){
        in >> I.name >> I.value;
        return in;
    }

private:
    string name;
    double value;
};

class CompareOperator{
public:
    bool operator()(string left, string right){
        // returns true if right is larger than or equals to left precedence
        int leftPrecedence = getOperatorPrecedence(left);
        int rightPrecedence = getOperatorPrecedence(right);
        if(leftPrecedence <= rightPrecedence){
            return true;
        }
        return false;
    }
private:
    int getOperatorPrecedence(string op){
        if(op == "*" || op == "/"){
            return 2;
        }
        else if(op == "+" || op == "-"){
            return 1;
        }
        else{
            return -1;
        }
    }
};

void printVector(vector<string> &v){
    cout << "------- printing vector -------" << endl;
    for (vector<string>::iterator i = v.begin(); i != v.end(); ++i)
        cout << *i << ", ";

    cout << "\n-------------------------------" << endl;
}

bool checkOperatorPrecedence(string left, string right){
    // returns true if right precedes left
    map<string, int> operatorPrecedenceMap;
    operatorPrecedenceMap["+"] = 1;
    operatorPrecedenceMap["-"] = 1;
    operatorPrecedenceMap["*"] = 2;
    operatorPrecedenceMap["/"] = 2;
    operatorPrecedenceMap["("] = 3;
    operatorPrecedenceMap[")"] = 3;

    int valueLeft = operatorPrecedenceMap[left];
    int valueRight = operatorPrecedenceMap[right];

    return valueLeft < valueRight;

}

bool isOperator(string s){
    if(s == "+" || s == "-" || s == "*" || s == "*" || s == "(" || s == ")"){
        return true;
    }
    return false;
}

string infixToPostFix(vector<std::string> &output){

    stack<string> operatorStack;
    string postFixOutput;
    CompareOperator cmp;

    for( vector<std::string>::iterator i = output.begin(); i != output.end(); i++){
        cout << "processing " << *i << endl;
        if(isOperator(*i)){
            if(operatorStack.empty()){
                cout << "stack is empty, pushing operator " << *i << endl;
                operatorStack.push(*i);
            }
            else{
                // something in the operatorStack
                if(*i == "("){
                    operatorStack.push(*i);
                }
                else if(*i == ")"){
                    while (operatorStack.top() != "("){
                        postFixOutput += *i;
                        operatorStack.pop();
                    }
                    operatorStack.pop();
                }
                else{
                    string topOperator = operatorStack.top();
                    if(checkOperatorPrecedence(topOperator, *i)){
                        // if current operator precede topOperator, then output the current operator
                        postFixOutput += *i;
                    }
                    else{
                        // current operator does not precede top Opeartor
                        while(! (operatorStack.empty()) && (cmp(*i, topOperator))){
                            postFixOutput += operatorStack.top();
                            operatorStack.pop();
                        }
                        operatorStack.push(*i);
                    }
                }

            }
        }
        else{
            postFixOutput += *i;
        }
        cout << "at the end of each loop " << postFixOutput << endl;
    }
    cout << "at the end" << endl;
    return postFixOutput;
}

vector<std::string> tokenizer(string infixExpression){
    cout << "tokenizer" << endl;
    string token;
    vector<string>* output = new vector<string>();
    for( string::iterator i = infixExpression.begin(); i != infixExpression.end()+1; i++){
        if(*i != ' '){
            token += *i;
        }
        else{
            output->push_back(token);
            token = "";
        }
    }
    if(token[0] != ' '){
        // if it is not just empty space, add last element to the output
        output->push_back(token);
    }
    return *output;
}


int main(){
    cout << "Enter the infix expression: " << endl;
    string infixExpression;
    getline(cin, infixExpression);
    cout << "entered : " << infixExpression << endl;

    vector<string> output = tokenizer(infixExpression);
    printVector(output);

    string postFixOutput = infixToPostFix(output);
    cout << "postFixOutput is " << postFixOutput << endl;




}