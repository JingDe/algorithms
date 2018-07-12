
/*
并查集：

*/

#define SIZE 100
int ufsets[SIZE]; // 集合元素数组，父节点指针数组

void initial(int S[])
{
	for(int i=0; i<size; i++)
		S[i]=-1;
}

int find(int S[], int x)
{
	while(S[x]>=0) // 所有子树父节点指针为-1
		x=S[x];
	return x;
}

// 将子树root2挂到子树root1上
void union(int S[], int root1, int root2)
{
	S[root2]=root1;
}


