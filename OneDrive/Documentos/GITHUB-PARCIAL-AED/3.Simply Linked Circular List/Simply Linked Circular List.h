#ifndef GITHUB_PARCIAL_AED_SIMPLY_LINKED_CIRCULAR_LIST_H
#define GITHUB_PARCIAL_AED_SIMPLY_LINKED_CIRCULAR_LIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class CircularSimplyLinkedList {
private:
    Node<T>* head;

public:
    CircularSimplyLinkedList() : head(nullptr) {}

    ~CircularSimplyLinkedList() {
        clear();
    }

    T front() {
        if (empty()) throw std::out_of_range("The list is empty");
        return head->data;
    }

    T back() {
        if (empty()) throw std::out_of_range("The list is empty");
        Node<T>* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        return temp->data;
    }

    void push_front(T val) {
        Node<T>* new_node = new Node<T>(val);
        if (empty()) {
            head = new_node;
            head->next = head;
        } else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            new_node->next = head;
            temp->next = new_node;
            head = new_node;
        }
    }

    void push_back(T val) {
        Node<T>* new_node = new Node<T>(val);
        if (empty()) {
            head = new_node;
            head->next = head;
        } else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->next = head;
        }
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("The list is empty");
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            Node<T>* front_node = head;
            head = head->next;
            temp->next = head;
            delete front_node;
        }
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("The list is empty");
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next->next != head) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = head;
        }
    }

    void insert(int pos, T val) {
        if (pos < 0 || pos > size()) throw std::out_of_range("Invalid Position");

        if (pos == 0) {
            push_front(val);
            return;
        }

        Node<T>* new_node = new Node<T>(val);
        Node<T>* temp = head;

        for (int i = 0; i < pos - 1; ++i) {
            temp = temp->next;
        }

        new_node->next = temp->next;
        temp->next = new_node;
    }

    void remove(int pos) {
        if (pos < 0 || pos >= size()) throw std::out_of_range("Invalid Position");

        if (pos == 0) {
            pop_front();
            return;
        }

        Node<T>* temp = head;
        for (int i = 0; i < pos - 1; ++i) {
            temp = temp->next;
        }

        Node<T>* to_delete = temp->next;
        temp->next = to_delete->next;
        delete to_delete;
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
        if (empty() || head->next == head) return;

        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        Node<T>* tail = head;

        do {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        } while (current != head);

        tail->next = prev;
        head = prev;
    }
};

#endif //GITHUB_PARCIAL_AED_SIMPLY_LINKED_CIRCULAR_LIST_H
