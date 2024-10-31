#ifndef GITHUB_PARCIAL_AED_TREEAVL_H
#define GITHUB_PARCIAL_AED_TREEAVL_H

#include <iostream>
#include <algorithm>

#define MAX_SIZE 50000
#include <stdexcept>


template<typename T>
class Stack {
    T stack[MAX_SIZE];
    int top;
public:
    Stack() : top(-1) {}

    bool isfull() const {
        return top == MAX_SIZE - 1;
    }

    bool isempty() const {
        return top == -1;
    }

    T get_top() const {
        if (isempty()) {
            throw std::out_of_range("Stack is empty");
        }
        return stack[top];
    }

    void push(T e) {
        if (isfull()) {
            throw std::overflow_error("Stack overflow");
        }
        stack[++top] = e;
    }

    T pop() {
        if (isempty()) {
            throw std::underflow_error("Stack underflow");
        }
        return stack[top--];
    }
    int depth(const std::string& s) {
        Stack<char> stack;
        int current_depth = 0;
        int max = 0;

        for(auto c:s) {
            if(c == '(') {
                stack.push(c);
                current_depth+=1;
            }
            if(c == ')') {
                if(stack.get_top() == '(') {
                    stack.pop();
                    max =  current_depth >= max ? current_depth:max;
                    --current_depth;
                }
            }
        }

        return max;
    }
};


template <typename T>
struct Node {
    Node* next;
    T data;
    Node(T val):next(nullptr),data(val){};
};

template <typename T>
class Queue {
    Node<T>* front;
    Node<T>* rear;
public:
    Queue():front(nullptr),rear(nullptr){}
    ~Queue() {
        while (!isempty()) {
            dequeue();
        }
    }
    bool isempty() {
        return front==nullptr;
    }
    void enqueue(const T& val) {
        auto new_node = new Node(val);
        if(isempty()){
            front = rear = new_node;
        }
        else {
            rear->next = new_node;
            rear= new_node;
        }
    }
    T dequeue() {
        auto front_val = front->data;
        auto new_front = front->next;
        delete front;
        front = new_front;
        if(front == nullptr) rear = nullptr;
        return front_val;
    }
    T get_front() {
        return front->data;
    }
    T get_rear() {
        return rear->data;
    }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    int height = 0;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct AVLTree {
    TreeNode* root;

    int height(TreeNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(TreeNode* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    TreeNode* insert(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);

        if (val < node->val)
            node->left = insert(node->left, val);
        else if (val > node->val)
            node->right = insert(node->right, val);
        else
            return node;

        updateHeight(node);

        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && val < node->left->val)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && val > node->right->val)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && val > node->left->val) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && val < node->right->val) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    TreeNode* remove(TreeNode* node, int val) {
        if (!node) return nullptr;

        if (val < node->val)
            node->left = remove(node->left, val);
        else if (val > node->val)
            node->right = remove(node->right, val);
        else {
            if (!node->left || !node->right) {
                TreeNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;
                delete temp;
            } else {
                TreeNode* temp = findMin(node->right);
                node->val = temp->val;
                node->right = remove(node->right, temp->val);
            }
        }

        if (!node) return nullptr;

        updateHeight(node);

        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);

        // Left Right Case
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);

        // Right Left Case
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorderTraversal(TreeNode* node) {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->val << " ";
            inorderTraversal(node->right);
        }
    }

    void preorderTraversal(TreeNode* node) {
        if (node) {
            std::cout << node->val << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void postorderTraversal(TreeNode* node) {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->val << " ";
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    void remove(int val) {
        root = remove(root, val);
    }

    bool search(int val) {
        TreeNode* current = root;
        while (current) {
            if (val == current->val)
                return true;
            current = (val < current->val) ? current->left : current->right;
        }
        return false;
    }

    void inorder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void preorder() {
        preorderTraversal(root);
        std::cout << std::endl;
    }

    void postorder() {
        postorderTraversal(root);
        std::cout << std::endl;
    }

    void dfs() {
        if (!root) return;

        Stack<TreeNode*> stack;
        stack.push(root);

        while (!stack.isempty()) {
            TreeNode* node = stack.get_top();
            stack.pop();

            std::cout << node->val << " ";

            if (node->right)
                stack.push(node->right);
            if (node->left)
                stack.push(node->left);
        }
        std::cout << std::endl;
    }

    void bfs() {
        if (!root) return;

        Queue<TreeNode*> queue;
        queue.enqueue(root);

        while (!queue.isempty()) {
            TreeNode* node = queue.get_front();
            queue.dequeue();

            std::cout << node->val << " ";

            if (node->left)
                queue.enqueue(node->left);
            if (node->right)
                queue.enqueue(node->right);
        }
        std::cout << std::endl;
    }

    int getHeight() {
        return height(root);
    }

    bool isEmpty() {
        return root == nullptr;
    }

    void clear() {
        while (root)
            root = remove(root, root->val);
    }
};

#endif //GITHUB_PARCIAL_AED_TREEAVL_H
