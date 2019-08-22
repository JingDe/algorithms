

int removeDuplicates(vector<int>& nums) {
	if(nums.empty())
		return 0;
	
	int next=1;
	int cur=1;
	int lastValue=nums[0];
	int occurCount=1;
	
	while(cur<nums.size())
	{
		if(nums[cur]!=lastValue)
		{
			nums[next++]=nums[cur];
			lastValue=nums[cur];
			occurCount=1;
		}
		else if(occurCount<2)
		{
			nums[next++]=nums[cur];
			occurCount++;
		}
		else
			occurCount++;
		cur++;
	}
	return next;
}