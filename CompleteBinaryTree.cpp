#include "CompleteBinaryTree.h"

Node::Node(int value) : data(value), left(nullptr), right(nullptr) {}

CompleteBinaryTree::CompleteBinaryTree() : root(nullptr), size(0) {}

void CompleteBinaryTree::insert(int value) {
    Node* newNode = new Node(value);
    if (!root) {
        root = newNode;
        size++;
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (!current->left) {
            current->left = newNode;
            size++;
            return;
        } else {
            q.push(current->left);
        }

        if (!current->right) {
            current->right = newNode;
            size++;
            return;
        } else {
            q.push(current->right);
        }
    }
}

bool CompleteBinaryTree::search(int value) const {
    return searchHelper(root, value);
}

bool CompleteBinaryTree::searchHelper(Node* node, int value) const {
    if (!node) return false;
    if (node->data == value) return true;
    return searchHelper(node->left, value) || searchHelper(node->right, value);
}

bool CompleteBinaryTree::isComplete() const {
    return isCompleteHelper(root, 0, size);
}

bool CompleteBinaryTree::isCompleteHelper(Node* node, int index, int numberNodes) const {
    if (!node) return true;
    if (index >= numberNodes) return false;

    return isCompleteHelper(node->left, 2 * index + 1, numberNodes) &&
           isCompleteHelper(node->right, 2 * index + 2, numberNodes);
}

void CompleteBinaryTree::read(std::ostream& os) const {
    readHelper(root, os);
    os << std::endl;
}

void CompleteBinaryTree::readHelper(Node* node, std::ostream& os) const {
    if (!node) return;
    os << node->data << " ";
    readHelper(node->left, os);
    readHelper(node->right, os);
}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear(root);
}

void CompleteBinaryTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}