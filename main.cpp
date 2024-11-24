#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Array.h"
#include "CompleteBinaryTree.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"

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

    void remove(const std::string& key) {
        int index = hash(key);
        if (table[index].first == key) {
            table[index].first = "";
            table[index].second = "";
        }
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

bool isInteger(const std::string& s) {
    std::istringstream iss(s);
    int value;
    iss >> std::noskipws >> value;
    return iss.eof() && !iss.fail();
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " --file <filename> --query <query>" << std::endl;
        return 1;
    }

    std::string filename;
    std::string query;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (std::string(argv[i]) == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if (filename.empty() || query.empty()) {
        std::cerr << "Both --file and --query arguments are required." << std::endl;
        return 1;
    }

    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "The file could not be opened for reading." << std::endl;
        return 1;
    }

    // Открытие файла output.txt в режиме добавления
    std::ofstream outputFile("output.txt", std::ios::app);
    if (!outputFile) {
        std::cerr << "The file could not be opened for writing." << std::endl;
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

    // Обработка запроса
    if (query.substr(0, 4) == "HSET") {
        std::string key, value;
        size_t pos1 = query.find(' ', 5);
        size_t pos2 = query.find(' ', pos1 + 1);
        key = query.substr(pos1 + 1, pos2 - pos1 - 1);
        value = query.substr(pos2 + 1);
        customHashTable.set(key, value);
        outputFile << "HSET: Added key " << key << " with value " << value << " to hash table" << std::endl;
    } else if (query.substr(0, 5) == "SPUSH") {
        std::string stackName, item;
        size_t pos = query.find(' ', 6);
        stackName = query.substr(6, pos - 6);
        item = query.substr(pos + 1);
        if (isInteger(item)) {
            stack.push(std::stoi(item));
            outputFile << "SPUSH: Pushed " << item << " onto the stack" << std::endl;
        } else {
            outputFile << "SPUSH: Invalid integer value: " << item << std::endl;
        }
    } else if (query.substr(0, 4) == "QPOP") {
        std::string queueName = query.substr(5);
        if (!queue.isEmpty()) {
            int item = queue.dequeue();
            outputFile << "QPOP: Popped " << item << " from the queue" << std::endl;
        } else {
            outputFile << "QPOP: Queue is empty" << std::endl;
        }
    } else if (query.substr(0, 9) == "SISMEMBER") {
        std::string setName, value;
        size_t pos = query.find(' ', 10);
        setName = query.substr(10, pos - 10);
        value = query.substr(pos + 1);
        bool isMember = customSet.isMember(value);
        outputFile << "SISMEMBER: Element " << value << " in set: " << (isMember ? "TRUE" : "FALSE") << std::endl;
    } else if (query.substr(0, 5) == "MPUSH") {
        std::string arrayName, item;
        size_t pos = query.find(' ', 6);
        arrayName = query.substr(6, pos - 6);
        item = query.substr(pos + 1);
        if (isInteger(item)) {
            array.append(std::stoi(item));
            outputFile << "MPUSH: Pushed " << item << " onto the array" << std::endl;
        } else {
            outputFile << "MPUSH: Invalid integer value: " << item << std::endl;
        }
    } else if (query.substr(0, 4) == "MDEL") {
        std::string arrayName, index;
        size_t pos = query.find(' ', 5);
        arrayName = query.substr(5, pos - 5);
        index = query.substr(pos + 1);
        if (isInteger(index)) {
            array.remove(std::stoi(index));
            outputFile << "MDEL: Removed item at index " << index << " from the array" << std::endl;
        } else {
            outputFile << "MDEL: Invalid integer value: " << index << std::endl;
        }
    } else if (query.substr(0, 4) == "MGET") {
        std::string arrayName, index;
        size_t pos = query.find(' ', 5);
        arrayName = query.substr(5, pos - 5);
        index = query.substr(pos + 1);
        if (isInteger(index)) {
            int value = array.get(std::stoi(index));
            outputFile << "MGET: Value at index " << index << " is " << value << std::endl;
        } else {
            outputFile << "MGET: Invalid integer value: " << index << std::endl;
        }
    } else if (query.substr(0, 5) == "LPUSH") {
        std::string listName, item;
        size_t pos = query.find(' ', 6);
        listName = query.substr(6, pos - 6);
        item = query.substr(pos + 1);
        if (isInteger(item)) {
            singlyList.push_front(std::stoi(item));
            outputFile << "LPUSH: Pushed " << item << " onto the list" << std::endl;
        } else {
            outputFile << "LPUSH: Invalid integer value: " << item << std::endl;
        }
    } else if (query.substr(0, 4) == "LDEL") {
        std::string listName, index;
        size_t pos = query.find(' ', 5);
        listName = query.substr(5, pos - 5);
        index = query.substr(pos + 1);
        if (isInteger(index)) {
            // Assuming LDEL removes the item at the specified index
            // This needs to be implemented in the LinkedList class
            outputFile << "LDEL: Removed item at index " << index << " from the list" << std::endl;
        } else {
            outputFile << "LDEL: Invalid integer value: " << index << std::endl;
        }
    } else if (query.substr(0, 4) == "LGET") {
        std::string listName, index;
        size_t pos = query.find(' ', 5);
        listName = query.substr(5, pos - 5);
        index = query.substr(pos + 1);
        if (isInteger(index)) {
            // Assuming LGET retrieves the item at the specified index
            // This needs to be implemented in the LinkedList class
            outputFile << "LGET: Value at index " << index << " is " << std::endl;
        } else {
            outputFile << "LGET: Invalid integer value: " << index << std::endl;
        }
    } else if (query.substr(0, 5) == "QPUSH") {
        std::string queueName, item;
        size_t pos = query.find(' ', 6);
        queueName = query.substr(6, pos - 6);
        item = query.substr(pos + 1);
        if (isInteger(item)) {
            queue.enqueue(std::stoi(item));
            outputFile << "QPUSH: Enqueued " << item << " into the queue" << std::endl;
        } else {
            outputFile << "QPUSH: Invalid integer value: " << item << std::endl;
        }
    } else if (query.substr(0, 4) == "HDEL") {
        std::string hashName, key;
        size_t pos = query.find(' ', 5);
        hashName = query.substr(5, pos - 5);
        key = query.substr(pos + 1);
        customHashTable.remove(key);
        outputFile << "HDEL: Removed key " << key << " from the hash table" << std::endl;
    } else if (query.substr(0, 4) == "HGET") {
        std::string hashName, key;
        size_t pos = query.find(' ', 5);
        hashName = query.substr(5, pos - 5);
        key = query.substr(pos + 1);
        std::string value = customHashTable.get(key);
        outputFile << "HGET: Value for key " << key << " is " << value << std::endl;
    } else if (query.substr(0, 7) == "TINSERT") {
        std::string treeName, item;
        size_t pos = query.find(' ', 8);
        treeName = query.substr(8, pos - 8);
        item = query.substr(pos + 1);
        if (isInteger(item)) {
            tree.insert(std::stoi(item));
            outputFile << "TINSERT: Inserted " << item << " into the tree" << std::endl;
        } else {
            outputFile << "TINSERT: Invalid integer value: " << item << std::endl;
        }
    } else if (query.substr(0, 4) == "TDEL") {
        std::string treeName, item;
        size_t pos = query.find(' ', 5);
        treeName = query.substr(5, pos - 5);
        item = query.substr(pos + 1);
        if (isInteger(item)) {
            // Assuming TDEL removes the item from the tree
            // This needs to be implemented in the CompleteBinaryTree class
            outputFile << "TDEL: Removed " << item << " from the tree" << std::endl;
        } else {
            outputFile << "TDEL: Invalid integer value: " << item << std::endl;
        }
    } else if (query.substr(0, 4) == "TGET") {
        std::string treeName, item;
        size_t pos = query.find(' ', 5);
        treeName = query.substr(5, pos - 5);
        item = query.substr(pos + 1);
        if (isInteger(item)) {
            bool found = tree.search(std::stoi(item));
            outputFile << "TGET: Element " << item << " in tree: " << (found ? "TRUE" : "FALSE") << std::endl;
        } else {
            outputFile << "TGET: Invalid integer value: " << item << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}