

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// BFS方法
Node* cloneGraph(Node* node) 
{
	if(node==NULL)
		return node;
	
	map<Node*, Node*> hash;
	Node* root=new Node(node->val, vector<Node*>());
	hash[node]=root;
	
	queue<Node*> Q;
	Q.push(node);
	while(!Q.empty())
	{
		Node* cur=Q.front();
		Q.pop();
		Node* copy=hash[cur];
		
		for(vector<Node*>::iterator it=cur->neighbors.begin(); it!=cur->neighbors.end(); ++it)
		{
			Node* neighbor=*it;
			if(!hash.contains(neighbor))
			{
				Node* neighborCopy=new Node(neighbor->val, vector<Node*>());
				hash[neighbor]=neighborCopy;
				
				Q.push(neighbor);
			}
			copy->neighbors.push_back(hash[neighbor]);
			
			//Q.push(neighbor);
		}
	}
	return root;
}