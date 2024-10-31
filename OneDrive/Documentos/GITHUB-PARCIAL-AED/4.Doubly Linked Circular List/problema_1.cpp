// https://leetcode.com/problems/all-oone-data-structure/

#include <string>
#include <iostream>

using namespace std;

struct Node {
    int count;
    string key;
    Node* previous;
    Node* next;

    Node(int count, string key) : count(count), key(key), previous(nullptr), next(nullptr) {}
};

class DoubleLinkedList {
public:
    Node* start;
    Node* end;

    DoubleLinkedList() {
        start = nullptr;
        end = nullptr;
    }

    void insert_front(Node* node) {
        if (!start) {
            start = end = node;
        } else {
            node->next = start;
            start->previous = node;
            start = node;
        }
    }

    void remove(Node* node) {
        if (!node->previous && !node->next) {
            start = end = nullptr;
        } else if (!node->previous) {
            start = node->next;
            start->previous = nullptr;
        } else if (!node->next) {
            end = node->previous;
            end->next = nullptr;
        } else {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }
    }
};

class HashTable {
private:
    static const int SIZE = 1000;
    Node* table[SIZE];

    int hashFunction(string key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % SIZE;
        }
        return hashValue;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    Node* get(string key) {
        int idx = hashFunction(key);
        Node* entry = table[idx];
        while (entry != nullptr) {
            if (entry->key == key) {
                return entry;
            }
            entry = entry->next;
        }
        return nullptr;
    }

    void insert(string key, int count) {
        int idx = hashFunction(key);
        Node* entry = table[idx];
        while (entry != nullptr) {
            if (entry->key == key) {
                entry->count = count;
                return;
            }
            entry = entry->next;
        }
        Node* newNode = new Node(count, key);
        newNode->next = table[idx];
        table[idx] = newNode;
    }

    void remove(string key) {
        int idx = hashFunction(key);
        Node* entry = table[idx];
        Node* prev = nullptr;
        while (entry != nullptr) {
            if (entry->key == key) {
                if (prev != nullptr) {
                    prev->next = entry->next;
                } else {
                    table[idx] = entry->next;
                }
                return;
            }
            prev = entry;
            entry = entry->next;
        }
    }
};

class AllOne {
private:
    HashTable keyCounts;
    DoubleLinkedList countList;

public:
    AllOne() {}

    void inc(string key) {
        Node* node = keyCounts.get(key);
        if (!node) {
            keyCounts.insert(key, 1);
            countList.insert_front(new Node(1, key));
        } else {
            int count = node->count;
            countList.remove(node);
            keyCounts.insert(key, count + 1);
            countList.insert_front(new Node(count + 1, key));
        }
    }

    void dec(string key) {
        Node* node = keyCounts.get(key);
        if (!node) return;

        int count = node->count;
        countList.remove(node);

        if (count == 1) {
            keyCounts.remove(key);
        } else {
            keyCounts.insert(key, count - 1);
            countList.insert_front(new Node(count - 1, key));
        }
    }

    string getMaxKey() {
        if (!countList.end) return "";
        return countList.end->key;
    }

    string getMinKey() {
        if (!countList.start) return "";
        return countList.start->key;
    }
};
