
vector<int> productExceptSelf(vector<int>& nums) 
{
	if(nums.empty())
		return vector<int>();
	vector<int> ans(nums.size(), 1);
	
	int n=nums.size();
	int leftProduct[n];
	leftProduct[0]=1;
	for(int i=1; i<n; ++i)
	{
		leftProduct[i]=leftProduct[i-1]*nums[i-1];
	}
	
	int rightProduct[n+1];
	rightProduct[n]=1;
	for(int i=n-1; i>=1; i--) // i>=0
	{
		rightProduct[i]=rightProduct[i+1]*nums[i];
	}
	
	for(int i=0; i<nums.size(); ++i)
	{
		ans[i]=leftProduct[i]*rightProduct[i+1];
	}
	return ans;
}

vector<int> productExceptSelf(vector<int>& nums) 
{
	if(nums.empty())
		return vector<int>();
	int length=nums.size();
	int L[length];
	int R[length];

	vector<int> answer(length, 1);
	L[0]=1;
	for(int i=1; i<length; ++i)
	{
		L[i]=nums[i-1]*L[i-1];
	}

	R[length-1]=1;
	for(int i=length-2; i>=0; i--)
	{
		R[i]=nums[i+1]*R[i+1];
	}

	for(int i=0; i<length; i++)
	{
		answer[i]=L[i]*R[i];
	}
	return answer;
}

vector<int> productExceptSelf(vector<int>& nums) 
{
	if(nums.empty())
		return vector<int>();
	
	int n=nums.size();
	vector<int> ans(n);
	ans[0]=1;
	for(i=1; i<n; ++i)
	{
		answer[i]=answer[i-1]*nums[i-1];
	}
	
	int R=1;
	for(int i=n-1; i>=0; i--)
	{
		answer[i] *= R;
		R *= nums[i];
	}
	return answer;
}