

bool containsNearbyDuplicate(vector<int>& nums, int k) {
	std::map<int, int> num2pos;
	for(int i=0; i<k; i++)
	{
		if(num2pos.count(nums[i]))
		{
			int start=num2pos[nums[i]];
			if(i-start<=k)
				return true;
		}
		num2pos[nums[i]]=i;
	}
	return false;
}