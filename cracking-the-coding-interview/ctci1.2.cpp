#include<stdio.h>
#include<string.h>

void swap1(char& a, char& b)
{
	char temp=a;
	a=b;
	b=temp;
}

void swap2(char& a, char& b)
{
	a=a^b; // 异或
	b=b^a; // 
	a=a^b;
}

void solution()
{
	char str[]="abcd";
	int len=strlen(str);
	printf("%d\n", len);
	for(int i=0, j=len-1; i<j;)
	{
		swap2(str[i], str[j]);
		i++, j--;
	}
	printf("str=%s\n", str);
}

void solution1()
{
	char str[]="abcd";
	int len=strlen(str);
	printf("%d\n", len);
	for(int i=0; i<len/2; i++)
	{
		swap2(str[i], str[len-1-i]);
	}
	printf("str=%s\n", str);
}

void solution2(char* str)
{
	if(str==NULL)
		return;
	char *l=str, *r=str;
	while(*r)
		r++;
	r--;
	while(l<r)
		swap2(*(l++), *(r--));
	printf("str=%s\n", str);
}

int main()
{
	solution();
	solution1();
	
	char str[]="abcd";
	solution2(str);
	
	return 0;
}