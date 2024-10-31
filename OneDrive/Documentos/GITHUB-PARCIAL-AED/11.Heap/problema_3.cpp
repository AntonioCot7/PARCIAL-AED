// https://leetcode.com/problems/maximum-score-from-removing-stones/description/

#include <iostream>
using namespace std;

template <typename T>
class MaxHeap {
private:
    T* arr;
    int capacity;
    int size;

    void heapifyUp(int index) {
        if (index && arr[parent(index)] < arr[index]) {
            swapValues(arr[index], arr[parent(index)]);
            heapifyUp(parent(index));
        }
    }

    void heapifyDown(int index) {
        int left = leftChild(index);
        int right = rightChild(index);
        int largest = index;

        if (left < size && arr[left] > arr[largest])
            largest = left;

        if (right < size && arr[right] > arr[largest])
            largest = right;

        if (largest != index) {
            swapValues(arr[index], arr[largest]);
            heapifyDown(largest);
        }
    }

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void swapValues(T& a, T& b) {
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
    MaxHeap() {
        size = 0;
        capacity = 10;
        arr = new T[capacity];
    }

    ~MaxHeap() {
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

    T extractMax() {
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

    T getMax() {
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

class Solution {
public:
    int maximumScore(int a, int b, int c) {
        MaxHeap<int> heap;

        heap.insert(a);
        heap.insert(b);
        heap.insert(c);

        int score = 0;

        while (true) {
            int first = heap.extractMax();
            int second = heap.extractMax();

            if (first == 0 || second == 0) {
                break;
            }

            first--;
            second--;
            score++;

            heap.insert(first);
            heap.insert(second);
        }

        return score;
    }
};