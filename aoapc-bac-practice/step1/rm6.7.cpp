#include<stdio.h>
using namespace std;


/*//指针实现
bool failed;

struct Node{
	bool have_value;
	int v;
	Node *left, *right;
	Node():have_value(false),left(NULL),right(NULL){}
};
Node* root;



Node* newnode() {  return new Node(); }

void remove_tree(Node* u)
{
	if(u==NULL)	return ;
	remove_tree(u->left);
	remove_tree(u->right);
	delete u;
}

void addnode(int v, char* s)
{
	int n=strlen(s);
	Node* u=root;
	for(int i=0; i<n; i++)
		if(s[i]=='L')
		{
			if(u->left==NULL)
				u->left=newnode();
			u=u->left;
		}
		else if(s[i]=='R')
		{
			if(u->right==NULL)
				u->right=newnode();
			u=u->right;
		}

	if(u->have_value)
		failed=true;
	u->v=v;
	u->have_value=true;
}




char s[maxn];
bool read_input()
{
	failed=false;
	remove_tree(root);
	root=newnode();
	while(true)
	{
		if(scanf("%s", s)!=1)	return false;
		if(!strcmp(s, "()"))	break;
		int v;
		sscanf(&s[1], "%d", &v);
		addnode(v, strchr(s, ',')+1);
	}
	return true;
}



bool bfs(vector<int>& ans)
{
	queue<Node*> q;
	ans.clear();
	q.push(root);
	while(!q.empty())
	{
		Node* u=q.front();  q.pop();
		if(!u->have_value)  return false;
		ans.push_back(u->v);
		if(u->left!=NULL)	q.push(u->left);
		if(u->right!=NULL)	q.push(u->right);
	}
	return true;
}
*/


//数组实现
bool failed;

const int NODE=256;
int left[NODE];
int right[NODE];
int value[NODE];
bool have_value[NODE];

const int root=1;

void newtree()
{
	left[root]=right[root]=0;
	have_value[root]=false;
	cnt=root;
}

int newnode() 
{
	int u=++cnt;
	left[u]=right[u]=0;
	have_value[root]=false;
	return u;
}

void remove_tree(int u)
{
	if(u==0)	return ;
	remove_tree(left[u]);
	remove_tree(right[u]);
	u=0;
}

void addnode(int v, char* s)
{
	int n=strlen(s);
	int u=root;
	for(int i=0; i<n; i++)
		if(s[i]=='L')
		{
			if(left[u]==0)
				left[u]=newnode();
			u=left[u];
		}
		else if(s[i]=='R')
		{
			if(right[u]==0)
				right[u]=newnode();
			u=right[u];
		}

	if(have_value[u])
		failed=true;
	value[u]=v;
	have_value[u]=true;
}




char s[maxn];
bool read_input()
{
	failed=false;
	remove_tree(root);
	root=newnode();
	while(true)
	{
		if(scanf("%s", s)!=1)	return false;
		if(!strcmp(s, "()"))	break;
		int v;
		sscanf(&s[1], "%d", &v);
		addnode(v, strchr(s, ',')+1);
	}
	return true;
}



bool bfs(vector<int>& ans)
{
	queue<int> q;
	ans.clear();
	q.push(root);
	while(!q.empty())
	{
		int u=q.front();  q.pop();
		if(!have_value[u])  return false;
		ans.push_back(v[u]);
		if(left[u]!=0)		q.push(left[u]);
		if(right[u]!=0)	q.push(right[u]);
	}
	return true;
}


//动态化静态
struct Node{
	bool have_value;
	int v;
	Node *left, *right;
};

Node* newnode()
{
	Node* u=&node[++cnt];
	u->left=u->right=NULL;
	u->have_value=false;
	return u;
}

//内存池:静态数组配合空闲列表
queue<Node*> freenodes;
Node node[maxn];
void init()
{
	for(int i=0; i<maxn; i++)
		freenodes.push(&node[i]);
}
Node* newnode()
{
	Node* u=freenodes.front();
	freenodes.pop();
	u->left=u->right=NULL;
	u->have_value=false;
	return u;
}
void deletenode(Node *u)
{
	freenodes.push(u);
}