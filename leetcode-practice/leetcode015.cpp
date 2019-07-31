#include<stdio.h>
#include<vector>

using std::vector;

vector<int> sortVec_mergesort_helper(const vector<int>& nums, int start, int end);
vector<int> merge(const vector<int>& left, const vector<int>& right);


void printVec(const vector<int>& vec)
{
	for(int i=0; i<vec.size(); ++i)
		printf("%d ", vec[i]);
	printf("\n");
}

// 排序算法

vector<int> sortVec(const vector<int>& nums)
{
	// 堆排序、快速排序、归并排序 复杂度O(nlogn)
#ifdef USE_QS
	return sortVec_quicksort(nums);
#else
	return sortVec_mergesort(nums);
#endif
}

vector<int> sortVec_quicksort(const vector<int>& nums)
{
	// 挖坑法、交换指针法、单向移动法
	return nums;
}

vector<int> quicksort_hole(const vector<int>& nums)
{
	vector<int> res=nums;
	int sz=nums.size();
	int left=0, right=sz-1;
	while(left<right)
	{
		
	}
}


vector<int> sortVec_mergesort(const vector<int>& nums)
{
	int sz=nums.size();
	return sortVec_mergesort_helper(nums, 0, sz-1);
}

vector<int> sortVec_mergesort_helper(const vector<int>& nums, int start, int end)
{
	if(start>end)
		return vector<int>();
	if(start==end)
		return nums;
	int sz=end-start+1;
	int half=sz/2;
	vector<int> left=sortVec_mergesort_helper(nums, 0, half-1);
	vector<int> right=sortVec_mergesort_helper(nums, half, end);
	return merge(left, right);
}

vector<int> merge(const vector<int>& left, const vector<int>& right)
{
	if(left.empty())
		return right;
	if(right.empty())
		return left;
	int len1=left.size();
	int len2=right.size();
	//vector<int> res(len1+len2);
	vector<int> res;
	res.reserve(len1+len2);
	int i=0, j=0;
	while(i<len1  &&  j<len2)
	{
		if(left[i]<=right[j])
			res.push_back(left[i++]);
		else
			res.push_back(right[j++]);
	}
	while(i<len1)
		res.push_back(left[i++]);
	while(j<len2)
		res.push_back(right[j++]);
	return res;
}


void test_sortVec_mergesort()
{
	vector<int> nums({8, 9, 1, 2, 1, 4, 1, 5, 0, 8, 1, 7});
	vector<int> sorted=sortVec_mergesort(nums);
	printVec(sorted);
}


// 查找算法
//
bool binaryFind(vector<int>& nums, int target)
{
	return true;
}

vector<vector<int>> threeSum_findC_sort(vector<int>& nums) 
{
	vector<vector<int>> res;	
	//vector<int> nums2=sortVec(nums);
	// 使用stl算法排序
	vector<int> nums2=nums;
	std::sort(nums2.begin(), nums2.end());
	
	int sz=nums.size();
	for(int ia=0; ia<sz; ++ia)
		for(int ib=ia+1; ib<sz; ++ib)
		{
			int c=0-(nums2[ia]+nums2[ib]);
			
			//if(binaryFind(nums2, c))
			if(std::find(nums2.begin()+ib+1, nums2.end(), c)!=nums2.end())
			{
				vector<int> seq({nums2[ia], nums2[ib], c});
				if(std::find(res.begin(), res.end(), seq)==res.end())
					res.push_back(seq);
			}
		}
	return res;
}

// 解法一：两个指针遍历
vector<vector<int>> threeSum_2pointer(vector<int>& nums)
{
	vector<vector<int> > res;
	std::sort(nums.begin(),  nums.end());
	int sz=nums.size();
	for(int i=0; i<sz; ++i)
	{
		if(nums[i]>0)
			break;
		if(i!=0  &&  nums[i]==nums[i-1])
			continue;
		
		int s=i+1;
		int e=sz-1;
		while(s<sz  &&  e<sz  &&  s<e)
		{
			int sum=nums[i]+nums[s]+nums[e];
			if(sum==0)
			{
				vector<int> sol({nums[i], nums[s],  nums[e]});
				res.push_back(sol);
				while(s+1<e  &&  nums[s]==nums[s+1])
					++s;
				while(e-1>s  &&  nums[e]==nums[e-1])
					--e;
				++s;
				--e;
			}
			else if(sum<0)
				++s;
			else
				--e;			
		}
	}
	return res;
}


vector<vector<int>> threeSum_2pointer1(vector<int>& nums)
{
	vector<vector<int> > res;
	std::sort(nums.begin(), nums.end());
	int len=nums.size();
	if(len==0)
		return res;
	for(int i=0; i<len; ++i)
	{
		if(nums[i]>0)
			break;
		if(i>0  &&  nums[i]==nums[i-1])
			continue;
		int L=i+1;
		int R=len-1;
		while(L<R)
		{
			int sum=nums[i]+nums[L]+nums[R];
			if(sum==0)
			{
				res.push_back(vector<int>({nums[i], nums[L], nums[R]}));
				while(L<R  &&  nums[L]==nums[L+1])
					++L;
				while(L<R  &&  nums[R]==nums[R-1])
					--R;
				++L;
				--R;
			}
			else if(num<0)
				++L;
			else
				--R;
		}
	}
	return res;
}

int main()
{
	test_sortVec_mergesort();
	
	return 0;
}