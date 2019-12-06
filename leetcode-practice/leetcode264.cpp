
int nthUglyNumber(int n) {
	std::vector<int> nums;
	nums.reserve(n);
	nums.push_back(1);
	
	int p2=0;
	int p3=0;
	int p5=0;
	while(nums.size()<n)
	{
		int next2=nums[p2]*2;
		int next3=nums[p3]*3;
		int next5=nums[p5]*5;
		
		//int next= min(min(next2, next3), next5);

		
		nums.push_back(next);
	}
	
	return nums[n-1];
}