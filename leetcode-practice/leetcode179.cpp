


string largestNumber(vector<int>& nums) {
	bool allZero=true;
	for(int i=0; i<nums.size(); i++)
		if(nums[i]!=0)
		{
			allZero=false;
			break;
		}
	if(allZero)
		return "0";
	std::sort(nums.begin(), nums.end(), comparator);
	print(nums);
	string ans;
	ans=getString(nums);
	return ans;
}


bool comparator(int a, int b)
{
	string sa=std::to_string(a);
	string sb=std::to_string(b);
	int i=0;
	int j=0;
	char ca=sa[0];
	char cb=sb[0];
	while(i<sa.size()  ||  j<sb.size())
	{
		//if(a[i]!=b[j])
			//return a[i]>b[j];
		if(ca!=cb)
			return ca>cb;
		i++;
		j++;
		if(i<sa.size())
			ca=sa[i];
		if(j<sb.size())
			cb=sb[j];
	}
	return true;
}

void print(const vector<int>& nums)
{
	for(int i=0; i<nums.size(); ++i)
		printf("%d, ", nums[i]);
	printf("\n");
}

string getString(const vector<int>& nums)
{
	string ans;
	for(int i=0; i<nums.size(); ++i)
		ans=ans+std::to_string(nums[i]);
	return ans;
}


// 
string largestNumber(vector<int>& nums) {
	vector<string> numsStr;
	for(int i=0; i<nums.size(); ++i)
		numsStr.push_back(std::to_string(nums[i]));
	
	std::sort(numsStr.begin(), numsStr.end(), comparator2);
	
	string ans;
	ans=getString2(numsStr);
	return ans;
}


string getString2(const vector<string>& nums)
{
	string ans;
	for(int i=0; i<nums.size(); ++i)
		ans=ans+nums[i];
	return ans;
}

bool comparator2(const string& sa, const string& sb)
{
	int i=0;
	int j=0;
	char ca=sa[0];
	char cb=sb[0];
	while(i<sa.size()  ||  j<sb.size())
	{
		if(ca!=cb)
			return ca>cb;
		i++;
		j++;
		if(i<sa.size())
			ca=sa[i];
		if(j<sb.size())
			cb=sb[j];
	}
	return true;
}

// 正确的排序规则
bool comparator3(const string& sa, const string& sb)
{
	string left=sa+sb;
	string right=sb+sa;	
	return left>right;
}

// 
string largestNumber(vector<int>& nums) 
{
	vector<string> asStrs;
	for(int i=0; i<nums.size(); ++i)
	{
		asStrs.push_back(std::to_string(nums[i]));
	}
	
	std::sort(nums.begin(), nums.end(), cmp)
	
	if(asStrs[0]=="0")
		return "0";
	string ans;
	for(int i=0; i<asStrs.size(); ++i)
		ans+=asStrs[i];
	return ans;
}

bool cmp(const string& a, const string& b)
{
	
}
