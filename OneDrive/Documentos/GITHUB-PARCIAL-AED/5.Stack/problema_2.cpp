// https://leetcode.com/problems/online-stock-span/description/

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


class StockSpanner {
private:
    my_stack<int> stack_prices;
    my_stack<int> stack_spans;
    int currentIndex;

public:
    StockSpanner() {
        init_stack(&stack_prices);
        init_stack(&stack_spans);
        currentIndex = 0;
    }

    int next(int price) {
        int span = 1;
        while (!isempty(&stack_prices) && top(&stack_prices) <= price) {
            pop(&stack_prices);
            pop(&stack_spans);
        }

        if (!isempty(&stack_spans)) {
            span = currentIndex - top(&stack_spans);
        } else {
            span = currentIndex + 1;
        }

        push(&stack_prices, price);
        push(&stack_spans, currentIndex);

        currentIndex++;
        return span;
    }
};