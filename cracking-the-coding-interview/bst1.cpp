
struct Node {
    int data;
    Node *lchild, *rchild, *parent;
    Node(): lchild(NULL), rchild(NULL), parent(NULL) { }
};

class BST{
private:
	Node *root;
	
	Node* predecessor(Node* n); // 返回n节点的前驱节点：左孩子的maxNode；没有左孩子时，
	Node* successor(Node* n); 	// n节点的后继节点：右孩子的minNode；没有右孩子时，
	Node* minNode(Node* n); // 返回n为根节点的子树上的最小值节点：搜索到最后一个左孩子节点
	Node* maxNode(Node* n); //

public:
    BST();
	~BST();
	
    void Insert(int x); // 插入到何时的叶子节点位置
    void InorderTraver(); // 中序递归遍历
    Node* Find(int x); // 根据bst性质查找（非递归）
    void Remove(Node* z); // 删除：删除叶节点直接删除；
	// 删除节点只有一个孩子节点，使用孩子节点替换；
	// 删除节点有两个孩子，使用后继或者前驱节点替换，接着删除后继或者前驱节点
};



