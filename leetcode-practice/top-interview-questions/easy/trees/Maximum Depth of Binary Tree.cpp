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
    int maxDepth1(TreeNode* root) { // µÝ¹é 
        if(root==NULL)
        	return NULL;
        if(root->left==NULL)
        	return 1+maxDepth(root->right);
        if(root->right==NULL)
        	return 1+maxDepth(root->left);
        return 1+std::max(maxDepth(root->left), maxDepth(root->right));
    }
    int maxDepth1(TreeNode* root) {
    	// ²ã´Î±éÀú
    	if(root==NULL)
    		return 0;
    	
		std::queue<TreeNode*> que;
		
		que.push(root);
		int depth=0;
		TreeNode* rightest=root;
		TreeNode* recent=root;
		
		while(que.empty()==false)
		{
			TreeNode* cur=que.front();
			que.pop();
			
			if(cur->left)
			{
				que.push(cur->left);
				recent=cur->left;
			}
			if(cur->right)
			{
				que.push(cur->right);
				recent=cur->right;
			}
			if(cur==rightest)
			{				
				depth++;
				rightest=recent;			
			}
		}
		return depth;
    }
};
