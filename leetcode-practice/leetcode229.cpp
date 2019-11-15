
vector<int> majorityElement(vector<int>& nums) {
	if(nums.empty())
		return vector<int>();
	int count1=0;
	int count2=0;
	int candidate1=0;
	int candidate2=1;
	for(int i=0; i<nums.size(); ++i)
	{
		if(nums[i]==candidate1)
			count1++;
		else if(nums[i]==candidate2)
			count2++;
		else if(count1==0)
		{
			candidate1=n;
			count1=1;
		}
		else if(count2==0)
		{
			candidate2=n;
			count2=1;
		}
		else
		{
			count1--;
			count2--;
		}
	}
	vector<int> ans;
	if(nums.count(candidate1)>nums.size()/3)
		ans.push_back(candidate1);
	if(nums.count(candidate2)>nums.size()/3)
		ans.push_back(candidate2);
	return ans;
}