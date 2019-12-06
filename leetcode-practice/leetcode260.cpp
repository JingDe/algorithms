

vector<int> singleNumber(vector<int>& nums) {
	int all=nums[0];
	for(int i=1; i<nums.size(); i++)
		all = all ^ nums[i];
	
	int p;
	for(p=0; p<sizeof(all)*8; ++p)
		if(all  &  1<<p)
			break;
	// all从低到高第p位是1

	int all_set = 0;
	int all_unset = 0;
	for(int i=0; i<nums.size(); ++i)
	{
		if(nums[i]  &  1<<p)
		{
			all_set = all_set ^ nums[i];
		}
		else
		{
			all_unset = all_unset ^  nums[i];
		}
	}

	return std::vector<int>({all_set, all_unset});
}

vector<int> singleNumber(vector<int>& nums)
{
	int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
	/* 获得最后一个等于1的位 */
	diff &= -diff;
	
	vector<int> rets ={0, 0};
	for(int num : nums)
	{
		if(num  &  diff)
			res[0] ^= num;
		else
			res[1] ^= num;
	}
	return rets;
}