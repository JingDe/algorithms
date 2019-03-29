
template<typename Comparable>
class RedBlackTree
{
public:
	explicit RedBlackTree(const Comparable& negInf);
	RedBlackTree(const RedBlackTree& rhs);
	~RedBlackTree();
	
	const Comparable& findMin() const;
	const Comparable& findMax() const;
	bool contains(const Comparable& x) const;
	bool isEmpty() const;
	void printTree() const;
	
	void makeEmpty();
	void insert(const Comparable& x);
	void remove(const Comparable& x);
	
	enum{RED, BLACK};
	
	const RedBlackTree& operator=(const RedBlackTree& rhs);
	
private:
	struct RedBlackNode
	{
		Comparable element;
		RedBlackNode* left;
		RedBlackNode* right;
		int color;
		
		RedBlackNode(const Comparable& theElement=Comparable(), RedBlackNode *lt=NULL, RedBlackNode *rt=NULL, int c=BLACK)
			:element(theElement), left(lt), right(rt), color(c){}
	};
	
	// 插入函数使用
	RedBlackNode *current;
	RedBlackNode *parent;
	RedBlackNode *grand;
	RedBlackNode *great;
	
	void reclaimMemory(RedBlackNode *t);
	void printTree(RedBlackNode *t) const;
	
	RedBlackNode *clone(RedBlackNode* t) const;
	
	//
	void handleReorient(const Comparable& item);
	RedBlackNode* rotate(const Comparable& item, RedBlackNode *theParent);
	void rotateWithLeftChild(RedBlackNode *&k2);
	void rotateWithRightChild(RedBlackNode *&k1);
};

void RedBlackTree::printTree() const
{
	if(header->right==nullNode)
		cout<<"Empty tree"<<std::endl;
	else
		printTree(header->right);
		// header节点的right指向真正的红黑树根节点
}

void RedBlackTree::printTree(RedBlackNode *t) const
{
	if(t!=t->left)
	{
		printTree(t->left);
		cout<<t->element<<std::endl;
		printTree(t->right);
	}
}

const RedBlackTree& RedBlackTree::operator=(const RedBlackTree& rhs)
{
	if(this!=&rhs)
	{
		makeEmpty();
		header->right=clone(rhs.header->right);
	}
}

RedBlackNode* RedBlackTree::clone(RedBlackNode *t) const
{
	if(t==t->left)// 不能t==nullNode
		return nullNode;
	else
		return new RedBlackNode(t->element, clone(t->left), clone(t->right), t->color);
}

RedBlackTree::RedBlackTree(const Comparable& negInf)// 小于等于所有其他值
{
	nullNode=new RedBlackNode;
	nullNode->left=nullNode->right=nullNode;
	header=new RedBlackNode(negInf);
	header->left=header->right=nullNode;
	// 构造一个空树。header节点，left和right都指向nullNode。nullNode节点指向自身的空节点。
}


// 执行单旋转或者双旋转
// 被handleReorient调用
// item是handleReorient的item
// theParent是被旋转字数的跟的父节点
// 返回旋转字数的根节点

// 执行单旋转
// theParent是item所在节点的祖父节点
RedBlackNode* RedBlackNode::rotate(const Comparable& item, RedBlackNode *theParent)
{
	// item是theParent的左子树上
	if(item<theParent->element)
	{
		item<theParent->left->element ?  
					rotateWithLeftChild(theParent->left)  : // LL 一次右旋转
					rotateWithRightChild(theParent->left); // LR 先左后右旋转
		return theParent->left; // 无论一次旋转，两次旋转，都以theParent->left为支点，theParent->left旋转后成为子树根
	}
	else // item是theParent的右子树上
	{
		item<theParent->right->element ? 
					rotateWithLeftChild(theParent->right) : // RL
					rotateWithRightChild(theParent->right); // RR
		return theParent->right;
	}
}

// k2和左儿子一起旋转，
void RedBlackTree::rotateWithLeftChild(RedBlackNode* &k2)
{
	RedBlackNode *k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	k2=k1;
}

void RedBlackTree::rotateWithRightChild(RedBlackNode* &k1)
{
	RedBlackNode* k2=k1->right;
	k1->
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
// 插入过程中，如果一个节点有两个红色子节点时
// 执行变色和旋转，item是被插入的值
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