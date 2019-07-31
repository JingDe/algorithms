
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};

Node* copyRandomList(Node* head) {
	Node* newList=NULL;
	
	map<Node*, Node*> old2new;
	Node* cur=head;
	Node* before=NULL;
	while(cur)
	{
		Node* node=new Node(cur->val, NULL, cur->random);
		old2new[cur]=node;
		if(before==NULL)
		{
			newList=node;
			before=node;
		}
		else
		{
			before->next=node;
			before=node;
		}
		cur=cur->next;
	}
	
	cur=newList;
	while(cur)
	{
		if(cur->random)
			cur->random=old2new[cur->random];
		cur=cur->next;
	}
	return newList;
}

Node* copyRandomList1(Node* head) {
	if(head==NULL)
		return NULL;
	
	map<Node*, Node*> old2new;
	Node* newList=new Node(head->val, NULL, NULL);	
	old2new[head]=newList;
	
	Node* curOld=head;	
	Node* curNew=newList;
	while(curOld)
	{
		curNew.random=getClonedNode(curOld->random, old2new);
		curNew.next=getClonedNode(curOld->next, old2new);
		
		curOld=curOld->next;
		curNew=curNew->next;
	}
	return newList;
	// return old2new[head];
}

Node* getClonedNode(Node* cur, map<Node*,Node*>& old2new)
{
	if(cur==NULL)
		return NULL;
	Node* copy=NULL;
	map<Node*,Node*>::iterator it=old2new.find(cur);
	if(it!=old2new.end())
	{
		copy=it->second;
	}
	else
	{
		copy=new Node(cur->val, NULL, NULL;
		old2new[cur]=copy;
	}
	return copy;
}

Node* copyRandomList2(Node* head) {
	if(head==NULL)
		return NULL;
	Node* oldNode=head;
	Node* newNode=NULL;
	while(oldNode)
	{
		newNode=new Node(oldNode->val, oldNode->next, NULL);
		oldNode->next=newNode;
		
		oldNode=newNode->next;
	}
	
	oldNode=head;
	while(oldNode)
	{
		newNode=oldNode->next;
		if(oldNode->random)
			newNode->random=oldNode->random->next;
		
		oldNode=newNode->next;
	}
	
	oldNode=head;
	// if(head==NULL)
		// return NULL;
	Node* newList=oldNode->next;
	newNode=oldNode->next;
	while(oldNode)
	{
		oldNode->next=oldNode->next->next;
		if(newNode->next!=NULL)
			newNode->next=newNode->next->next;
		
		oldNode=oldNode->next;
		newNode=newNode->next;
	}
	
	return newList;	
}


Node* copyRandomList3(Node* head) 
{
	map<Node*,Node*> old2new;
	return helper(head, old2new);
}

Node* helper(Node* cur, map<Node*,Node*>& old2new)
{
	if(cur==NULL)
		return NULL;
	map<Node*,Node*>::iterator it=old2new.find(cur);
	Node* newNode=NULL;
	if(it!=old2new.end())
		newNode=it->second;
	else
	{
		newNode=new Node(cur->val, NULL, NULL);
		old2new[cur]=newNode; // 必须在递归之前，记录cur已被访问过
		
		newNode->next=helper(cur->next, old2new);
		newNode->random=helper(cur->random, old2new);
	}      

	return newNode;
}

