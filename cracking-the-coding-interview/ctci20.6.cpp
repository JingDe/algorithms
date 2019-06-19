
// n个数中寻找最大的k个数，假定n个数都能装入内存
#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<functional>
#include<assert.h>


void print(const std::vector<int> &vec)
{
	for(int i=0; i<vec.size(); ++i)
		printf("%d ", vec[i]);
	printf("\n");
}

void debug_sort(std::vector<int> &vec)
{
	std::sort(vec.begin(), vec.end(), std::greater<int>());
}



// 排序法
std::vector<int> sort_solution(int arr[], int n, int k)
{
	std::sort(arr, arr+n, std::greater<int>());
	//debug_print(arr, n);
	
	// std::vector<int> res(k);
	// assert(res.size()==k);
	// for(int i=0; i<k; i++)
		// res.push_back(arr[i]);
	std::vector<int> res(arr, arr+k);
	
	return res;
}


// 最小堆
std::vector<int> heap_solution0(int arr[], int n, int k)
{	
	int sz=std::min(n, k);
	std::vector<int> minHeap(arr, arr+sz);
	if(k>n)
		return minHeap;
	
	// 默认创建大根堆，这里创建小根堆
	std::make_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
	for(int i=k; i<n; ++i)
	{
		if(arr[i]>minHeap.front())
		{
			std::pop_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
			minHeap.pop_back();
			minHeap.push_back(arr[i]);
			// minHeap.back()=arr[i];
			std::push_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
		}
	}
	
	return minHeap;
}

std::vector<int> heap_solution1(int arr[], int n, int k)
{	
	int sz=std::min(n, k);
	std::vector<int> minHeap(arr, arr+sz);
	if(k>n)
		return minHeap;
	
	// 默认创建大根堆，这里创建小根堆
	std::make_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
	for(int i=k; i<n; ++i)
	{
		if(arr[i]>minHeap.front())
		{
			std::pop_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
			minHeap.back()=arr[i];
			std::push_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
		}
	}
	
	return minHeap;
}

std::vector<int> heap_solution2(int arr[], int n, int k)
{	
	int sz=std::min(n, k);
	std::vector<int> minHeap(arr, arr+sz);
	if(k>n)
		return minHeap;
	
	// 默认创建大根堆，这里创建小根堆
	std::make_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
	for(int i=k; i<n; ++i)
	{
		if(arr[i]>minHeap.front())
		{
			minHeap.front()=arr[i];
			std::make_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
		}
	}
	
	return minHeap;
}


// extern int partition(int arr[], int start, int end);
// 交换指针方法
int partition_reverse(int arr[], int start, int end)
{	
	int pivot=arr[start];
	int saveStart=start;
	while(start<end)
	{
		while(start<end  &&  arr[end]<=pivot)
			--end;
		while(start<end  &&  arr[start]>=pivot)
			++start;
		if(start<end)
		{
			std::swap(arr[start], arr[end]);
		}
	}
	assert(start==end);
	std::swap(arr[saveStart], arr[start]);

	return end;
}


// 线性partition
std::vector<int> partition_solution1(int arr[], int n, int k)
{
	std::vector<int> res(k);
	int start=0, end=n-1;
	
	int idx=0;
	while(true)
	{
		idx=partition_reverse(arr, start, end);
		//printf("%d %d %d %d\n", start, end, idx, k);
		if(idx==k-1  ||  idx==k)
		{
			break;
		}
		else if(idx>k)
		{
			end=idx-1;
		}
		else // idx<k-1
		{
			start=idx+1;
		}
	}
	res.assign(arr, arr+k);
	return res;
}

// std::vector<int> partition_solution2(int arr[], int n, int k)
// {
	// std::vector<int> res(k);
	// int start=0, end=n-1;
	// int target=k;
	
	// int idx=0;
	// while(true)
	// {
		// idx=partition_reverse(arr, start, end);
		// if(idx-start==target-1  ||  idx-start==target)
		// {
			// break;
		// }
		// else if(idx-start>target)
		// {
			// end=idx-1;
		// }
		// else
		// {
			// start=idx+1;
			// target-=idx-start+1;
		// }
	// }
	// res.assign(arr, arr+k);
	// return res;
// }

void test_heap_solution()
{
	const int sz=100;
	const int k=22;
	
	int arr[sz];
	srand(time(NULL));
	for(int i=0; i<sz; ++i)
	{
		arr[i]=rand()%100;
	}
	std::vector<int> res=sort_solution(arr, sz, k);
	//debug_sort(res);
	print(res);
	
	res=heap_solution0(arr, sz, k);
	debug_sort(res);
	print(res);
	
	res=heap_solution1(arr, sz, k);
	debug_sort(res);
	print(res);
	
	res=heap_solution2(arr, sz, k);
	debug_sort(res);
	print(res);
	
	printf("partition_solution1\n");
	res=partition_solution1(arr, sz, k);
	debug_sort(res);
	print(res);
	
	printf("partition_solution2\n");
	// res=partition_solution2(arr, sz, k);
	// debug_sort(res);
	// print(res);
}

int main()
{

	
	test_heap_solution();
	
	return 0;
}


