#ifndef GITHUB_PARCIAL_AED_DOUBLY_LINKED_CIRCULAR_LIST_H
#define GITHUB_PARCIAL_AED_DOUBLY_LINKED_CIRCULAR_LIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class CircularDoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    CircularDoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~CircularDoublyLinkedList() {
        clear();
    }

    T front() {
        if (empty()) throw std::out_of_range("The list is empty");
        return head->data;
    }

    T back() {
        if (empty()) throw std::out_of_range("The list is empty");
        return tail->data;
    }

    void push_front(T val) {
        Node<T>* new_node = new Node<T>(val);
        if (empty()) {
            head = tail = new_node;
            head->next = head->prev = head;  // Circularidad
        } else {
            new_node->next = head;
            new_node->prev = tail;
            head->prev = new_node;
            tail->next = new_node;
            head = new_node;
        }
    }

    void push_back(T val) {
        Node<T>* new_node = new Node<T>(val);
        if (empty()) {
            head = tail = new_node;
            head->next = head->prev = head;  // Circularidad
        } else {
            new_node->next = head;
            new_node->prev = tail;
            tail->next = new_node;
            head->prev = new_node;
            tail = new_node;
        }
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("The list is empty");
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("The list is empty");
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = tail;
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            delete temp;
        }
    }

    void insert(int pos, T val) {
        if (pos < 0 || pos > size()) throw std::out_of_range("Invalid Position");

        if (pos == 0) {
            push_front(val);
            return;
        }
        if (pos == size()) {
            push_back(val);
            return;
        }

        Node<T>* new_node = new Node<T>(val);
        Node<T>* temp = head;

        for (int i = 0; i < pos - 1; ++i) {
            temp = temp->next;
        }

        new_node->next = temp->next;
        new_node->prev = temp;
        temp->next->prev = new_node;
        temp->next = new_node;
    }

    void remove(int pos) {
        if (pos < 0 || pos >= size()) throw std::out_of_range("Invalid Position");

        if (pos == 0) {
            pop_front();
            return;
        }
        if (pos == size() - 1) {
            pop_back();
            return;
        }

        Node<T>* temp = head;
        for (int i = 0; i < pos; ++i) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    T operator[](int pos) {
        if (pos < 0 || pos >= size()) throw std::out_of_range("Invalid Position");

        Node<T>* temp = head;
        for (int i = 0; i < pos; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        if (empty()) return 0;
        int count = 1;
        Node<T>* temp = head;
        while (temp->next != head) {
            ++count;
            temp = temp->next;
        }
        return count;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void reverse() {
        if (empty() || head == tail) return;

        Node<T>* current = head;
        Node<T>* temp = nullptr;

        do {
            temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        } while (current != head);

        temp = head;
        head = tail;
        tail = temp;
    }
};

#endif //GITHUB_PARCIAL_AED_DOUBLY_LINKED_CIRCULAR_LIST_H
