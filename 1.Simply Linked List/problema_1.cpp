// https://leetcode.com/problems/remove-linked-list-elements/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};



class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        while (head != nullptr) {
            if (head->val == val) {
                auto temp = head;
                head = head->next;
                delete temp;
            }
            else break;
        }

        if (head == nullptr) return head;

        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* current = head;
        while (current->next != nullptr) {
            if(val == current->next->val) {
                auto temp = current->next;
                auto next = temp->next;
                delete temp;
                current->next = next;
            }
            else current = current->next;
        }
        return dummy->next;
    }
};



