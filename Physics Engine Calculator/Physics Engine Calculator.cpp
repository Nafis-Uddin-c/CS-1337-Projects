// Name: Nafis Uddin


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Data.h"
#include "Node.h"
#include "Stack.h"



int precedence(char token)
{
    if(token == '^') return 3;   // highest precedence
    else if(token == '*' || token == '/') return 2;   // second highest precedence
    else if(token == '+' || token == '-') return 1;     // lowest precedence
    else return 0;
}

string convertToPostfix(string expression)
{
    Stack stack;
    Node *newnode = nullptr;
    string postfix;

    for(char token : expression)       // reading the expression
    {
        if(isdigit(token) || token == '.')      
        {
            postfix += token;       // if the character is digit or has the point (.) character
                                    // adding them into the postfix
        }

        else if(token == '(')
        {
            newnode = new Node (Data(token));       // if the character is '(', create a new node
            stack<<newnode;         // add the node into the stack
        }

        else if(token == ')')           // if the character is ')'
        {
            while(stack.getHead() && stack.getHead()->getPayload().getOperator()!= '(')
            {           // while the head of the stack linked list isn't nullptr, and the operator of the 
                        // head isn't '(' character
                postfix += ' ';         
                postfix += stack.getHead()->getPayload().getOperator();     // add the operator of the head node
                stack>>newnode;         // popping the head every time in the loop
            }
            stack>>newnode;         // pop the head to remove the '(' character
        }
 
       else     // if any other character
       {
            postfix += ' ';
            while (stack.getHead() && stack.getHead()->getPayload().getOperator()!= '(' 
            && precedence(stack.getHead()->getPayload().getOperator()) >= precedence(token))
            // check if the head of the stack isn't nullptr, and the head node operator hasn't a '(' character
            // and the precedence of the head node operator has the highest value than the current character

            {
                postfix += stack.getHead()->getPayload().getOperator();     
                // adding the head node operator to the postfix in the loop
                postfix += ' '; 
                stack>>newnode;     // popping the head in the loop 
            }
            newnode = new Node (Data(token)); // outside of the loop, create a new node with the current character/ operator
            stack<<newnode;         // add the newnode into the stack
       }

    }

    while(stack.getHead())      // if the head has still some other operator
    {
        postfix += ' ';
        postfix += stack.getHead()->getPayload().getOperator();     // adding them into the postfix using loop 
        stack>>newnode;;        // also popping the head every time
    }

    return postfix;     // return the postfix
}   




double convertToValue(string postfix)
{
    double value = 0;
    Stack stack;
    string full_digit;
    bool space = false;
    Node *newnode = nullptr;

    for(char token: postfix)
    {
        if(isdigit(token) || token == '.')   // is the character is digit or '.', add them into a string 
        {
            full_digit += token;    // this string will cover the whole digit of double value
            space = true;       // checking if the character is digit or '.'
        }

        else if(token == ' ' && space == true)      // if the character is a space and the character doesn't meet
        {                                          // any operator rather than digit
            newnode = new Node(Data(stod(full_digit)));         // create a new node and send the double value to then node operand
            stack<<newnode;     // push the node into the stack
            full_digit = "";        // reset the string
        }


        else if(token == '*' || token == '+' || token == '-' || token == '/' || token == '^')
        {
            space = false;

            double left = stack.getHead()->getPayload().getOperand();  // get the operand from the stack
            stack>>newnode;  // pop the node

            double right = stack.getHead()->getPayload().getOperand();  // get the operand from the stack
            stack>>newnode;  // pop the node

            switch (token)      // check the character
            {
                case '+':
                    value = left + right;
                    break;
                case '-':
                    value = right - left;
                    break;
                case '*':
                    value = right * left;
                    break;
                case '/':
                    value = right / left;
                    break;
                case '^':
                    value = pow(right,left);
                    break;
                default:
                    break;
            }

            newnode = new Node (Data(value));       // send the value to the node operand
            stack<<newnode;     // add the node to the stack
            
        }
        
    }

    if(stack.getHead()) 
    {
        value = stack.getHead()->getPayload().getOperand(); // get the head operand of the stack
        stack>>newnode;     // pop the node
    }
    
    return value;       // return the value
}   




int main()
{
    string filename, expression;
    cout<<"Enter the filename "<<std::endl;

    cin>>filename;

    std::fstream file (filename, ios::binary | ios::in | ios::out);     
    if(file)        // checking if the file exists
    {   
         while(getline(file, expression))
        {
            string postfix = convertToPostfix(expression);      // getting the postfix expression
            double value  = convertToValue(postfix);        // getting the value of the expression
            cout<< postfix <<"\t"<<fixed <<setprecision(3) <<value<<endl;
        }

        file.close();
    }
    return 0;

}
