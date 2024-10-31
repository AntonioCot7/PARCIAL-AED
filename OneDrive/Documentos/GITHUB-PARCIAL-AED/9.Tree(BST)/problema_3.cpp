// https://leetcode.com/problems/find-bottom-left-tree-value/description/?envType=problem-list-v2&envId=binary-tree


struct TreeNode {
    int val;TreeNode *left;TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
private:
    int maxDepth = -1;        // Profundidad máxima encontrada
    int bottomLeftValue = 0;  // Valor más a la izquierda en la última fila

    void findBottomLeftValueDFS(TreeNode* node, int depth) {
        if (!node) return;
        if (depth > maxDepth) {
            maxDepth = depth;
            bottomLeftValue = node->val;
        }
        findBottomLeftValueDFS(node->left, depth + 1);
        findBottomLeftValueDFS(node->right, depth + 1);
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        findBottomLeftValueDFS(root, 0);
        return bottomLeftValue;
    }
};