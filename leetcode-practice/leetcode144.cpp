
vector<int> preorderTraversal_1(TreeNode* root) {
	vector<int> order;
	helper(root, order);
	return order;
}

void helper(TreeNode* root, vector<int>& order)
{
	if(root==NULL)
		return;
	order.push_back(root->val);
	helper(root->left, order);
	helper(root->right, order);
}



vector<int> preorderTraversal_2(TreeNode* root) 
{
	vector<int> order;
	stack<TreeNode*> s;
	TreeNode* cur=root;
	while(cur  ||  !s.empty())
	{
		while(cur)
		{
			order.push_back(cur->val);
			s.push(cur);
			cur=cur->left;
		}
		while(!s.empty())
		{
			cur=s.top();
			s.pop();
			cur=cur->right;
			if(cur)
			{
				break;
			}
		}
	}
	return order;
}


vector<int> preorderTraversal_2(TreeNode* root) 
{
	vector<int> order;
	stack<TreeNode*> s;
	TreeNode* cur=root;
	while(cur  ||  !s.empty())
	{
		while(cur)
		{
			order.push_back(cur->val);
			s.push(cur);
			cur=cur->left;
		}
		if(!s.empty())
		{
			cur=s.top();
			s.pop();
			cur=cur->right;
		}
	}
	return order;
}