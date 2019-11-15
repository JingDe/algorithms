
vector<string> summaryRanges(vector<int>& nums) {
	vector<string> ans;
	if(nums.empty())
		return ans;
	
	int left=nums[0];
	int right=nums[0];
	for(int i=1; i<nums.size(); i++)
	{
		if(nums[i]==right+1)
		{
			right=nums[i];
		}
		else
		{
			ans.push_back(rangeToStr(left, right));
			left=right=nums[i];
		}		
	}
	ans.push_back(rangeToStr(left, right));
	return ans;
}

string rangeToStr(int left, int right)
{
	if(left==right)
		return std::to_string(left);
	else
		return std::to_string(left)+"->"+std::to_string(right);
}