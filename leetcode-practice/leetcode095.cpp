
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


vector<TreeNode*> generateTrees(int n) 
{
	vector<TreeNode*> trees;
	
	bool visited[n+1];
	
	
	for(int i=1; i<=n; ++i)
	{
		meemset(visited, sizeof(visited), 0);
		
		visited[i]=true;
		helper(n, 1, &visited[0], trees);
	}
}

TreeNode* insertTree(TreeNode* root, int val)
{
	if(root==NULL)
	{
		root=new TreeNode(val);
		return root;
	}
	if(root->val>val)
		root->left=insertTree(root->left, val);
	else
		root->right=insertTree(root->right, val);
	return root;
}


void helper(int n, int inserted, bool* visited, vector<TreeNode*>& trees )
{
	if(
	for(int i=0; i<n; ++i)
	{
		if(visited)
	}
}

// 递归
vector<TreeNode*> generateTrees(int n) 
{
	if(n==0)
		return vector<TreeNode*>();
	return generate_helper(1, n);
}

vector<TreeNode*> generate_helper(int start, int end)
{
	vector<TreeNode*> trees;
	if(start>end)
		return trees;
	for(int rootIdx=start; rootIdx<end; ++rootIdx)
	{		
		vector<TreeNode*> leftTrees=generate_helper(start, rootIdx-1);
		vector<TreeNode*> rightTrees=generate_helper(rootIdx+1, end);
		
		for(int i=0; i<leftTrees.size(); ++i)
			for(int j=0; j<rightTrees.size(); ++j)
			{
				TreeNode* rootNode=new TreeNode(rootIdx);
				//connectTree(leftTrees[i], rootNode, rightTrees[j], trees);
				rootNode->left=leftTrees[i];
				rootNode->right=rightTrees[j];
				trees.push_back(rootNode);
			}
	}
	return trees;
}

void connectTree(TreeNode* left, TreeNode* root, TreeNode* right, vector<TreeNode*>& trees)
{
	root->left=left;
	root->right=right;
	trees.push_back(root);
}

