// https://leetcode.com/problems/evaluate-reverse-polish-notation/description/

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#define MAX_STACK_SIZE 100
using namespace std;

template <typename T>
struct element {
    T key;
};

template <typename T>
struct my_stack {
    int top;
    element<T> list[MAX_STACK_SIZE];
};

template <typename T>
void init_stack(my_stack<T>* s) {
    s->top = -1;
}

template <typename T>
int isfull(my_stack<T>* s) {
    return s->top >= MAX_STACK_SIZE - 1;
}

template <typename T>
int isempty(my_stack<T>* s) {
    return s->top == -1;
}

template <typename T>
void push(my_stack<T>* s, T key) {
    if (isfull(s)) {
        cout << "La pila esta llena" << endl;
    } else {
        s->top++;
        s->list[s->top].key = key;
    }
}

template <typename T>
void pop(my_stack<T>* s) {
    if (isempty(s)) {
        cout << "La pila esta vacia" << endl;
    } else {
        s->top--;
    }
}

template <typename T>
T top(my_stack<T>* s) {
    if (isempty(s)) {
        throw out_of_range("Pila vacía");
    } else {
        return s->list[s->top].key;
    }
}

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        my_stack<int> st;
        init_stack(&st);

        for (auto& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = top(&st);
                pop(&st);
                int a = top(&st);
                pop(&st);
                if (token == "+") {
                    push(&st, a + b);
                } else if (token == "-") {
                    push(&st, a - b);
                } else if (token == "*") {
                    push(&st, a * b);
                } else if (token == "/") {
                    push(&st, a / b);
                }
            } else {
                push(&st, stoi(token));
            }
        }
        return top(&st);
    }
};
