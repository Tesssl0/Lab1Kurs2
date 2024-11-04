#include "Array.h"

Array::Array(size_t initialCapacity) : capacity(initialCapacity), length(0) {
    data = new int[capacity];
}

Array::~Array() {
    delete[] data;
}

void Array::append(int value) {
    if (length >= capacity) {
        resize();
    }
    data[length++] = value;
}

void Array::insert(int index, int value) {
    if (index < 0 || index > length) {
        std::cerr << "Index out of range.\n";
        return;
    }
    if (length >= capacity) {
        resize();
    }
    for (size_t i = length; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    length++;
}

int Array::get(int index) const {
    if (index < 0 || index >= length) {
        std::cerr << "Index out of range.\n";
        return -1;
    }
    return data[index];
}

void Array::remove(int index) {
    if (index < 0 || index >= length) {
        std::cerr << "Index out of range.\n";
        return;
    }
    for (size_t i = index; i < length - 1; ++i) {
        data[i] = data[i + 1];
    }
    length--;
}

void Array::replace(int index, int value) {
    if (index < 0 || index >= length) {
        std::cerr << "Index out of range.\n";
        return;
    }
    data[index] = value;
}

size_t Array::size() const {
    return length;
}

void Array::read(std::ostream& os) const { // Изменено на передачу потока вывода
    for (size_t i = 0; i < length; ++i) {
        os << data[i] << " ";
    }
    os << std::endl;
}

void Array::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (size_t i = 0; i < length; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}