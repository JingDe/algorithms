
int threeSumClosest(vector<int>& nums, int target) 
{
	int res=0; // res最终返回最接近target的三数之和
	bool first=true;
	
	std::sort(nums.begin(), nums.end());
	int sz=nums.size();
	for(int i=0; i<sz; ++i)
	{
		int L=i+1;
		int R=sz-1;
		while(L<R)
		{
			int sum=nums[i]+nums[L]+nums[R];
			if(first)
			{
				res=sum;
				first=false;
			}
			else
			{
				if(std::abs(res-target)>std::abs(sum-target))
				{
					res=sum;
				}
			}
			
			if(sum==target)
				return target;
			else if(sum<target)
				++L;
			else
				--R;
		}
	}
	return res;
}