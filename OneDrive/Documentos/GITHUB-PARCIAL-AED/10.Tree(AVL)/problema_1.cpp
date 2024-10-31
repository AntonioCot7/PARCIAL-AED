// https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/?envType=problem-list-v2&envId=binary-search-tree

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    int minDiff = INT_MAX;
    TreeNode* prev = nullptr;

public:
    int getMinimumDifference(TreeNode* root) {
        inOrderTraversal(root);
        return minDiff;
    }

    void inOrderTraversal(TreeNode* node) {
        if (!node) return;
        inOrderTraversal(node->left);
        if (prev != nullptr) {
            minDiff = min(minDiff, node->val - prev->val);
        }
        prev = node;
        inOrderTraversal(node->right);
    }
};