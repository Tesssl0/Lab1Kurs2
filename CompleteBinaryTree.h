#ifndef COMPLETE_BINARY_TREE_H
#define COMPLETE_BINARY_TREE_H

#include <iostream>
#include <queue>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value);
};

class CompleteBinaryTree {
private:
    Node* root;
    int size;

public:
    CompleteBinaryTree();
    void insert(int value);
    bool search(int value) const;
    bool isComplete() const;
    void read(std::ostream& os) const;
    ~CompleteBinaryTree();

private:
    bool searchHelper(Node* node, int value) const;
    bool isCompleteHelper(Node* node, int index, int numberNodes) const;
    void readHelper(Node* node, std::ostream& os) const;
    void clear(Node* node);
};

#endif // COMPLETE_BINARY_TREE_H