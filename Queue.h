#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

class QNode {
public:
    int data;
    QNode* next;

    QNode(int value);
};

class Queue {
private:
    QNode* front;
    QNode* rear;

public:
    Queue();
    ~Queue();
    void enqueue(int value);
    int dequeue();
    int peek() const;
    bool isEmpty() const;
    void print(std::ostream& os) const;
};

#endif // QUEUE_H