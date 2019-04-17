#include<stdio.h>

void merge(int a[], int sz1, int b[], int sz2)
{
	int last=sz1+sz2-1;
	int i=0, j=0;
	for(i=sz1-1, j=sz2-1; i>=0  &&  j>=0; )
	{
		if(a[i]>b[j])
			a[last--]=a[i--];
		else
			a[last--]=b[j--];
	}
	while(j>=0)
		a[last--]=b[j--];
}

void print(int a[], int sz)
{
	for(int i=0;i<sz; i++)
		printf("%d, ", a[i]);
	printf("\n");
}

int main()
{
	{
		int a[12]={0,2,5,6};
		int b[6]={1,1,3,4,5,9};
		merge(a, 4, b, 6);
		print(a, 10);
	}
	return 0;
}