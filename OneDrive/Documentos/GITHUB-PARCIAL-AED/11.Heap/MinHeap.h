#ifndef GITHUB_PARCIAL_AED_MINHEAP_H
#define GITHUB_PARCIAL_AED_MINHEAP_H

#include <iostream>
using namespace std;

template <typename T>
class MinHeap {
private:
    T* arr;
    int capacity;
    int size;

    void heapifyUp(int index) {
        if (index && arr[parent(index)] > arr[index]) {
            swap(arr[index], arr[parent(index)]);
            heapifyUp(parent(index));
        }
    }

    void heapifyDown(int index) {
        int left = leftChild(index);
        int right = rightChild(index);
        int smallest = index;

        if (left < size && arr[left] < arr[smallest])
            smallest = left;

        if (right < size && arr[right] < arr[smallest])
            smallest = right;

        if (smallest != index) {
            swap(arr[index], arr[smallest]);
            heapifyDown(smallest);
        }
    }

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    void resize() {
        int newCapacity = capacity * 2;
        T* newArray = new T[newCapacity];

        for (int i = 0; i < size; i++) {
            newArray[i] = arr[i];
        }

        delete[] arr;

        arr = newArray;
        capacity = newCapacity;
    }

public:
    MinHeap() {
        size = 0;
        capacity = 10;
        arr = new T[capacity];
    }

    ~MinHeap() {
        delete[] arr;
    }

    void insert(T key) {
        if (size == capacity) {
            resize();
        }

        size++;
        int index = size - 1;
        arr[index] = key;

        heapifyUp(index);
    }

    T extractMin() {
        if (size <= 0) {
            return T();
        }
        if (size == 1) {
            size--;
            return arr[0];
        }

        T root = arr[0];

        arr[0] = arr[size - 1];
        size--;

        heapifyDown(0);

        return root;
    }

    T getMin() {
        if (size <= 0) {
            return T();
        }
        return arr[0];
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

#endif //GITHUB_PARCIAL_AED_MINHEAP_H
