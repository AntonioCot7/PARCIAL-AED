// https://leetcode.com/problems/repeated-dna-sequences/description/

#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <stdexcept>
using namespace std;

template <typename K, typename V>
class HashTable {
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

        for (int i = 0; i < size; ++i) {
            delete table[i];
        }
        delete[] table;
        delete[] isOccupied;

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

    int size;
    int count;
    std::pair<K, V>** table;
    bool* isOccupied;
};

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> result;
        if (s.size() < 10) return result;

        HashTable<string, int> hashTable(10);
        for (int i = 0; i <= s.size() - 10; ++i) {
            string sub = s.substr(i, 10); // Extraemos una subcadena de longitud 10
            int *count = hashTable.search(sub);
            if (count == nullptr) {
                hashTable.insert(sub, 1); // Primera vez que aparece la subcadena
            } else {
                if (*count == 1) { // Solo añadimos si es la segunda vez que aparece
                    result.push_back(sub);
                }
                *count += 1; // Incrementamos el conteo de esta subcadena
            }
        }

        return result;
    }
};
