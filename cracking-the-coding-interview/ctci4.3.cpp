
BTNode* getBinaryTree(int a[], int start, int end)
{
	if(start>end)
		return NULL;
	if(start==end)
	{
		BTNode* n=new BTNode(a[start], NULL, NULL);
		return n;
	}
	int middle=start+(end-start)/2;
	BTNode* n=new BTNode(a[middle]);
	n->left=getBinaryTree(a, start, middle-1);
	n->right=getBinaryTree(a, middle+1, end);
	return n;
}


BTNode* getBinaryTree2(int a[], int start, int end, BTNode* parent)
{
	if(start>end)
		return NULL;
	if(start==end)
	{
		BTNode* n=new BTNode(a[start], parent, NULL, NULL);
		return n;
	}
	int middle=start+(end-start)/2;
	BTNode* n=new BTNode(a[middle]);
	n->left=getBinaryTree2(a, start, middle-1, n);
	n->right=getBinaryTree2(a, middle+1, end, n);
	return n;
}

