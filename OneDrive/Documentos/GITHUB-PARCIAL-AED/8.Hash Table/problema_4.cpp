// https://leetcode.com/problems/bulls-and-cows/description/

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
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
    string getHint(string secret, string guess) {
        int bulls = 0, cows = 0;
        HashTable<char, int> secretTable(10); // Tabla hash para contar los caracteres en 'secret'
        HashTable<char, int> guessTable(10);  // Tabla hash para contar los caracteres en 'guess'

        // Paso 1: Contar los toros (bulls)
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) {
                bulls++;
            } else {
                // Contamos los caracteres no coincidentes en sus posiciones respectivas
                int* secretCount = secretTable.search(secret[i]);
                if (secretCount == nullptr) {
                    secretTable.insert(secret[i], 1);
                } else {
                    *secretCount += 1;
                }

                int* guessCount = guessTable.search(guess[i]);
                if (guessCount == nullptr) {
                    guessTable.insert(guess[i], 1);
                } else {
                    *guessCount += 1;
                }
            }
        }

        // Paso 2: Contar las vacas (cows)
        for (int i = 0; i < secretTable.size; ++i) {
            if (secretTable.isOccupied[i]) {
                char charSecret = secretTable.table[i]->first;
                int countInSecret = secretTable.table[i]->second;
                int* countInGuess = guessTable.search(charSecret);
                if (countInGuess != nullptr) {
                    cows += min(countInSecret, *countInGuess);
                }
            }
        }

        // Construimos el resultado final en el formato "xAyB"
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};
