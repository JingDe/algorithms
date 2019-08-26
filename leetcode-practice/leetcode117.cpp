
Node* connect(Node* root) {
	if(root==NULL)
		return root;
	queue<Node*> Q;
	Q.push(root);
	root->next=NULL;
	
	Node* levelRightest=root;
	Node* latestVisited=root;
	Node* pre=NULL;
	
	while(!Q.empty())
	{
		Node* cur=Q.front();
		Q.pop();
		if(pre)
			pre->next=cur;
		pre=cur;
		
		if(cur->left)
		{
			Q.push(cur->left);
			latestVisited=cur->visited;
		}
		if(cur->right)
		{
			Q.push(cur->right);
			latestVisited=cur->right;
		}
		if(cur==levelRightest)
		{
			cur->next=NULL;
			pre=NULL;
			levelRightest=latestVisited;
		}		
	}
	return root;
}