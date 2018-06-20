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
    bool isSymmetric(TreeNode* root) {
        // 层次遍历
       std::queue<TreeNode*> Q;
	   Q.push(root);
	   Q.push(root);
	   while(!Q.empty())
	   {
			TreeNode* t1=Q.front(); Q.pop();
			TreeNode* t2=Q.front(); Q.pop();
			
			if(t1==NULL  &&  t2==NULL)
				continue;
			else if(t1==NULL  ||  t2==NULL  ||  t1->val!=t2->val)
				return false;
			Q.push(t1->left);
			Q.push(t2->right);
			Q.push(t1->right);
			Q.push(t2->left);
	   }
	   return true;
    }
    bool isSymmetric(TreeNode* root) {
        // 层次遍历
        if(root==NULL)
        	return true;
       std::queue<TreeNode*> Q;
	   Q.push(root);
	   Q.push(root);
	   while(!Q.empty())
	   {
			TreeNode* t1=Q.front(); Q.pop();
			TreeNode* t2=Q.front(); Q.pop();
			
			if(t1->val!=t2->val)
				return false;
				
			if(t1->left!=NULL  &&  t2->right!=NULL)
			{
				Q.push(t1->left);
				Q.push(t2->right);
			}
			else if(t1->left!=NULL  ||  t2->right!=NULL)
				return false;
			
			if(t2->left!=NULL  &&  t1->right!=NULL)
			{
				Q.push(t2->left);
				Q.push(t1->right);
			}
			else if(t2->left!=NULL  ||  t1->right!=NULL)
				return false;
	   }
	   return true;
    }
    bool isSymmetric(TreeNode* root) {
    	if(root==NULL)
    		return true;
    	return isSymmetric(root->left, root->right);
    }
    bool isSymmetricHelper(TreeNode* t1, TreeNode* t2)
    {
    	if(t1==NULL  &&  t2==NULL)
    		return true;
    	if(t1==NULL  ||  t2==NULL  ||  t1->val!=t2->val)
    		return false;
    	if(isSymmetricHelper(t1->left, t2->right)  &&  isSymmetricHelper(t1->right, t2->left))
    		return true;
    	return false;
	}
};
