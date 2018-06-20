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
        // BST树：
		// 结点的左子树所有结点都小于结点
		// 结点的右子树所有结点都大于结点
		// 左子树、右子树都是BST

		// 中根遍历是有序的
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
