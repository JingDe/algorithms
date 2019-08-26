
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
int sumNumbers(TreeNode* root) {
	if(root==NULL)
		return 0;
	int ans=0;
	vector<int> path;
	dfs(path, root, ans);
	return ans;
}

void dfs(vector<int> path, TreeNode* start, int& ans)
{        
	if(start==NULL)
	{
		int num=getNum(path);
		//printf("vec.size %d, num %d\n", path.size(), num);
		ans+=num;
		return;
	}
	
	path.push_back(start->val);
	if(start->left==NULL  &&  start->right==NULL)
	{
		int num=getNum(path);
		ans+=num;
		return;
	}
	if(start->left)
	{
		dfs(path, start->left, ans);
	}
	if(start->right)
	{
		dfs(path, start->right, ans);
	}
}

int getNum(const vector<int>& path)
{
	int res=0;
	for(int i=0; i<path.size(); ++i)
	{
		res=res*10+path[i];
	}
	return res;
}