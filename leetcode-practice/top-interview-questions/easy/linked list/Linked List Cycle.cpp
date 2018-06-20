/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* left=head;
        ListNode* right=head;
        while(left!=NULL  &&  right!=NULL)
        {
        	left=left->next;
        	right=right->next;
        	if(right==NULL)
        		return false;
        	right=right->next;
        	if(left==right)
        		return true;
		}
		return false;
    }
};
