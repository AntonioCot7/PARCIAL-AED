#ifndef GITHUB_PARCIAL_AED_STACK_H
#define GITHUB_PARCIAL_AED_STACK_H

#include <iostream>
#define MAX_STACK_SIZE 100
using namespace std;

template <typename T>
struct element {
    T key;
};

template <typename T>
struct stack {
    int top;
    element<T> list[MAX_STACK_SIZE];
};

template <typename T>
void init_stack(stack<T>* s) {
    s->top = -1;
}

template <typename T>
int isfull(stack<T>* s) {
    return s->top >= MAX_STACK_SIZE - 1;
}

template <typename T>
int isempty(stack<T>* s) {
    return s->top == -1;
}

template <typename T>
void push(stack<T>* s, T key) {
    if(isfull(s)) {
        cout << "La pila esta llena" << endl;
    }
    else {
        s->top++;
        s->list[s->top].key = key;
    }
}

template <typename T>
void pop(stack<T>* s) {
    if(isempty(s)) {
        cout << "La pila esta vacia" << endl;
    }
    else {
        s->top--;
    }
}

template <typename T>
T top(stack<T>* s) {
    if(isempty(s)) {
        return T();
    }
    else {
        return s->list[s->top].key;
    }
}

#endif //GITHUB_PARCIAL_AED_STACK_H
