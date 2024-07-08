#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <iostream>

class Stack
{
private:
    Node * head;

public:
    Stack();
    Stack(Node *node1); 

    Stack(const Stack& Stack1);
    ~Stack();
    
    Node *getHead() const;
    void setHead(Node * node1);
 
    Stack& operator<<(Node *&);
    Stack& operator>>(Node *&);
    friend std::ostream & operator<<(std::ostream&, const Stack&);

};

#endif
