// https://leetcode.com/problems/number-of-boomerangs/description/

#include <vector>
#include <utility>
#include <functional>
#include <stdexcept>
using namespace std;

// Función para calcular la distancia cuadrada entre dos puntos
int distanceSquared(const std::vector<int>& p1, const std::vector<int>& p2) {
    int dx = p1[0] - p2[0];
    int dy = p1[1] - p2[1];
    return dx * dx + dy * dy;
}

// Clase HashTable personalizada
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

    int count;
    int size;
    std::pair<K, V>** table;
    bool* isOccupied;
};

// Solución de LeetCode
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int totalBoomerangs = 0;

        for (int i = 0; i < points.size(); ++i) {
            HashTable<int, int> distanceCount(points.size());
            for (int j = 0; j < points.size(); ++j) {
                if (i == j) continue;
                int dist = distanceSquared(points[i], points[j]);
                int *count = distanceCount.search(dist); // retorna el valor
                if (count == nullptr) {
                    distanceCount.insert(dist, 1);
                } else {
                    *count += 1; // suma uno al valor
                }
            }

            for (int k = 0; k < distanceCount.size; ++k) {
                if (distanceCount.isOccupied[k]) {
                    int count = distanceCount.table[k]->second;
                    if (count > 1) {
                        totalBoomerangs += count * (count - 1);
                    }
                }
            }
        }
        return totalBoomerangs;
    }
};
