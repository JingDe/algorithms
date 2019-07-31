
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 根据中序和后序构建二叉树
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
{
	return buildTree(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);	
}

TreeNode* buildTree(vector<int>& inorder, int s1, int e1, vector<int>& postorder, int s2, int e2) 
{
	//if(inorder.empty()  ||  postorder.empty()  || inorder.size()!=postorder.size())
	if(s1>e1  ||  s2>e2  ||  e1-s1!=e2-s2)
		return NULL;
	TreeNode* root=new TreeNode(postorder[e2]);
	std::vector<int>::iterator it = std::find(inorder.begin()+s1, inorder.begin()+e1+1, postorder[e2]);
	if(it==inorder.begin()+e1+1)
		return NULL;
	int leftNum=it-(inorder.begin()+s1);
	root->left=buildTree(inorder, s1, s1+leftNum-1, postorder, s2, s2+leftNum-1);
	root->right=buildTree(inorder, s1+leftNum+1, e1, postorder, s2+leftNum, e2-1);
	return root;
}

void test_find_interator()
{
	// 测试
	vector<int> iv({0, 0, 1, 3, 9});
	vector<int>::iterator it=std::find(iv.begin()+2, iv.end(), 3);
	if(it!=iv.end())
	{
		printf("%d\n", *it);
	}
	
	
	it=std::find(iv.begin()+2, iv.begin()+iv.size(), 3);
	if(it!=iv.begin()+iv.size())
	{
		printf("%d\n", *it);
	}
}

void test_end()
{
	vector<int> iv({0, 0, 1, 3, 9});
	if(v.end()==v.begin()+v.size())
		printf("equal\n");
	else
		printf("unequal\n");
}