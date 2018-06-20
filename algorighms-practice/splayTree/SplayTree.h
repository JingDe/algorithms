

template<typename Comparable>
class SplayTree{
public:
	SplayTree()
	{
		nullNode=new BinaryNode;
		nullNode->left=nullNode->right=nullNode;
		root=nullNode;
	}
	
	~SplayTree()
	{
		makeEmpty();
		delete nullNode;
	}
	
	SplayTree(const SplayTree& rhs);
	const SplayTree& operator=(const SplayTree& rhs);
	
	void insert(const Comparable& x);
	void remove(const Comparable& x);

private:
	struct BinaryNode{};// 二叉查找树结点
	
	BinaryNode *root;
	BinaryNode *nullNode;
	
	void rotateWithLeftChild(BinaryNode* &k2);
	void rotateWithRightChild(BinaryNode* &k1);
	void splay(const Comparable& x, BinaryNode* &t);//自顶向下伸展过程
};

// 自顶向下伸展方法：围绕x伸展t
// t是中间的树的根结点
// x是查找的值
void SplayTree::splay(const Comparable& x, BinaryNode* &t)
{
	BinaryNode *leftTreeMax, *rightTreeMin;
	static BinaryNode header;
	
	header.left=header.right=nullNode;
	leftTreeMax=rightTreeMin=&header;
	
	nullNode->element=x;
	
	for(; ;)
	{
		if(x<t->element)
		{
			if(x<t->left->element)
				rotateWithLeftChild(t);
			if(t->left==nullNode)
				break;
			
			rightTreeMin->left=t;
			rightTreeMin=t;
			t=t->left;
		}
		else if(t->element<x)
		{
			if(t->right->element<x)
				rotateWithRightChild(t);
			if(t->right==nullNode)
				break;
			
			leftTreeMax->right=t;
			leftTreeMax=t;
			t=t->right;
		}
		else
			break;
	}
	// 整理	
	leftTreeMax->right=t->left;
	rightTreeMin->left=t->right;
	t->left=header.right;
	t->right=header.left;
}

// 插入一个值x
void SplayTree::insert(const Comparable& x)
{
	static BinaryNode *newNode=NULL;
	
	if(newNode==NULL)
		newNode=new BinaryNode;
	newNode->element=x;
	
	if(root==nullNode)
	{//建立一棵单结点树
		newNode->left=newNode->right=nullNode;
		root=newNode;
	}
	else
	{		
		splay(x, root);// 将x从root自顶向下伸展，围绕x伸展root
		if(x<root->element)//新根数据大于x
		{
			newNode->left=root->left;
			newNode->right=root;
			root->left=nullNode;
			root=newNode;//newNode称为新的根
		}
		else if(root->element<x)
		{
			newNode->left=root;
			newNode->right=root->right;
			root->right=nullNode;
			root=newNode;
		}
		else//新根的数据等于x，重复元素不插入
			return;
	}
	newNode=NULL;
}

void SplayTree::remove(const Comparable& x)
{
	BinaryNode *newTree;
	
	splay(x, root);
	if(root->element!=x)
		return;
	
	if(root->left==nullNode)
		newTree=root->right;
	else
	{
		newTree=root->left;
		splay(x, newTree);
		newTree->right=root->right;
	}
	delete root;
	root=newTree;
}

void SplayTree::makeEmpty()
{
	while(!isEmpty())
	{
		findMax();
		remove(root->element);
	}
}