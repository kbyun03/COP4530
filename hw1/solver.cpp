// Young0Bin Byun
// FSUID: YB23E
// EMPLID: 201093220

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <iterator>
#include <sstream>

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
        output << I.getName() <<  ":" << I.getValue();
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

template <class T>
void printVector(vector<T> &v){
    typename vector<T>::iterator i;

    for (i = v.begin(); i != v.end(); ++i)
    {
        cout << *i << " ";
    }
    cout << endl;
}

bool isOperator(string s){
    if(s == "+" || s == "-" || s == "*" || s == "*" || s == "/" || s == "(" || s == ")"){
        return true;
    }
    return false;
}

bool is_numeric (string &str) 
{
    auto result = double();
    // auto i = istringstream(str);
    istringstream i(str);
    i >> result;      
    return !i.fail() && i.eof();
}



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

vector<string> infixToPostFix(vector<std::string> &output){

    stack<string> operatorStack;
    string postFixOutput;
    vector<string> outputVector;

    for( vector<std::string>::iterator i = output.begin(); i != output.end(); i++){
        if(isOperator(*i)){
            if(operatorStack.empty()){
                operatorStack.push(*i);
            }
            else{
                if(*i == "("){
                    operatorStack.push(*i);
                }
                else if(*i == ")"){
                    while (operatorStack.top() != "("){
                        postFixOutput = postFixOutput + " " + operatorStack.top();
                        outputVector.push_back(operatorStack.top());
                        operatorStack.pop();
                    }
                    operatorStack.pop();
                }
                else{
                    string topOperator = operatorStack.top();

                    int topOperatorPrecedence = getOperatorPrecedence(topOperator);
                    int currentOperatorPrecence = getOperatorPrecedence(*i);

                    if(topOperatorPrecedence < currentOperatorPrecence){
                        // if current is heigher than lower, then just push operator to stack
                        operatorStack.push(*i);
                    }
                    else{
                        // if equal or lower, then
                        while(! (operatorStack.empty()) && (topOperatorPrecedence >= currentOperatorPrecence)){
                            postFixOutput = postFixOutput + " " + topOperator;
                            outputVector.push_back(topOperator);
                            operatorStack.pop();

                            topOperator = operatorStack.top();
                            topOperatorPrecedence = getOperatorPrecedence(topOperator);
                        }
                        operatorStack.push(*i);
                    }
                }
            }
        }
        else{
            postFixOutput = postFixOutput + " " + *i;
            outputVector.push_back(*i);
        }
    }

    while (!operatorStack.empty()){
        postFixOutput = postFixOutput + " " + operatorStack.top();
        outputVector.push_back(operatorStack.top());
        operatorStack.pop();
    }
    // return postFixOutput;
    return outputVector;
}

vector<string> tokenizer(string infixExpression){
    string token;
    vector<string>* output = new vector<string>();
    for( string::iterator i = infixExpression.begin(); i != infixExpression.end(); i++){
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

vector<Identifier> tokenizer(vector<string> &postFixExpression){
    string token;
    vector<Identifier>* output = new vector<Identifier>();

    for (vector<string>::iterator i = postFixExpression.begin(); i != postFixExpression.end(); ++i)
    {
        
        double val;
        string name = *i;
        if(is_numeric(*i)){
            val = stod(*i);
        }
        else{
            if(!isOperator(*i)){
                cout << "Enter the value of " << *i << ": ";
                cin >> val;
                cout << endl;
            }
            else{
                val = 0;
            }
        }
        Identifier id(name, val);
        output->push_back(id);
    }
    return *output;
}

double evaluateOperator(double left, double right, string op){
    double result;
    if(op == "+"){
        result = left + right;
    }
    else if(op == "-"){
        result = left - right;
    }
    else if(op == "*"){
        result = left * right;
    }
    else if(op == "/"){
        result = left / right;
    }
    return result;
}

double evaluatePostFix(vector<Identifier> identifierVector){
    stack<double> postfixStack;
    for (vector<Identifier>::iterator i = identifierVector.begin(); i != identifierVector.end(); ++i){
        if(isOperator((*i).getName())){
            double right = postfixStack.top();
            postfixStack.pop();
            double left = postfixStack.top();
            postfixStack.pop();
            double result = evaluateOperator(left, right, (*i).getName());
            postfixStack.push(result);
        }
        else{
            postfixStack.push((*i).getValue());
        }
        
    }
    return postfixStack.top();
}


int main(){
    
    cout << "Enter the infix expression: " << endl;
    string infixExpression;
    getline(cin, infixExpression);

    vector<string> output = tokenizer(infixExpression);

    vector<string> postFixOutput = infixToPostFix(output);
    cout << "postFixOutput is " << endl;
    printVector(postFixOutput);

    vector<Identifier> identifierVector = tokenizer(postFixOutput);
    // printVector(identifierVector);
    double postFixEvaluated = evaluatePostFix(identifierVector);
    cout << "result is " << postFixEvaluated << endl;
}