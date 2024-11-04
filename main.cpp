#include <iostream>
#include <fstream>
#include "Array.h"
#include "CompleteBinaryTree.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include <string>

// Кастомная хеш-таблица для хранения строковых ключей и значений
class CustomHashTable {
public:
    CustomHashTable(int size) : size(size) {
        table = new std::pair<std::string, std::string>[size];
        for (int i = 0; i < size; ++i) {
            table[i].first = "";
        }
    }

    void set(const std::string& key, const std::string& value) {
        int index = hash(key);
        table[index] = {key, value};
    }

    std::string get(const std::string& key) {
        int index = hash(key);
        if (table[index].first == key) {
            return table[index].second;
        }
        return "";
    }

private:
    int hash(const std::string& key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % size;
        }
        return hashValue;
    }

    std::pair<std::string, std::string>* table;
    int size;
};

// Кастомный Set для работы с уникальными значениями
class CustomSet {
public:
    CustomSet(int size) : size(size) {
        setArray = new std::string[size];
        count = 0;
    }

    void insert(const std::string& value) {
        if (!isMember(value)) {
            setArray[count++] = value;
        }
    }

    bool isMember(const std::string& value) {
        for (int i = 0; i < count; ++i) {
            if (setArray[i] == value) return true;
        }
        return false;
    }

private:
    std::string* setArray;
    int size;
    int count;
};

int main() {
    std::ifstream inputFile("123.txt");
    if (!inputFile) {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
        return 1;
    }

    std::ofstream outputFile("output.txt");
    if (!outputFile) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return 1;
    }

    // Инициализация структур данных
    Array array(10); 
    SinglyLinkedList<int> singlyList;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    CompleteBinaryTree tree;
    CustomHashTable customHashTable(10);
    CustomSet customSet(10);

    std::string command;
    while (inputFile >> command) {
        std::cout << "Command: " << command << std::endl; // Отладочный вывод

        if (command == "ArrayAppend") {
            int value;
            inputFile >> value;
            array.append(value);
        } else if (command == "ArrayInsert") {
            int index, value;
            inputFile >> index >> value;
            array.insert(index, value);
        } else if (command == "ArrayRemove") {
            int index;
            inputFile >> index;
            array.remove(index);
        } else if (command == "ArrayPrint") {
            outputFile << "Array contents:\n";
            for (size_t i = 0; i < array.size(); i++) {
                outputFile << array.get(i) << " ";
            }
            outputFile << std::endl;
        } else if (command == "ListPushFront") {
            int value;
            inputFile >> value;
            singlyList.push_front(value);
        } else if (command == "ListPushBack") {
            int value;
            inputFile >> value;
            singlyList.push_back(value);
        } else if (command == "ListPopFront") {
            singlyList.pop_front();
        } else if (command == "ListPopBack") {
            singlyList.pop_back();
        } else if (command == "ListPrint") {
            outputFile << "Linked List contents:\n";
            singlyList.print(outputFile);
            singlyList.print(std::cout);
        } else if (command == "StackPush") {
            int value;
            inputFile >> value;
            stack.push(value);
        } else if (command == "StackPop") {
            stack.pop();
        } else if (command == "StackPrint") {
            outputFile << "Stack contents:\n";
            stack.read(outputFile);
            stack.read(std::cout);
        } else if (command == "QueueEnqueue") {
            int value;
            inputFile >> value;
            queue.enqueue(value);
        } else if (command == "QueueDequeue") {
            queue.dequeue();
        } else if (command == "QueuePrint") {
            outputFile << "Queue contents:\n";
            queue.display(outputFile);
            queue.display(std::cout);
        } else if (command == "HashSet") {
            int key, value;
            inputFile >> key >> value;
            hashTable.set(key, value);
        } else if (command == "HashRemove") {
            int key;
            inputFile >> key;
            hashTable.remove(key);
        } else if (command == "HashPrint") {
            outputFile << "Hash Table contents:\n";
            hashTable.display(outputFile);
            hashTable.display(std::cout);
        } else if (command == "TreeInsert") {
            int value;
            inputFile >> value;
            tree.insert(value);
        } else if (command == "TreeSearch") {
            int value;
            inputFile >> value;
            bool found = tree.search(value);
            outputFile << "Search " << value << ": " << (found ? "found" : "not found") << std::endl;
        } else if (command == "TreeCheckComplete") {
            bool isComplete = tree.isComplete();
            outputFile << "Tree completeness: " << (isComplete ? "complete" : "not complete") << std::endl;
        } else if (command == "TreePrint") {
            outputFile << "Tree contents:\n";
            tree.read(outputFile);
            tree.read(std::cout);
        }

        // Новые команды для работы с дополнительными структурами
        else if (command == "HSET") {
            std::string key, value;
            inputFile >> key >> value;
            customHashTable.set(key, value);
            outputFile << "HSET: Added key " << key << " with value " << value << " to hash table" << std::endl;
        } else if (command == "SPUSH") {
            int item;
            inputFile >> item;
            stack.push(item);
            outputFile << "SPUSH: Pushed " << item << " onto the stack" << std::endl;
        } else if (command == "QPOP") {
            if (!queue.isEmpty()) {
                int item = queue.dequeue();
                outputFile << "QPOP: Popped " << item << " from the queue" << std::endl;
            } else {
                outputFile << "QPOP: Queue is empty" << std::endl;
            }
        } else if (command == "SISMEMBER") {
            std::string value;
            inputFile >> value;
            bool isMember = customSet.isMember(value);
            outputFile << "SISMEMBER: Element " << value << " in set: " << (isMember ? "TRUE" : "FALSE") << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
