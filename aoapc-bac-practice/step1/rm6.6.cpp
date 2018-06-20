#include<stdio.h>
#include<cstring>
const int maxd=20;//叶子深度D最大20
int s[1<<maxd];//结点数组，最大结点个数2^maxd-1

int main()
{
	int D, I;//叶子深度、小球个数I
	while(scanf("%d%d", &D, &I)==2)
	{
		memset(s, 0, sizeof(s));

		int k, n=(1<<D)-1;//n是最大结点编号
		for(int i=0; i<I; i++)
		{
			k=1;
			while(true)
			{
				s[k]=!s[k];
				k=s[k] ? k*2 : k*2+1;
				if(k>n)
					break;
			}
		}
		printf("%d\n", k/2);//最后一个小球
	}
	return 0;
}

/*
1、
每个小球都会落在根结点上，因此前两个小球必然是一个在左子树，
一个在右子树。一般地，只需看小球编号的奇偶性，
就能知道它是最终在哪棵子树中。
2、
对于那些落入根结点左子树的小球来说，只需知道该小球是第几个
落在根的左子树里的，就可以知道它下一步往左还是往右了。
依此类推，直到小球落到叶子上。
3、
如果使用题目中给出的编号I，则当I是奇数时，它是往左走的
第（I+1）/2个小球；当I是偶数时，它是往右走的第I/2个小球。
*/

/*
while(scanf("%d%d", &D, &I)==2)
{
	int k=1;
	for(int i=0; i < D-1; i++)
	{
		if(I%2)
		{
			k=k*2;  I=(I+1)/2;
		}
		else
		{
			k=k*2+1;  I /= 2;
		}
	}
	printf("%d\n", k);
}
*/