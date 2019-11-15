
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {        
	if(!root  ||  !p  ||  !q)
		return NULL;
	std::stack<TreeNode*> sp;
	std::stack<TreeNode*> sq;
	postTraverseToNode(root, p, sp);
	printf("\n==\n");
	postTraverseToNode(root, q, sq);
	while(sp.size()>sq.size())
		sp.pop();
	while(sq.size()>sp.size())
		sq.pop();

	while(sq.empty()==false  &&  sp.empty()==false)
	{
		TreeNode* a=sp.top();
		TreeNode* b=sq.top();
		if(a==b)
			return a;
		sp.pop();
		sq.pop();
	}
	assert(false);
	return NULL;
}

// 后序遍历，方法一：使用r记录最近访问的节点
void postTraverseToNode(TreeNode* root, TreeNode* p, std::stack<TreeNode*>& path)
{
	if(!root  ||  !p)
		return ;
	std::stack<TreeNode*>& S=path; // ??
	TreeNode* cur=root;
	TreeNode* r=NULL;
	
	while(cur)
	{
		S.push(cur);
		if(cur==path)
			return;
		cur=cur->left;
	}
	
	while(!S.empty())
	{
		cur=S.top();
		if(cur->right==NULL   ||  cur->right==r)
		{
			// printf("%d ", cur->val);
			if(cur==p)
				return;
			S.pop();
			r=cur;
		}
		else
		{
			cur=cur->right;
			while(cur)
			{
				S.push(cur);
				cur=cur->left;
			}
		}
	}
	// printf("\n");
}

void postTraverseToNode(TreeNode* root, TreeNode* p, std::stack<TreeNode*>& path)
{
	if(!root  ||  !p)
		return ;
	std::stack<TreeNode*>& S=path; 
	TreeNode* cur=root;
	TreeNode* r=NULL;
	
	while(cur  ||  !S.empty())
	{
		if(cur)
		{
			S.push(cur);
			if(cur==p)
				return;
			cur=cur->left;
		}
		else
		{
			cur=S.top();
			if(cur->right==NULL   ||  cur->right==r)
			{
				printf("%d ", cur->val);
				if(cur==p)
					return;
				S.pop();
				r=cur;
				cur=NULL; // cur如果不置为NULL，会重复压入cur的左子树
			}
			else
			{
				cur=cur->right;
				S.push(cur);
				cur=cur->left;
			}
		}
	}
}

// 方法二：栈元素 记录某节点的右儿子是否被访问过的信息
typedef struct _SNode SNode;
struct _SNode{
	TreeNode* p;
	int rvisited;
    _SNode()
    {
        p=NULL;
        rvisited=0;
    }
    _SNode(TreeNode* a, int b)
    {
        p=a;
        rvisited=b;
    }
};

void postTraverseToNode(TreeNode* root, TreeNode* p, std::stack<TreeNode*>& path)
{
	if(!root  ||  !p)
		return;
	
	std::stack<SNode> S;
	TreeNode* cur=root;
	SNode sn;
	while(cur)
	{
		S.push(SNode(cur, 0));
		path.push(cur);
		if(cur==p)
			return;
		cur=cur->left;
	}
	
	while(!S.empty())
	{
		sn=S.top();
		if(sn.p->right==NULL  ||  sn.rvisited==1)
		{
			printf("%d ", sn.p->val);
			if(sn.p==p)
				return;
			S.pop();
			path.pop();
		}
		else
		{
			sn.rvisited=1;
			S.pop();
			S.push(sn);
			cur=sn.p->right;
			while(cur)
			{
				S.push(SNode(cur, 0));
				path.push(cur);
				if(cur==p)
					return ;
				cur=cur->left;
			}
		}
	}
	printf("\n");
}