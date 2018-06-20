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
    vector<vector<int>> levelOrder(TreeNode* root) {
        // 层次遍历
		std::queue<TreeNode*> Q;
		std::vector<vector<int> > result;
		if(root==NULL)
			return result;
			
		std::vector<int> level;
		TreeNode* rightest=root;
		TreeNode* latest=root;
		
		Q.push(root);
		while(!Q.empty()) 
		{
			TreeNode* cur=Q.front();
            Q.pop();
			level.push_back(cur->val);
			
			if(cur==rightest)
			{
				result.push_back(level);
				level.clear();
			}
			if(cur->left)
			{
                Q.push(cur->left);
				latest=cur->left;
			}
			if(cur->right)
			{
                Q.push(cur->right);
				latest=cur->right;
			}
			if(cur==rightest)
				rightest=latest; // rightest更新为cur的所有兄弟节点和自己的所有的孩子结点中最后访问的一个 
		}
		return result;
    }
};
