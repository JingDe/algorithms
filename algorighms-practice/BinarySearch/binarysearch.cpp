// 二分查找 和 变体


// 基础二分查找
void binary_search(const vector<int>& nums, int target)
{
	int left=0;
	int right=nums.size()-1;
	
	int mid;
	while(left <= right)
	{
		mid = (right-left)/2+left;
		if(nums[mid]==target)
			return mid;
		if(nums[mid]>target)
			right=mid-1;
		else
			left=mid+1;
	}
	return -1;
}
/*
当target存在重复，返回的位置不确定。
*/


/*当left存在重复时*/
void binary_search(const vector<int>& nums, int target)
{
	int left=0;
	int right=nums.size()-1;
	
	int mid;
	while(left <= right)
	{
		mid = (right-left)/2+left;

		if(nums[mid]>target)
			right=mid-1;
		else
			left=mid+1;
	}
	return -1;
}

