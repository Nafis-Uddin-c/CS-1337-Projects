#include "Stack.h"

Stack::Stack() 
{
    head = nullptr;
}


Stack::Stack(Node* node1) 
{
    head = node1;
}

void deleteNode(Node *node)
{
    if(node)
    {
        node = node->getNext();
        deleteNode(node);
        delete node;
    }
}
Stack::~Stack()
{
    deleteNode(head);
}


Stack::Stack(const Stack& Stack1) 
{
    if(Stack1.head == nullptr) head = nullptr;
    else 
    {
        Node *temp = Stack1.head;
        Node *newnode = new Node(temp->getPayload());
        head = newnode;
        temp = temp->getNext();
        while(temp)
        {
            newnode->setNext(new Node(temp->getPayload()));
            temp = temp->getNext();
            newnode = newnode->getNext();
        }

    }
} 



Node* Stack::getHead() const 
{
    return head;
}


void Stack::setHead(Node* node1) 
{
    head = node1;
}

 
Stack & Stack::operator<<(Node *& node)
{
    node->setNext(head);
    head = node;
    return *this;
}


Stack & Stack::operator>>(Node *& node)
{
    node = head;
    if(node)
    {
        head = head->getNext();
        node->setNext(nullptr);
    }
    return *this;
}


std::ostream& operator<<(std::ostream& out, const Stack & stack)
{
    Node *temp = stack.getHead();
    if(temp)
    {
        while(temp)
        {
            if(temp->getPayload().getOperand())
            out << temp->getPayload().getOperand();
            
            else out << temp->getPayload().getOperator();

            if(temp->getNext()) out << ", ";
            temp = temp->getNext();
        }
    }

    return out;
}
