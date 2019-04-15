

typedef struct node{
	int data;
	node *left, *right;
	int level;
	
	bool isLeaf()
	{
		return (left==NULL &&  right==NULL ) ? true : false;
	}
}BTNode;


class BTree{
private:
	BTNode* root;
	
public:
	
}

bool isBalanced(BTNode* root)
{
	// 层次遍历树，获得叶子节点高度
	int minHeight=INT_MAX, maxHeight=INT_MIN;
	std::queue<BTNode*> q;
	BTNode* node;
	if(root==NULL  ||  root->isLeaf())
		return true;
	root->level=1;
	q.push(root);
	while(q.empty()==false)
	{
		node=q.front();
		q.pop();
		
		if(node->left)
		{
			node->left->level=node->level+1;
			q.push(node->left);
			if(node->left->isLeaf())
			{
				if(node->left->level<minHeight)
					minHeight=node->left->level;
				else if(node->left->level>maxHeight)
					maxHeight=node->left->level;
			}
		}
		if(node->right)
		{
			node->right->level=node->level+1;
			q.push(node->right);
			if(node->right->isLeaf())
			{
				if(node->right->level<minHeight)
					minHeight=node->right->level;
				else if(node->right->level>maxHeight)
					maxHeight=node->right->level;
			}
		}
	}
	if(maxHeight-minHeight<=1)
		return true;
	return false;
}

void init()
{}


// ==============================
// 中序遍历，递归实现，求出从左到右的叶子节点到根节点的距离。
void getDepth(BTNode* root)
{
	
}


int main()
{
	return 0;
}