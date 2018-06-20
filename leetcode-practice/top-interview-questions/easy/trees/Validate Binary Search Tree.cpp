/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // BST����
		// �������������н�㶼С�ڽ��
		// �������������н�㶼���ڽ��
		// ������������������BST

		// �и������������
		if(root==NULL)
			return true;
		
		std::stack<TreeNode*> s;
        
        int before=INT_MIN;
        int tag=true;
        
        TreeNode* p=root;
        while(!s.empty()  ||  p!=NULL)
        {
        	while(p)
        	{
        		s.push(p);
        		p=p->left;
			}
			p=s.top();
            s.pop();
			
			if(before>p->val)
				return false;
            else if(before==p->val  &&  tag!=true)
                return false;
			before=p->val;
            tag=false;
			
			p=p->right;
		}
		return true;
	}
};
