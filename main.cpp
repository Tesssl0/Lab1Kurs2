#include <iostream>
#include <fstream>
#include "Array.h"
#include "CompleteBinaryTree.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

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
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> hashTables;
    std::unordered_map<std::string, std::unordered_set<std::string>> sets;

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
            std::string hashName, key, value;
            inputFile >> hashName >> key >> value;
            hashTables[hashName][key] = value;
            outputFile << "HSET: Added key " << key << " with value " << value << " to hash " << hashName << std::endl;
        } else if (command == "SPUSH") {
            int item;
            inputFile >> item;
            stack.push(item);
            outputFile << "SPUSH: Pushed " << item << " onto the stack" << std::endl;
        } else if (command == "QPOP") {
            if (!queue.isEmpty()) {
                int item = queue.dequeue();  // Здесь вызываем dequeue, чтобы получить значение
                outputFile << "QPOP: Popped " << item << " from the queue" << std::endl;
            } else {
                outputFile << "QPOP: Queue is empty" << std::endl;
            }
        } else if (command == "SISMEMBER") {
            std::string setName, value;
            inputFile >> setName >> value;
            bool isMember = sets[setName].find(value) != sets[setName].end();
            outputFile << "SISMEMBER: Element " << value << " in set " << setName << ": " << (isMember ? "TRUE" : "FALSE") << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
