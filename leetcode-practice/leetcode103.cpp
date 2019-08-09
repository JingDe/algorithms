
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<vector<int>> zigzagLevelOrder(TreeNode* root) 
{
	vector<vector<int> > res;
	if(root==NULL)
		return res;
	stack<int> S1, S2;
	S1.push(root);
	bool toRight=true; // 开始时从左往右
	vector<int> levelElems;
	while(!S1.empty()  ||  !S2.empty())
	{
		if(S1.empty())
		{
			res.push_back(levelElems);
			levelElems.clear();
			
			S1.swap(S2);
			toRight=!toRight;
		}
		
		TreeNode* cur=S1.top();
		S1.pop();
		levelElems.push_back(cur->val);
		
		if(toRight)
		{
			if(cur->left)
				S2.push(cur->left);
			if(cur->right)
				S2.push(cur->right);
		}
		else
		{
			if(cur->right)
				S2.push(cur->right);
			if(cur->left)
				S2.push(cur->left);
		}
	}
	if(!levelElems.empty())
		res.push_back(levelElems);
	return res;
}