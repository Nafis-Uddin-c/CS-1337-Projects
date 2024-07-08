#ifndef NODE_H
#define NODE_H

#include "Data.h"

class Node 
{
private:
    Data payload;
    Node* next;

public:
    Node()     { payload = Data(); next = nullptr; }
    Node(const Data& payload)   { this->payload = payload; }
    Node(const Data& payload, Node* next)   { this->payload = payload; this->next = next; }

    Data getPayload()      { return payload; }
    Node* getNext()        { return next; }

    void setPayload(const Data& payload1)      { payload = payload1; }
    void setNext(Node* next1)                   { this->next = next1; }
};
 
#endif
