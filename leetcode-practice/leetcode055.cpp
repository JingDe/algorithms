
// 方法一：回溯 超时
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
			return true; // 不记录中间结果
	}
	return false; // 不记录中间结果
}

// bool canJump(vector<int>& nums) {
	// if(nums.empty())
		// return false;
	// for(int i=nums.size()-2; i>=0; --i)
		// if(nums[i]>=len-i)
			// return true;
	// return false;
// }

// 方法二：自顶向下的动态规划，使用记忆表
enum{
	UNKNOWN=2,
	GOOD=1,
	BAD=0,
};
bool canJump(vector<int>& nums)
{
	if(nums.empty())
		return false;
	vector<int> memo(nums.size(), UNKNOWN);
	memo[nums.size()-1]=GOOD;
	
	return helper(0, memo, nums);
}

bool helper(int startPos, vector<int>& memo, const vector<int>& nums)
{
	if(memo[startPos]!=UNKNOWN)
		return memo[startPos];
	
	for(int step=nums[startPos]; step>0; --step)
	{
		if(startPos+step>=nums.size())
                continue;
		if(helper(startPos+step, memo, nums))
		{
			memo[startPos]=GOOD;
			return true;
		}
	}
	memo[startPos]=BAD; // !!!注意保存中间状态
	return BAD;
}

// 方法二

bool canJump(vector<int>& nums)
{
	vector<int> memo(nums.size(), UNKNOWN);
	memo[nums.size()-1]=GOOD;
	
	return canJumpFromPosition(0, memo, nums);
}
bool canJumpFromPosition(int position, vector<int>& memo, const vector<int>& nums)
{
	if(memo[startPos]!=UNKNOWN)
		return memo[startPos];
		
	int furtherJump=std::min(position+nums[position], nums.size()-1);
	for(int nextPosition=position+1; nextPosition<=furtherJump; ++nextPosition)
	{
		if(canJumpFromPosition(nextPosition, nums))
		{
			memo[startPos]=GOOD;
			return true;
		}
	}
	
	memo[startPos]=BAD;
	return false;
}


// 方法三：
bool canJump(vector<int>& nums)
{
	if(nums.empty())
		return false;
	vector<int> memo(nums.size(), UNKNOWN);
	memo[nums.size()-1]=GOOD;
	
	for(int position=nums.size()-2; position>=0; --position)
	{
		int maxStep=nums[position];
		for(int step=maxStep; step>0; --step)
		{
			if(position+step>=nums.size())
				continue;
			if(memo[position+step]==GOOD)
			{
				memo[position]=GOOD;
				break;
			}
		}
		if(memo[position]==GOOD)
			continue;
		memo[position]=BAD;
	}
	return memo[0]==GOOD;
}

// 方法四： 
bool canJump(vector<int>& nums)
{
	if(nums.empty())
		return false;
	
	int leftmostGoodPos=nums.size()-1;
	for(int positon=nums.size()-2; positon>=0; --position)
	{
		if(position+nums[position]>=leftmostGoodPos)
		{
			leftmostGoodPos=positon;
		}			
	}
	return leftmostGoodPos==0;
}

