
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};


Node* connect(Node* root) {
	if(root==NULL)
		return root;
	std::queue<Node*> Q;
	Q.push(root);
	Node* levelFirst=root;
	Node* before=NULL;
	Node* latestChild=NULL;
	while(!Q.empty())
	{
		Node* node=Q.front();
		Q.pop();
		
		node->next=before;
		before=node;
				
		if(node->right)
		{
			Q.push(node->right);
			latestChild=node->right;
		}
		if(node->left)
		{
			Q.push(node->left);
			latestChild=node->left;
		}
		
		if(node==levelFirst)
		{
			levelFirst==latestChild;
			before=NULL;
		}
	}
	return root;
}

// 基本的层次遍历
void levelTraverse(TreeNode* root)
{
	if(root==NULL)
		return;
	std::queue<TreeNode*> Q;
	while(!Q.empty())
	{
		TreeNode* node=Q.front();
		Q.pop_front();
		
		visit(node);
		
		if(node->left)
			Q.push(node->left);
		if(node->right)
			Q.push(node->right);
	}
}


// 解法二：
// 完美二叉树, pre指向每一层第一个节点，cur层次遍历
Node* connect(Node* root)
{
	if(root==NULL)
		return;
	Node* pre=root;
	Node* cur=NULL;
	while(pre->left)
	{
		cur=pre;
		while(cur)
		{
			cur->left->next=cur->right;
			if(cur->next)
				cur->right->next=cur->next->left;
			cur=cur->next;
		}
		pre=pre->left;
	}
	return root;
}