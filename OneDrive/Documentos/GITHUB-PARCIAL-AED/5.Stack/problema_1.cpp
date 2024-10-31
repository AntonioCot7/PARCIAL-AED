// https://leetcode.com/problems/implement-queue-using-stacks/description/

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

#include <iostream>
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
        return T();
    } else {
        return s->list[s->top].key;
    }
}

class MyQueue {
private:
    my_stack<int> stack_in;
    my_stack<int> stack_out;

public:
    MyQueue() {
        init_stack(&stack_in);
        init_stack(&stack_out);
    }

    void push(int x) {
        ::push(&stack_in, x);
    }

    int pop() {
        if (isempty(&stack_out)) {
            while (!isempty(&stack_in)) {
                int temp = top(&stack_in);
                ::pop(&stack_in);
                ::push(&stack_out, temp);
            }
        }
        int front_val = top(&stack_out);
        ::pop(&stack_out);
        return front_val;
    }

    int peek() {
        if (isempty(&stack_out)) {
            while (!isempty(&stack_in)) {
                int temp = top(&stack_in);
                ::pop(&stack_in);
                ::push(&stack_out, temp);
            }
        }
        return top(&stack_out);
    }

    bool empty() {
        return isempty(&stack_in) && isempty(&stack_out);
    }
};
