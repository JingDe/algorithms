
struct Node{
	Node* left, *right;
	int data;
	
	Node():data(0),left(NULL),right(NULL)
	{}
	Node(int d):data(d),left(NULL),right(NULL)
	{}
};

Node* fullCopy(Node* node)
{
	if(node==NULL)
		return NULL;
	Node* ret=new Node(node->data);
	ret->left=fullCopy(node->left);
	ret->right=fullCopy(node->right);
	return ret;
}

typedef map<Node*, Node*> NodeMap;
Node* copy_recursive(Node* cur, NodeMap &nodeMap)
{
	if(cur==NULL)
		return NULL;
	NodeMap::iterator it=nodeMap.find(cur);
	if(it!=nodeMap.end())
		return i->second;
	Node *node = new Node;
    nodeMap[cur] = node;
    node->ptr1 = copy_recursive(cur->ptr1, nodeMap);
    node->ptr2 = copy_recursive(cur->ptr2, nodeMap);
    return node;
}

Node* fullCopy2(Node* root){
    NodeMap nodeMap; // we will need an empty map
    return copy_recursive(root, nodeMap);
}

void init(Node* n)
{
	
}


int main()
{
	{
		Node* n1=NULL;
		init(n1);
		Node* n2=fullCopy(n1);
		print(n1);
		print(n2);
		free(n1);
		free(n2);
	}
	return 0;
}