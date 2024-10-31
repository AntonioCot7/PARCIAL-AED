// https://leetcode.com/problems/design-browser-history/description/

/**
* Your BrowserHistory object will be instantiated and called as such:
* BrowserHistory* obj = new BrowserHistory(homepage);
* obj->visit(url);
* string param_2 = obj->back(steps);
* string param_3 = obj->forward(steps);
*/

#include <iostream>
using namespace std;
struct Node{
    Node* next;
    Node* prev;
    string val;
    Node(string val):val(val),next(nullptr),prev(nullptr){};
};
class BrowserHistory {
    Node* current;
public:
    BrowserHistory(string homepage) {
        current = new Node(homepage);
    }
    void visit(string url) {
        auto forward = new Node(url);
        current->next = forward;
        forward->prev = current;
        current = current->next;
    }
    string back(int steps) {
        while(current->prev != nullptr && steps-- > 0 ){
            current = current->prev;
        }
        return current->val;
    }
    string forward(int steps) {
        int i = 0;
        while(current->next != nullptr && i++ < steps ){
            current = current->next;
        }
        return current->val;
    }
};
