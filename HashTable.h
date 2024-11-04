#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

class HashNode {
public:
    int key;
    int value;
    HashNode* next;

    HashNode(int k, int v);
};

class HashTable {
private:
    HashNode** table;
    size_t size;

public:
    HashTable(size_t s);
    ~HashTable();
    void set(int key, int value);
    int get(int key) const;
    void remove(int key);
    void display(std::ostream& os) const;

private:
    size_t hashFunction(int key) const;
};

#endif // HASH_TABLE_H