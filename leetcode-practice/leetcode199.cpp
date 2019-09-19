

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

vector<int> rightSideView(TreeNode* root) {
	vector<int> ans;
	if(root==NULL)
		return ans;
	queue<TreeNode*> Q;
	Q.push(root);
	TreeNode* rightest=root;
	TreeNode* latest=root;
	while(!Q.empty())
	{
		TreeNode* tmp=Q.front();
		Q.pop();
		
		if(tmp==rightest)
			ans.push_back(tmp->val);
		
		if(tmp->left)
		{
			Q.push(tmp->left);
			latest=tmp->left;
		}
		if(tmp->right)
		{
			Q.push(tmp->right);
			latest=tmp->right;
		}
		
		if(tmp==rightest)
			rightest=latest;
	}
	return ans;
}

//DFS方法
vector<int> rightSideView(TreeNode* root) 
{
	map<int, int> rightmostValueAtDepth;
	int max_depth=-1;
	
	stack<TreeNode*> nodeStack;
	stack<int> depthStack;
	nodeStack.push(root);
	depthStack.push(0);
	
	while(!nodeStack.empty())
	{
		TreeNode* node=nodeStack.top();
		nodeStack.pop();
		int depth=depthStack.top();
		depthStack.pop();
		
		if(node)
		{
			max_depth=std::max(max_depth, depth);
			
			if(!rightmostValueAtDepth.count(depth))
				rightmostValueAtDepth[depth]=node->val;
			
			nodeStack.push(node->left);
			nodeStack.push(node->right);
			depthStack.push(depth+1);
			depthStack.push(depth+1);
		}
	}
	
	vector<int> rightView;
	for(int depth=0; depth<=max_depth; depth++)
		rightView.push_back(rightmostValueAtDepth[depth]);
	return rightView;
}

vector<int> rightSideView(TreeNode* root) 
{
	map<int, int> rightmostValueAtDepth;
	int max_depth=-1;
	
	queue<TreeNode*> nodeQueue;
	queue<int> depthQueue;
	nodeQueue.push(root);
	depthQueue.push(0);
	
	while(!nodeQueue.empty())
	{
		TreeNode* node=nodeQueue.front();
		int depth=depthQueue.front();
		nodeQueue.pop();
		depthQueue.pop();
		
		if(node!=NULL)
		{
			max_depth=std::max(max_depth, depth);
			
			rightmostValueAtDepth[depth]=node->val; // 最右节点是该深度最后访问的节点
			
			nodeQueue.push(node->left);
			nodeQueue.push(node->right);
			depthQueue.push(depth+1);
			depthQueue.push(depth+1);
		}
	}
	vector<int> rightView;
	for(int depth=0; depth<=max_depth; depth++)
		rightView.push_back(rightmostValueAtDepth[depth]);
	return rightView;
}