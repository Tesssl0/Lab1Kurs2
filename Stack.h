#ifndef STACK_H
#define STACK_H

#include <iostream>

class StackNode {
public:
    int data;
    StackNode* next;

    StackNode(int value);
};

class Stack {
private:
    StackNode* top;

public:
    Stack();
    ~Stack();
    void push(int value);
    void pop();
    void read(std::ostream& os) const;
    bool isEmpty() const;
};

#endif // STACK_H