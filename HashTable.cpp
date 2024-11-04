#include "HashTable.h"

HashNode::HashNode(int k, int v) : key(k), value(v), next(nullptr) {}

HashTable::HashTable(size_t s) : size(s) {
    table = new HashNode*[size]();
}

HashTable::~HashTable() {
    for (size_t i = 0; i < size; ++i) {
        HashNode* temp = table[i];
        while (temp) {
            HashNode* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
    delete[] table;
}

size_t HashTable::hashFunction(int key) const {
    return key % size;
}

void HashTable::set(int key, int value) {
    size_t index = hashFunction(key);
    HashNode* newNode = new HashNode(key, value);
    if (!table[index]) {
        table[index] = newNode;
    } else {
        HashNode* temp = table[index];
        while (temp->next) {
            if (temp->key == key) {
                temp->value = value;
                delete newNode;
                return;
            }
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int HashTable::get(int key) const {
    size_t index = hashFunction(key);
    HashNode* temp = table[index];
    while (temp) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    std::cerr << "Key not found.\n";
    return -1;
}

void HashTable::remove(int key) {
    size_t index = hashFunction(key);
    HashNode* temp = table[index];
    HashNode* prev = nullptr;

    while (temp) {
        if (temp->key == key) {
            if (prev) {
                prev->next = temp->next;
            } else {
                table[index] = temp->next;
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    std::cerr << "Key not found.\n";
}

void HashTable::display(std::ostream& os) const {
    for (size_t i = 0; i < size; ++i) {
        HashNode* temp = table[i];
        os << "Index " << i << ": ";
        while (temp) {
            os << "[" << temp->key << ": " << temp->value << "] -> ";
            temp = temp->next;
        }
        os << "nullptr" << std::endl;
    }
}