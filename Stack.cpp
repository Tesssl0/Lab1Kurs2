#include "Stack.h"

StackNode::StackNode(int value) : data(value), next(nullptr) {}

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    while (top) {
        pop();
    }
}

void Stack::push(int value) {
    StackNode* newStackNode = new StackNode(value);
    newStackNode->next = top;
    top = newStackNode;
}

void Stack::pop() {
    if (!top) {
        std::cerr << "Stack is empty.\n";
        return;
    }
    StackNode* temp = top;
    top = top->next;
    delete temp;
}

void Stack::read(std::ostream& os) const {
    StackNode* temp = top;
    while (temp) {
        os << temp->data << " ";
        temp = temp->next;
    }
    os << std::endl;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}