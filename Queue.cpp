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

// Измененный метод dequeue для возвращения удаленного значения
int Queue::dequeue() {
    if (!front) {
        std::cerr << "Queue is empty.\n";
        return -1; // Возвращаем значение для обозначения пустой очереди
    }
    int value = front->data; // Сохраняем значение, которое удалим
    QNode* temp = front;
    front = front->next;
    if (!front) {
        rear = nullptr;
    }
    delete temp;
    return value; // Возвращаем удаленный элемент
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

void Queue::display(std::ostream& os) const {
    QNode* temp = front;
    while (temp) {
        os << temp->data << " ";
        temp = temp->next;
    }
    os << std::endl;
}
