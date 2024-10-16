// https://leetcode.com/problems/linked-list-in-binary-tree/description/?envType=problem-list-v2&envId=binary-tree

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};



struct TreeNode {
int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        return dfs(head, head, root);
    }

    bool dfs(ListNode* head, ListNode* cur, TreeNode* root) {
        if (cur == nullptr) return true;
        if (root == nullptr) return false;

        if (cur->val == root->val) {
            cur = cur->next;
        } else if (head->val == root->val) {
            head = head->next;
        } else {
            cur = head;
        }

        return dfs(head, cur, root->left) || dfs(head, cur, root->right);
    }
};