
#include<stdio.h>
#include<stdint.h>

int add(int a, int b)
{
	if(b==0)
		return a;
	else if(a==0)
		return b;
	
	int v1= a ^ b;
	int v2= (a & b) << 1;
	int v = add(v1, v2);
	printf("%d, %d, %d, %d, %d\n", a, b, v1, v2, v);
	return v;
}

int add1(int a, int b)
{
	int res=0;
	while(a  &&  b)
	{
		int v1= a ^ b;
		int v2= (a & b) << 1;
		a = v1;
		b = v2;
	}
	if(a==0)
		return b;
	else
		return a;
}

int add2(int a, int b)
{
	int res=0;
	while(b)
	{
		int v1= a ^ b;
		int v2= (a & b) << 1;
		a = v1;
		b = v2;
	}
	printf("%d\n", a);
	return a;
}


// 将a看成char数组首地址，b看做数组下标，a[b]元素的地址=a+sizeof(char)*b
int add3(int a, int b)
{
	char* v1=(char*)a;
	char* v2=&(v1[b]);
	int v3=(intptr_t)((void*)v2);
	return v3;
}


void solve()
{
	add(759, 674);
	
	int v=add1(759, 674);
	printf("add1 %d\n", v);
	
	add2(759, 674);
	
	v=add3(759, 674);
	printf("add3 %d\n", v);
}


int main()
{
	solve();
	
	return 0;
}