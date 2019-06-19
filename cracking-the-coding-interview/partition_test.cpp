#include<stdio.h>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<assert.h>

// 划分arr[start, end]
// 1, 交换指针
// 2，挖坑
// 3，单向移动

void debug_print(int arr[], int n, int pivotPos)
{
	printf("partition 0-%d, pivot idx %d\n", n-1, pivotPos);
	for(int i=0; i<n; ++i)
	{
		if(i==pivotPos)
		{
			printf("[%d] ", arr[i]);
		}
		else
			printf("%d ", arr[i]);
	}
	printf("\n");
}

void debug_print(int arr[], int n)
{
	for(int i=0; i<n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// 交换指针方法
int partition_swap1(int array[], int start, int end, int n)
{
	// for debug
	int *arr=new int[n];
	for(int i=0; i<n; ++i)
		arr[i]=array[i];
	
	// srand(time(NULL));
	// int rndPos=rand() % (end-start+1) +start;
	// std::swap(arr[start], arr[rndPos]);
	// debug_print(arr, n);
	
	int pivot=arr[start];
	int saveStart=start;
	while(start<end)
	{
		while(start<end  &&  arr[end]>=pivot)
			--end;
		while(start<end  &&  arr[start]<=pivot)
			++start;
		if(start<end)
		{
			std::swap(arr[start], arr[end]);
		}
	}
	assert(start==end);
	std::swap(arr[saveStart], arr[start]);
	// for debug
	debug_print(arr, n, end);
	delete arr;
	return end;
}


// 挖坑方法
int partition_hole(int array[], int start, int end, int n)
{
	int *arr=new int[n];
	for(int i=0; i<n; ++i)
		arr[i]=array[i];
	
	int pivot=array[start];
	while(start<end)
	{
		while(start<end  &&  arr[end]>=pivot)
			--end;
		// if(start<end)
		arr[start]=arr[end];
		while(start<end  &&  arr[start]<=pivot)
			++start;
		// if(left<right)
		arr[end]=arr[start];
	}
	assert(start==end);
	arr[start]=pivot;
	
	debug_print(arr, n, end);
	delete arr;
	return start;
}

// 单向移动方法
int partition_move1(int array[], int start, int end, int n)
{
	int *arr=new int[n];
	for(int i=0; i<n; ++i)
		arr[i]=array[i];

	int pivot=arr[start];
	int left=start+1;
	int cur=start+1;
	while(cur<=end)
	{
		if(arr[cur]<pivot)
		{
			std::swap(arr[left], arr[cur]);
			++left;
		}
		++cur;
	}
	assert(arr[left]>=pivot);
	std::swap(arr[start], arr[left-1]);

	debug_print(arr, n, left-1);
	delete arr;
	return left-1;
}



int partition_move2(int array[], int start, int end, int n)
{
	int *arr=new int[n];
	for(int i=0; i<n; ++i)
		arr[i]=array[i];

	int pivot=arr[end];
	int left=start;
	int cur=start;
	while(cur<end)
	{
		if(arr[cur]<pivot)
		{
			std::swap(arr[left], arr[cur]);
			++left;
		}
		++cur;
	}
	std::swap(arr[left], arr[end]);

	debug_print(arr, n, left);
	delete arr;
	return left;
}

void test()
{
	const int sz=35;	
	int arr[sz];
	
	srand(time(NULL));
	for(int i=0; i<sz; ++i)
	{
		arr[i]=rand()%100;
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	partition_swap1(arr, 0, sz-1, sz);
	partition_hole(arr, 0, sz-1, sz);
	partition_move1(arr, 0, sz-1, sz);
	partition_move2(arr, 0, sz-1, sz);
}

int main()
{
	test();
	
	return 0;
}