
BTNode* minimal(BTNode* n)
{
	if(n==NULL)
		return NULL;
	BTNode* res=n->left;
	while(res->next!=NULL)
		res=res->next;
	return res;
}

BTNode* successorInBST(BTNode* btn)
{
	if(btn==NULL)
		return NULL;
	if(btn->right!=NULL)
		return minimal(btn->right);
	BTNode* p=btn->parent;
	while(p  &&  p->right==btn)
	{
		btn=p;
		p=p->parent; //
	}
	return p;
}