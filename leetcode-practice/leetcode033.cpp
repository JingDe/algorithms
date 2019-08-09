
int search(vector<int>& nums, int target) {
	if(nums.empty())
		return -1;
	int left=0; 
	int right=nums.size()-1;
	while(left<=right)
	{
		int mid=left+(right-left)/2;
		if(nums[mid]==target)
			return mid;
		if(nums[mid]<target)
		{
			if(nums.front()<=target)
			{
				left=0;
				right=mid-1;
			}
			else
			{
				left=mid+1;
			}
		}
		else
		{
			if(nums.back() >= target)
			{
				
			}
		}
	}
}


int search(vector<int>& nums, int target) {
	if(nums.empty())
		return -1;
	int left=0; 
	int right=nums.size()-1;
	while(left<=right)
	{
		int mid=left+(right-left)/2;
		if(nums[mid]==target)
			return mid;
		if(nums[mid]<target)
		{
			if(nums[right]>=target)
			{
				left=mid+1;
			}
			else
			{
				right=mid-1;
			}
		}
		else
		{
			if(nums[left]<=target)
			{
				right=mid-1;
			}
			else
				left=mid+1;
		}
	}
	return -1;
}


int search(vector<int>& nums, int target) {
	if(nums.empty())
		return -1;
	int left=0; 
	int right=nums.size()-1;
	while(left<=right)
	{
		int mid=left+(right-left)/2;
		if(nums[mid]==target)
			return mid;
		if()
	}
	return -1;
}