
int missingNumber(vector<int>& nums) {
	int n=0, cur_sum=0;
	for(int i=0; i<nums.size(); i++)
	{
		n=std::max(n, nums[i]);
		cur_sum += nums[i];
	}
	return n*(n+1)/2-cur_sum;
}