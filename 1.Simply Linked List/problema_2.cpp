// https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

static int calcMcm_fact2(int a, int b) {
    int result;
    bool find = false;
    int greater = std::max(a,b);
    int point = greater;
    while(!find){
        if ((a % point) == 0 and (b % point) == 0) {
            find = true;
            result = point;
        }
        --point;
    }
    return result;
}

class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if (head == nullptr or head->next == nullptr) return head;
        auto dummy = head;
        auto left = head;
        while (left->next != nullptr) {
            auto right = left->next;
            auto multpl = new ListNode(calcMcm_fact2(left->val, right->val));
            left->next = multpl;
            multpl->next = right;
            left = left->next->next;
        }
        return dummy;
    }
};

