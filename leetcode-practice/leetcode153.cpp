

// O(n)
int findMin(vector<int>& nums) {

}


// O(logN) 错误解法
int findMin(vector<int>& nums) {
	int left=0;
	int right=nums.size()-1;
	int mid=0;
	while(left+1<right)
	{
		mid=left+(right-left)/2;
		if(nums[mid]>=nums[left])
			left=mid;
		else
			right=mid;
		
	}
	if(left==right)
		return nums[left];
	else
		return min(nums[left], nums[right]);
}

int findMin(vector<int>& nums) {
	if(nums.empty())
		return 0;
	if(nums.size()==1)
		return nums[0];
	if(nums.back()>nums.front())
		return nums.front();
	int left=0;
	int right=nums.size()-1;
	int mid=0;
	while(left<=right)
	{
		mid=left+(right-left)/2;
		if(nums[mid]>nums[mid+1])
			return nums[mid+1];
		if(nums[mid-1]>nums[mid])
			return nums[mid];
		
		if(nums[mid]>nums[0])
			left=mid+1;
		else
			right=mid-1;		
	}
	return -1;
}