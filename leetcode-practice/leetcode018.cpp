#include<stdio.h>
#include<vector>
#include<algorithm> 

using std::vector;

// 4数组之和

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

// vector<vector<int> > ksum_recursive(vector<int>& nums, int cur_k, int cur_target, vector<int> stack, int stack_index, int begin)
// {}
