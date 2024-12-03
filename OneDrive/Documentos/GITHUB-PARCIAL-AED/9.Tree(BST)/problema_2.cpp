// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/?envType=problem-list-v2&envId=binary-tree

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"
using namespace std;

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        queue<TreeNode*> q;
        q.push(root);
        bool zigzag = false;
        while (!q.empty()) {
            int size = q.size();
            vector<int> currentLevel;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                currentLevel.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            if (zigzag) {
                reverse(currentLevel.begin(), currentLevel.end());
            }
            result.push_back(currentLevel);
            zigzag = !zigzag;
        }
        return result;
    }
};