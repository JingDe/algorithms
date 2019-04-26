

// T2是否是T1的子树
bool isSubTree(BTNode* T1, BTNode* T2)
{
	if(!T1  ||  !T2)
		return false;
	BTNode* cur=T1;
	
	if(cur->data==T2->data)
	{
		if(sameTree(cur, T2))
			return true;
	}
	
	if(/* cur->left  &&   */isSubTree(cur->left, T2))
		return true;
	if(/* cur->right  &&   */isSubTree(cur->right, T2))
		return true;

	return false;
}

bool sameTree(BTNode* t1, BTNode* t2)
{
	if(t2==NULL)
		return true;
	if(t2->isLeaf()  &&  t2->data==t1->data)
		return true;
	if(sameTree(t1->left, t2->left)  &&  sameTree(t1->right, t2->right))
		return true;
	return false;
}


