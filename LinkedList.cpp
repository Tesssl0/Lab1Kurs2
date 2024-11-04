#include "LinkedList.h"

// Реализация методов односвязного списка
template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template<typename T>
void SinglyLinkedList<T>::push_front(T value) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(value);
    newNode->next = head;
    head = newNode;
}

template<typename T>
void SinglyLinkedList<T>::push_back(T value) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(value);
    if (!head) {
        head = newNode;
        return;
    }
    LinkedListNode<T>* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

template<typename T>
void SinglyLinkedList<T>::pop_front() {
    if (!head) return;
    LinkedListNode<T>* temp = head;
    head = head->next;
    delete temp;
}

template<typename T>
void SinglyLinkedList<T>::pop_back() {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    LinkedListNode<T>* current = head;
    while (current->next->next) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}

template<typename T>
void SinglyLinkedList<T>::print(std::ostream& os) const {
    LinkedListNode<T>* current = head;
    while (current) {
        os << current->data << " ";
        current = current->next;
    }
    os << std::endl;
}

template<typename T>
void SinglyLinkedList<T>::clear() {
    while (head) {
        pop_front();
    }
}

// Реализация методов двусвязного списка
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void DoublyLinkedList<T>::push_front(T value) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(value);
    if (head) {
        newNode->next = head;
        head->prev = newNode;
    }
    head = newNode;
}

template<typename T>
void DoublyLinkedList<T>::push_back(T value) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(value);
    if (!head) {
        head = newNode;
        return;
    }
    LinkedListNode<T>* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (!head) return;
    LinkedListNode<T>* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    }
    delete temp;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    LinkedListNode<T>* current = head;
    while (current->next) {
        current = current->next;
    }
    current->prev->next = nullptr;
    delete current;
}

template<typename T>
void DoublyLinkedList<T>::print(std::ostream& os) const {
    LinkedListNode<T>* current = head;
    while (current) {
        os << current->data << " ";
        current = current->next;
    }
    os << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    while (head) {
        pop_front();
    }
}

// Инстанцирование шаблонных методов для типа int
template class SinglyLinkedList<int>;
template class DoublyLinkedList<int>;