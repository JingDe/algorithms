#include<stdio.h>
#include<cstring>

const int maxn=100000+5;

int last, cur, next[maxn];
//cur表示光标位置：即当前光标位于s[cur]的右边
//last表示显示屏的最后一个字符是s[last]
//next[i]表示在当前显示屏中s[i]右边的字符编号

char s[maxn];//输入保存在s[1]，s[2]...中

int main()
{
	while(scanf("%s", s+1)==1)
	{
		int n= strlen(s+1);
		last=cur=0;
		next[0]=0;//next[0]表示显示屏中最左边的字符

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