
// 两趟扫描
void sortColors(vector<int>& nums) {
	int num0=0, num1=0, num2=0;
	for(int i=0; i<nums.size(); ++i)
	{
		if(nums[i]==0)
			++num0;
		if(nums[i]==1)
			++num1;
		if(nums[i]==2)
			++num2;
	}
	vector<int>& ans(num0, 0);
	ans.reserve(nums.size());
	for(int i=0; i<num1; ++i)
		ans.push_back(1);
	for(int i=0; i<num2; ++i)
		ans.push_back(2);
	return ans;
}

// 两指针，一趟扫描
void sortColors(vector<int>& nums) {
	int left=0, right=nums.size()-1;
	while(left<right)
	{
		while(nums[left]==0)
			++left;
		while(nums[right]==2)
			--right;
		// 左边是1或者2，右边是0或者1
		
	}
}

// 3指针
void sortColors(vector<int>& nums) 
{
	int cur=0;
	int left=0;
	int right=nums.size()-1;
	// left指向当前最后一个0的下一位置
	// right指向当前第一个2的前一位置
	while(cur<right)
	{
		if(nums[cur]==0)
		{
			std::swap(nums[left++], nums[cur++]);
		}
		else if(nums[cur]==2)
		{
			std::swap(nums[cur], nums[right--]);
		}
		else
			cur++;
	}
	
}


