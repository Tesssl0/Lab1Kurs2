#include "Queue.h"

QNode::QNode(int value) : data(value), next(nullptr) {}

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(int value) {
    QNode* newQNode = new QNode(value);
    if (!rear) {
        front = rear = newQNode;
        return;
    }
    rear->next = newQNode;
    rear = newQNode;
}

int Queue::dequeue() {
    if (!front) {
        std::cerr << "Queue is empty.\n";
        return -1;
    }
    int value = front->data;
    QNode* temp = front;
    front = front->next;
    if (!front) {
        rear = nullptr;
    }
    delete temp;
    return value;
}

int Queue::peek() const {
    if (!front) {
        std::cerr << "Queue is empty.\n";
        return -1;
    }
    return front->data;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

void Queue::print(std::ostream& os) const {
    QNode* temp = front;
    while (temp) {
        os << temp->data << " ";
        temp = temp->next;
    }
    os << std::endl;
}