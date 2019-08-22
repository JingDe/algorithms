#include<stdio.h>
#include<vector>
#include<algorithm> 

using std::vector;

// 4数之和

void printVec(vector<int>& v)
{
	for(int i=0; i<v.size(); ++i)
		printf("%d ", v[i]);
	printf("\n");
}

// 固定两个数，双指针
// -2 -1 0 0 1 2
vector<vector<int>> fourSum(vector<int>& nums, int target) 
{
	vector<vector<int> > res;
	std::sort(nums.begin(), nums.end());
	int sz=nums.size();
	for(int i=0; i<sz-3; ++i)
	{
		if(nums[i]*4>target)
			return res;
		if(i>0  &&  nums[i]==nums[i-1])
			continue;
		printf("first %d\n", nums[i]);
		for(int j=i+1; j<sz-2; ++j)
		{
			if(nums[i]+nums[j]*3>target)
				return res;
			if(j>i+1  &&  nums[j]==nums[j-1])
				continue;
		
			int L=j+1;
			int R=sz-1;
			while(L<R)
			{
				int sum=nums[i]+nums[j]+nums[L]+nums[R];
				printf("%d %d %d %d\n", nums[i], nums[j], nums[L], nums[R]);
				if(sum==target)
				{
					vector<int> arr({nums[i], nums[j], nums[L], nums[R]});
					res.push_back(arr);
					++L;
					--R;
				}
				else if(sum<target)
				{
					++L;
				}
				else
					--R;
			}
		}
	}
	return res;
}
void test()
{
	vector<int> nums({1,0,-1,0,-2,2});
	
	vector<vector<int> > res=fourSum(nums, 0);
	printf("result\n");
	for(int i=0; i<res.size(); ++i)
	{
		printVec(res[i]);
	}
}

int main()
{
	test();
	
	return 0;
}

// 调用3sum解法



// 递归解法
// vector<vector<int>> fourSum(vector<int>& nums, int target) 
// {
	// std::sort(nums.begin(), nums.end());
	
// }

// vector<vector<int> > ksteum_recursive(vector<int>& nums, int cur_k, int cur_target, vector<int> stack, int stack_index, int begin)
// {}


// 方法一： 从2sum到3sum，从3sum到4sum
void twoSumForForSum(vector<int>& nums, int target, int low, int high, vector<vector<int>> forSumList, int z1, int z2)
{
	
}

vector<vector<int>> fourSum(vector<int>& nums, int target) 
{
	
}
	

// 方法二：k-sum
vector<vector<int>> fourSum(vector<int>& nums, int target) 
{
	std::sort(nums.begin(), nums.end());
	return kSum(nums, target, 4, 0);
}

vector<vector<int>> kSum(vector<int>& nums, int target, int k,  int index)
{
	vector<vector<int>> res;
	if(index >=nums.size())
		return res;
	
	if(k==2)
	{
		int i=index,j=len-1;
		while(i<j)
		{
			if(target-nums[i]==nums[j])
			{
				vector<int> temp;
				temp.push_back(nums[i]);
				temp.push_back(nums[j]);
				res.push_back(temp);
				while(i<j  &&  nums[i]==nums[i+1]) i++;
				while(i<j  &&  nums[j-1]==nums[j]) j--;
				i++;
				j--;
			}
			else if(target-nums[i]>nums[j])
				i++;
			else
				j--;
		}
	}
	else
	{
		for(int i=index; i<len-k+1; i++)
		{
			vector<vector<int>> temp=kSum(nums, target-nums[i], k-1, i+1);
			for(vector<int> t : temp)
			{
				t.push_back(nums[i]);
				res.push_back(t);
			}
			
			while(i<len-1  &&  nums[i]==nums[i+1])
				i++;
		}
	}
	return res;
}



