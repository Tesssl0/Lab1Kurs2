#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

// Узел для односвязного и двусвязного списка
template<typename T>
class LinkedListNode {
public:
    T data;
    LinkedListNode* next;
    LinkedListNode* prev;

    LinkedListNode(T value) : data(value), next(nullptr), prev(nullptr) {}
};

// Односвязный список
template<typename T>
class SinglyLinkedList {
private:
    LinkedListNode<T>* head;

public:
    SinglyLinkedList() : head(nullptr) {}
    ~SinglyLinkedList();

    void push_front(T value);
    void push_back(T value);
    void pop_front();
    void pop_back();
    T get(int index) const;
    void print(std::ostream& os) const;

private:
    void clear();
};

// Двусвязный список
template<typename T>
class DoublyLinkedList {
private:
    LinkedListNode<T>* head;

public:
    DoublyLinkedList() : head(nullptr) {}
    ~DoublyLinkedList();

    void push_front(T value);
    void push_back(T value);
    void pop_front();
    void pop_back();
    T get(int index) const;
    void print(std::ostream& os) const;

private:
    void clear();
};

#endif // LINKED_LIST_H