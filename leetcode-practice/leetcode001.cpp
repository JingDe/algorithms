
// 两数之和双指针法
vector<int> twoSum(vector<int>& nums, int target) 
{
	std::sort(nums.begin(), nums.end());
	int sz=nums.size();
	int L=0, R=sz-1;
	while(L<R)
	{
		if(nums[L]+nums[R]==target)
		{
			vector<int> res({nums[L], nums[R]});
			return res;
		}
		if(nums[L]+nums[R]<target)
			++L;
		else
			--R;
	}
	return vector<int>();
}