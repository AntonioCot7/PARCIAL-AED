// https://leetcode.com/problems/swap-nodes-in-pairs/description/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr or head->next == nullptr) return head;
        auto left = head;
        auto right = left->next;
        auto next = right->next;
        right->next = left;
        head = right;
        left->next = swapPairs(next);
        return head;
    }
};
