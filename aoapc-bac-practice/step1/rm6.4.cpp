#include<stdio.h>
#include<cstring>

const int maxn=100000+5;

int last, cur, next[maxn];
//cur��ʾ���λ�ã�����ǰ���λ��s[cur]���ұ�
//last��ʾ��ʾ�������һ���ַ���s[last]
//next[i]��ʾ�ڵ�ǰ��ʾ����s[i]�ұߵ��ַ����

char s[maxn];//���뱣����s[1]��s[2]...��

int main()
{
	while(scanf("%s", s+1)==1)
	{
		int n= strlen(s+1);
		last=cur=0;
		next[0]=0;//next[0]��ʾ��ʾ��������ߵ��ַ�

		for(int i=1; i<=n; i++)
		{
			char ch=s[i];
			if(ch=='[')		cur=0;
			if(ch==']')		cur=last;
			else
			{
				next[i]=next[cur];
				next[cur]=i;
				if(cur==last)	last=i;
				cur=i;
			}
		}
		for(i=next[0]; i!=0; i=next[i])
			printf("%d", s[i]);
		printf("\n");
	}
	return 0;
}