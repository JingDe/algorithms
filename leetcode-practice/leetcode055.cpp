
bool canJump(vector<int>& nums) {
	if(nums.empty())
		return false;
	
	return helper(nums, 0);
}
bool helper(const vector<int>& nums, int cur)
{
	if(cur>=nums.size()-1)
		return true;
	
	int maxStep=nums[cur];
	for(int step=maxStep; step>=1; --step)
	{
		if(helper(nums, cur+step))
			return true;
	}
	return false;
}

bool canJump(vector<int>& nums) {
	if(nums.empty())
		return false;
	for(int i=nums.size()-2; i>=0; --i)
		if(nums[i]>=len-i)
			return true;
	return false;
}