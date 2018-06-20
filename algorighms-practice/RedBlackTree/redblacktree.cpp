

// 执行单旋转或双旋转
// 
RedBlackNode* RedBlackNode::rotate(const Comparable& item, RedBlackNode *theParent)
{
	if(item<theParent->element)
	{
		item<theParent->left->element ?  
					rotateWithLeftChild(theParent->left)  :
					rotateWithRightChild(theParent->left);
		return theParent->left;
	}
	else
	{
		item<theParent->right->element ? 
					rotateWithLeftChild(theParent->right) :
					rotateWithRightChild(theParent->right);
		return theParent->right;
	}
}

void insert(const Comparable& x)
{
	current=parent=grand=header;
	nullNode->element=x;
	
	while(current->element !=x)
	{
		great=grand;
		grand=parent;
		parent=current;		
		current=x<current->element ? current->left  :  current->right;
		
		if(curent->left->color==RED  &&  current->right->color==RED)
			handleReorient(x);
	}
	
	if(current!=nullNode)// 已存在x结点
		return;
	curent=new RedBlackNode(x, nullNode, nullNode);
	
	if(x<parent->element)
		parent->left=current;
	else
		parent->right=current;
	handleReorient(x);
}

// 处理两个红色子节点情形
void handleReorient(const Comparable& item)
{
	current->color=RED;
	current->left->color=BLACK;
	current->right->color=BLACK;
	
	if(parent->color==RED)
	{
		grand->color=RED;
		if(item<grand->element!=item<parent->element)
			parent=rotate(item, grand);//双旋转
		current=rotate(item, great);
		current->color=BLACK;
	}
	header->right->color=BLACK;//根结点涂黑色
}