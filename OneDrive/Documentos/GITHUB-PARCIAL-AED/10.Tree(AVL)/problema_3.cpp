// https://leetcode.com/problems/convert-bst-to-greater-tree/description/?envType=problem-list-v2&envId=binary-search-tree

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
    int sum = 0;

public:
    TreeNode* convertBST(TreeNode* root) {
        reverseInOrder(root);
        return root;
    }

    void reverseInOrder(TreeNode* node) {
        if (!node) return;
        reverseInOrder(node->right);
        sum += node->val;
        node->val = sum;
        reverseInOrder(node->left);
    }
};
