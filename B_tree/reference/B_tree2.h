//B树的定义之一

struct Node  
{  
	bool isLeaf;             //是否是叶子节点  
	int keyNum;              //节点包含的关键字数量  
	T keyValue[KEY_MAX];     //关键字的值数组  
	Node *pChild[CHILD_MAX]; //子树指针数组  

	Node(bool b=true, int n=0)  
		:isLeaf(b), keyNum(n){}  
};  