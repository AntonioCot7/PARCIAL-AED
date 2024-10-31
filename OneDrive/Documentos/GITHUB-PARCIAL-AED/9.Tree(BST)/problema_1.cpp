// https://leetcode.com/problems/symmetric-tree/description/?envType=problem-list-v2&envId=binary-tree


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

#include "iostream"
using namespace std;

bool isMirror(TreeNode* leftSubtre, TreeNode* rightSubtre) {
    if (!leftSubtre && !rightSubtre) return true;
    if (!leftSubtre || !rightSubtre) return false;
    return (leftSubtre->val == rightSubtre->val) && isMirror(leftSubtre->left, rightSubtre->right) && isMirror(leftSubtre->right, rightSubtre->left);
}

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isMirror(root->left, root->right);
    }
};
