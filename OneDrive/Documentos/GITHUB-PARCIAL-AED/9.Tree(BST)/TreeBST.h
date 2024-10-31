#ifndef GITHUB_PARCIAL_AED_TREEBST_H
#define GITHUB_PARCIAL_AED_TREEBST_H

#include <iostream>
#include <algorithm>
#include <cmath>

template <typename T>
class BSTree {
    struct NodeBT {
        T data;
        NodeBT *left;
        NodeBT *right;
        NodeBT(const T& data): data(data), left(nullptr), right(nullptr) {}
    };
    NodeBT *root;

    bool find(NodeBT* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }
        if (value > node->data) {
            return find(node->right, value);
        }
        if (value < node->data) {
            return find(node->left, value);
        }
        return true;
    }

    void insert(NodeBT*& node, const T& value) {
        if (node == nullptr) {
            node = new NodeBT(value);
        } else if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        }
    }

    int height(NodeBT* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(height(node->left), height(node->right));
    }

    bool is_equilibrated(NodeBT* node) const {
        if (node == nullptr) {
            return true;
        }
        int left_height = height(node->left);
        int right_height = height(node->right);
        if (std::abs(left_height - right_height) <= 1 &&
            is_equilibrated(node->left) &&
            is_equilibrated(node->right)) {
            return true;
        }
        return false;
    }

    void inorder(NodeBT* node) const {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(NodeBT* node) const {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(NodeBT* node) const {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            std::cout << node->data << " ";
        }
    }

    NodeBT* remove(NodeBT*& node, const T& value) {
        if (node == nullptr) {
            return nullptr;
        }
        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr) {
                NodeBT* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                NodeBT* temp = node->left;
                delete node;
                return temp;
            }
            NodeBT* temp = find_min(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    NodeBT* find_min(NodeBT* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void clear(NodeBT* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BSTree() : root(nullptr) {}

    ~BSTree() {
        clear(root);
    }

    bool find(const T& value) const {
        return find(root, value);
    }

    void insert(const T& value) {
        insert(root, value);
    }

    bool is_equilibrated() const {
        return is_equilibrated(root);
    }

    void inorder() const {
        inorder(root);
        std::cout << std::endl;
    }

    void preorder() const {
        preorder(root);
        std::cout << std::endl;
    }

    void postorder() const {
        postorder(root);
        std::cout << std::endl;
    }

    void remove(const T& value) {
        root = remove(root, value);
    }


};

#endif //GITHUB_PARCIAL_AED_TREEBST_H
