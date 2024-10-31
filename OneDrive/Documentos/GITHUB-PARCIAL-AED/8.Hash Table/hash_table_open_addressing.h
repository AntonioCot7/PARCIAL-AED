#ifndef GITHUB_PARCIAL_AED_HASH_TABLE_OPEN_ADDRESSING_H
#define GITHUB_PARCIAL_AED_HASH_TABLE_OPEN_ADDRESSING_H

#include <functional>
#include <utility>
#include <stdexcept>

template <typename K, typename V>
class HashTable {
    std::pair<K, V>** table;
    bool* isOccupied;
    int size;
    int count;

    int hash(const K& key) const {
        return std::hash<K>{}(key) % size;
    }

    int probe(int index, int i) const {
        return (index + i) % size;
    }

    void resize() {
        int newCapacity = size * 2;
        std::pair<K, V>** newTable = new std::pair<K, V>*[newCapacity];
        bool* newIsOccupied = new bool[newCapacity]();

        for (int i = 0; i < newCapacity; ++i) {
            newTable[i] = nullptr;
            newIsOccupied[i] = false;
        }

        for (int i = 0; i < size; ++i) {
            if (isOccupied[i]) {
                int index = std::hash<K>{}(table[i]->first) % newCapacity;
                for (int j = 0; j < newCapacity; ++j) {
                    int newIdx = probe(index, j);
                    if (!newIsOccupied[newIdx]) {
                        newTable[newIdx] = new std::pair<K, V>(table[i]->first, table[i]->second);
                        newIsOccupied[newIdx] = true;
                        break;
                    }
                }
            }
        }

        // Cleanup old table
        for (int i = 0; i < size; ++i) {
            delete table[i];
        }
        delete[] table;
        delete[] isOccupied;

        // Update to the new table and capacity
        table = newTable;
        isOccupied = newIsOccupied;
        size = newCapacity;
    }


public:
    HashTable(int initialSize = 10) : size(initialSize), count(0) {
        table = new std::pair<K, V>*[size];
        isOccupied = new bool[size]();

        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
            isOccupied[i] = false;
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            delete table[i];
        }
        delete[] table;
        delete[] isOccupied;
    }

    void insert(const K& key, const V& value) {
        if (static_cast<double>(count) / size >= 0.75) {
            resize();
        }

        int index = hash(key);
        for (int i = 0; i < size; ++i) {
            int newIdx = probe(index, i);
            if (!isOccupied[newIdx] || table[newIdx]->first == key) {
                if (!isOccupied[newIdx]) {
                    table[newIdx] = new std::pair<K, V>(key, value);
                    isOccupied[newIdx] = true;
                    count++;
                } else {
                    table[newIdx]->second = value;
                }
                return;
            }
        }
    }

    V* search(const K& key) {
        int index = hash(key);
        for (int i = 0; i < size; ++i) {
            int newIdx = probe(index, i);
            if (isOccupied[newIdx] && table[newIdx]->first == key) {
                return &table[newIdx]->second;
            }
            if (!isOccupied[newIdx]) {
                return nullptr;
            }
        }
        return nullptr;
    }


    void remove(const K& key) {
        int index = hash(key);
        for (int i = 0; i < size; ++i) {
            int newIdx = probe(index, i);
            if (!isOccupied[newIdx]) {
                return;
            }
            if (table[newIdx]->first == key) {
                delete table[newIdx];
                table[newIdx] = nullptr;
                isOccupied[newIdx] = false;
                count--;
                return;
            }
        }
    }

    bool empty() const {
        return count == 0;
    }
};

#endif //GITHUB_PARCIAL_AED_HASH_TABLE_OPEN_ADDRESSING_H
