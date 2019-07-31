#include<stdio.h>
#include<vector>
#include<algorithm> 

using std::vector;

void printVec(vector<int>& v)
{
	for(int i=0; i<v.size(); ++i)
		printf("%d ", v[i]);
	printf("\n");
}

// wrong
/* void nextPermutation(vector<int>& nums) 
{
	if(nums.empty())
		return;
	
	int sz=nums.size();
	int p=sz-1;
	while(p>0 &&  nums[p]<=nums[p-1])
	{
		--p;
	}
	printf("%d\n", p);
	if(p==0)
	{
		for(int i=0; i<sz/2; ++i)
			std::swap(nums[i], nums[sz-1-i]);
	}
	else
	{
		int changePos=p-1;
		int saveNum=nums[changePos];
		nums[changePos]=nums[sz-1];
		
		for(p=sz-2; p>changePos; --p)
		{
			nums[p+1]=nums[p];
		}
		nums[changePos+1]=saveNum;
	}
	
} */

void nextPermutation(vector<int>& nums) 
{
	if(nums.empty())
		return;
	
	int sz=nums.size();
	int p=sz-1;
	while(p>0 &&  nums[p]<=nums[p-1])
	{
		--p;
	}
	if(p==0) // 翻转整个序列 a[0]~a[sz-1]
	{
		for(int i=0; i<sz/2; ++i)
			std::swap(nums[i], nums[sz-1-i]);
	}
	else
	{
		int j=0;
		while(nums[j]<nums[p-1])
			--j;
		std::swap(nums[p-1], nums[j]);
		// 翻转序列 a[p]~a[sz-1]
		int mid=(p+sz-1)/2;
		for(int k=p; k<=mid; ++k)
			std::swap(nums[k], nums[p+sz-1-k]);
	}
}

void nextPermutation(vector<int>& nums) 
{
	if(nums.empty())
		return;
	
	int sz=nums.size();
	int p=sz-1;
	while(p>0 &&  nums[p]<=nums[p-1])
	{
		--p;
	}
	if(p>0)
	{
		int j=sz-1;
		while(nums[j]<=nums[p-1])
			--j;
		std::swap(nums[p-1], nums[j]);
	}
	printVec(nums);
		
	// 翻转序列 a[p]~a[sz-1]
	int mid=(p+sz-1)/2;
	for(int k=p; k<=mid; ++k)
		std::swap(nums[k], nums[p+sz-1-k]);	
}

void test()
{
	{
	vector<int> nums({1, 2, 3});
	nextPermutation(nums);
	printVec(nums);
	}
	
	{
	vector<int> nums({1, 3, 2});
	nextPermutation(nums);
	printVec(nums);
	}
}

int main()
{
	test();
	
	return 0;
}
