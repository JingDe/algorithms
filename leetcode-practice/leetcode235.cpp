#include<stdio.h>
#include<vector>
#include<stack>

using std::stack;
using std::vector;


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

 
 void visit(const vector<int>& seq)
 {
	 for(int i=0; i<seq.size(); ++i)
		 printf("%d ", seq[i]);
	 printf("\n");
 }
 
// 普通二叉树的迭代先根遍历
void preTraverse2(TreeNode* root)
{
	//vector<int> seq;
	std::stack<TreeNode*> S;
	map<TreeNode*, int> visited; // 
	
	TreeNode* cur=root;
	while(cur!=NULL  ||  S.empty()==false)
	{
		while(cur)
		{
			//seq.push_back(cur->val);
            printf("%d ", cur->val);
			S.push(cur);
			cur=cur->left;
		}
		if(S.empty())
			continue;
		cur=S.top();
		if(cur->right  &&  visited[cur->right]==0) // 标示cur->right作为右儿子被访问过
		//if(cur->right  &&  visited.count(cur->right)==0)
		{
			cur=cur->right;
			visited[cur]=1;
		}
		else
		{
			S.pop();
            cur=NULL; // 注意!!
		}
	}
	//visit(seq);
}

void preTraverse_recur(TreeNode* root)
{
	//vector<int> seq;
	if(root==NULL)
		return;
	printf("%d ", root->val):
	preTraverse_recur(root->left);
	preTraverse_recur(root->right);
}

void preTraverse(TreeNode* root)
{
	vector<int> seq;
	std::stack<TreeNode*> S;
	map<TreeNode*, int> visited;
	
	TreeNode* cur=root;
	while(cur!=NULL  ||  S.empty()==false)
	{
		while(cur)
		{
			seq.push_back(cur->val);
			S.push(cur);
			cur=cur->left;
		}
		if(!S.empty())
		{
			cur=S.top();
			S.pop(); // 当某个节点的左子树和右子树都访问过，就从栈中弹出
			cur=cur->right;
		}
	}
	visit(seq);
}

// 模仿层次遍历：层次遍历的stack版本
void preTraverse3(TreeNode* root)
{
	if(root==NULL)
		return;
	
	stack<TreeNode*> S;
	S.push(root);
	TreeNode* cur=NULL;
	while(!S.empty())
	{
		cur=S.top();
		S.pop();
		printf("%d ", cur->val);
		
		if(cur->right)
			S.push(cur->right);
		if(cur->left)
			S.push(cur->left);
	}
	printf("\n");
}

//------------------------------------

// 普通二叉树的迭代中根遍历
void inTraverse1(TreeNode* root)
{
	std::stack<TreeNode*> S;
	map<TreeNode*, int> visited;

	TreeNode* cur=root;
	while(cur  ||  !S.empty())
	{
		if(cur)
		{
			S.push(cur);
			cur=cur->left;
		}
		else
		{
			cur=S.top();
			// 当cur没有右儿子或者第一次访问右儿子的时候，访问cur
			// 当cur的右儿子被访问过，弹出cur
			
			
			if(cur->right  &&  visited[cur->right]==0)
			{
				printf("%d ", cur->val);
				cur=cur->right;
				visited[cur]=1;
			}
			else if(cur->right==NULL)
            {                
				printf("%d ", cur->val);
                S.pop();
				cur=NULL;
            }
            else
			{
				S.pop();
				cur=NULL;
			}
		}
	}
	printf("\n");
}

void inTraverse_recur(TreeNode* root)
{
	if(root==NULL)
		return;
    inTraverse_recur(root->left);
	printf("%d ", root->val);
	inTraverse_recur(root->right);
}

void inTraverse(TreeNode* root)
{
	stack<TreeNode*> S;
	TreeNode* cur=root;
	while(cur  ||  !S.empty())
	{
		if(cur)
		{
			S.push(cur);
			cur=cur->left;
		}
		else
		{
			cur=S.top();
			S.pop();
			printf("%d ", cur->val);
			cur=cur->right;
		}
	}
	printf("\n");
}

// ------------------后序遍历的非递归解法
// 后序遍历，才需要visited等来存储某个节点的右儿子是否访问过
typedef struct _SNode SNode;
struct _SNode{
	TreeNode* p;
	int rvisited;
    _SNode()
    {}
    _SNode(TreeNode* a, int b)
    {
        p=a;
        rvisited=b;
    }
};

void postOrder(TreeNode* root)
{
	if(root==NULL)
		return;
	SNode sn;
	TreeNode* pt=root;
	std::stack<SNode> S;
	
	while(pt)
	{
		S.push(SNode(pt, 0));
		pt=pt->left;
	}
	
	while(!S.empty())
	{
		sn=S.top();
		if(sn.p->right==NULL  ||  sn.rvisited)
		{
			printf("%d ", sn.p->val);
			S.pop();
		}
		else
		{
			sn.rvisited=1;
			S.pop();
            S.push(sn);
			pt=sn.p->right;
			while(pt!=NULL)
			{
				S.push(SNode(pt, 0));
				pt=pt->left;
			}
		}
	}
	printf("\n");
}

void postOrder2(TreeNode* root)
{
	std::stack<TreeNode*> S;
	TreeNode* cur=root;
	TreeNode* r=NULL; // 辅助指针，指向最近访问过的节点
	while(cur  ||  !S.empty())
	{
		if(cur)
		{
			S.push(cur);
			cur=cur->left;
		}
		else
		{
			cur=S.top();
			if(cur->right  &&  cur->right!=r)
			{
				cur=cur->right;
				S.push(cur);
				cur=cur->left;
			}
			else // cur没有右儿子，或者cur的右儿子最近被弹出
			{
				S.pop();
				printf("%d ", cur->val);
				r=cur; // r指向最近被弹出的节点
				cur=NULL;
			}
		}
	}
	printf("\n");
}

// -----------------------------递归
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
	if(!root  ||  !p  ||  !q)
		return NULL;

	if(root->val<p->val  &&  root->val<q->val)
		return lowestCommonAncestor(root->right, p, q);
	else if(root->val>p->val  &&  root->val>q->val)
		return lowestCommonAncestor(root->left, p, q);
	else
		return root;
}

// 迭代
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if(!root  ||  !p  ||  !q)
		return NULL;
	TreeNode* cur=root;
	while(cur)
	{
		if(cur->val==p->val  ||  cur->val==q->val)
            break;
		if(p->val>=cur->val  &&  q->val>=cur->val)
			cur=cur->right;
		else if(p->val<=cur->val  &&  q->val<=cur->val)
			cur=cur->left;
		else
			break;
	}
	return cur;
}


 