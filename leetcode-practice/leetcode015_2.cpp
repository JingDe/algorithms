
// 2sum

vector<vector<int> > 2sum_1(vector<int>& nums, int target)
{
	vector<vector<int> > res;
	int sz=nums.size();
	for(int i=0; i<sz; ++i)
		for(int j=i+1; j<sz; ++j)
			if(nums[i]+nums[j]==target)
				res.push_back(vector<int>({nums[i], nums[j]));
	return res;
}

vector<vector<int> > 2sum_2(vector<int>& nums, int target)
{
	vector<vector<int> > res;
	int sz=nums.size();
	map<int, int> m;
	for(int i=0; i<sz; ++i)
		m[target-nums[i]]=nums[i]; // 
	for(int i=0; i<sz; ++i)
		if(m.count(nums[i]))
			res.push_back(vector<int>({nums[i], m[nums[i]]}));
	return res;
}

vector<vector<int> > 2sum_3(vector<int>& nums, int target)
{
	vector<vector<int> > res;
	for(int i=0; i<nums.size(); ++i)
	{
		if()
	}
}

vector<vector<int> > 2sum_3(vector<int>& nums, int target)
{
	 vector<vector<int> > res;
	 map<int, std::pair<int,int> > hash;
	 for(int i=0; i<nums.size(); ++i)
	 {
		 for(int j=i+1; j<nums.size(); ++j)
		 {
			 if(hash.count(nums[j])) // i需要的二人组已经存在？？
			 {
				 // ???				 
				 res.push_back(vector<int>({nums[j], hash[nums[j]].first, hash[nums[j]].second}));
				 hash.erase(nums[j]);
			 }
			 else
			 {
				 int mark=0-(nums[i]+nums[j]);
				 hash[mark]=std::make_pair<int,int>(nums[i], nums[j]);
				 // 自己i，拉上j，需要的第三个人是mark
			 }
			 
		 }
	 }
	 return res;
}