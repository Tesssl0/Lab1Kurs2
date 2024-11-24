#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array {
private:
    int* data;
    size_t capacity;
    size_t length;

public:
    Array(size_t initialCapacity = 10);
    ~Array();
    void append(int value);
    void insert(int index, int value);
    int get(int index) const;
    void remove(int index);
    void replace(int index, int value);
    size_t size() const;
    void print(std::ostream& os) const;

private:
    void resize();
};

#endif // ARRAY_H