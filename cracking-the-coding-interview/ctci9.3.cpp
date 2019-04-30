#include<iostream>
#include<stdlib.h>

using std::cout;
using std::endl;

void printCurrent(int a[], int left, int right)
{
	for(int i=left; i<=right; ++i)
		printf("%d ", a[i]);
	printf("\n");
}

void printCurrent(int a[], int sz, int left, int right)
{
	for(int i=0; i<left; ++i)
		printf("%d ", a[i]);
	printf("[");	
	for(int i=left; i<=right; ++i)
		printf("%d ", a[i]);
	printf("] ");
	for(int i=right+1; i<sz; ++i)
		printf("%d ", a[i]);
	printf("\n");
}

int binary_search(int a[], int sz, int num)
{
	int left=0, right=sz-1;
	int mid=0;
	while(left<=right)
	{
		printCurrent(a, sz, left, right);
		
		mid=left+(right-left)/2;
		if(a[mid]==num)
			return mid;
		if(a[left]<=a[mid])
		{
			//if(a[left]<=num  &&  num<=a[mid])
			if(a[left]<=num  &&  num<a[mid])
				right=mid-1;
			else
				left=mid+1;
		}
		else
		{
			//if(a[mid]<=num  &&  num<=a[left])
			if(a[mid]<num  &&  num<a[left])
				left=mid+1;
			else
				right=mid-1;
		}
	}
	return -1;
}

int main(){
    {
		int a[12] = {
			15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14
		};
		cout<<binary_search(a, 12, 3)<<endl;
	}
	{
		int b[19] = {
			2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,2,2,2,2
		};
		cout<<binary_search(b, 19, 3)<<endl;
	}
	getchar();
	system("pause");
    return 0;
}
