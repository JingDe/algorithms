

// NO 78
// 增量构造法
vector<vector<int>> subsets(vector<int>& nums) 
{
	vector<vector<int>> ans;
	vector<int> numSet;
	backtracking2(ans, nums, numSet, 0);
	return ans;
}

void backtracking2(vector<vector<int>>& ans, const vector<int>& nums, vector<int> numSet, int cur)
{
	ans.push_back(numSet);
	
	for(int i=cur; i<nums.size(); ++i)
	{
		numSet.push_back(nums[i]);
		backtracking2(ans, nums, numSet, i+1);
		numSet.pop_back();
	}
}


vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	vector<vector<int>> ans;
	
	std::sort(nums.begin(), nums.end());
	
	vector<int> numSet;
	backtracking(ans, nums, numSet, 0);
	
	return ans;
}

void backtracking(vector<vector<int>>& ans, const vector<int>& nums, vector<int> numSet, int cur)
{
	ans.push_back(numSet);
	
	for(int i=cur; i<nums.size(); ++i)
	{
		//if(i==0  ||  nums[i]!=nums[i-1])
		if(i==cur  ||  nums[i]!=nums[i-1])
		{
			numSet.push_back(nums[i]);
			backtracking(anst, nums, numSet, i+1);
			numSet.pop_back();
		}
	}
}




// 回溯法
vector<vector<int> > subsetsWithDup(vector<int> &nums)
{
	vector<vector<int>> ans;
	std::sort(nums.begin(), nums.end());
	backtracking1(nums, 0, vector<int>(), ans);
	return ans;
}

void backtracking1(const vector<int>& nums, int start, vector<int> temp, vector<vector<int>>& ans)
{
	ans.push_back(temp);
	
	for(int i=start; i<nums.size(); ++i)
	{
		if(i>start  &&  nums[i]==nums[i-1])
		{
			continue;
		}
		temp.push_back(nums[i]);
		backtracking1(nums, i+1, temp, ans);
		temp.pop_back();
	}
}



//======================================

vector<vector<int>> subsets(vector<int>& nums) {
	int n=nums.size();
	int max=pow(2, n)-1;
	
	std::sort(nums.begin(), nums.end());
	
	vector<vector<int> > ans;
	set<vector<int>> uniqueSet;
	for(int a=0; a<=max; ++a)
	{
		vector<int> numSet;
		getSet(numSet, a, n, nums); // 根据整数a的二进制表示低n位，创建一个nums的子集numSet
		//ans.push_back(numSet);
		uniqueSet.insert(numSet);
	}
	for(set<vector<int>>::iterator it=uniqueSet.begin(); it!=uniqueSet.end(); ++it)
		ans.push_back(*it);
	return ans;
}

void getSet(vector<int>& numSet, int a, int n, const vector<int>& nums)
{
	numSet.clear();
	for(int i=0; i<n; ++i)
	{
		if(a  &  (1<<i))
			numSet.push_back(nums[i]);
	}
}

[4,4,4,1,4]
[1,4,4,4,4]
Output
[[],[1],[1,4],[1,4,4],[1,4,4,4],[1,4,4,4,4],[4],[4,4],[4,4,4],[4,4,4,4]]



vector<vector<int> > subsetsWithDup(vector<int> &S)
{
	vector<vector<int>> totalset;
	totalset.push_back(vector<int>());
	
	sort(S.begin(), S.end());
	
	for(int i=0; i<S.size(); )
	{
		int count=0; // 相同元素的个数
		while(cout+i<S.size()  &&  S[count+i]==S[i])
			count++;
		
		int previousN=totalset.size();
		for(int k=0; k<previousN; k++)
		{
			vector<int> instance=totalset[k]; // 对当前子集集合中的每一个子集
			for(int j=0; j<count; j++) 
				// 某个元素出现了count次。参与的子集中，分别出现了0次、1次...count次。
			{
				instance.push_back(S[i]);
				totalset.push_back(instance);
			}
		}
		i+=count;
	}
	return totalset;
}

[4,2,1,2,3]
[1,2,2,3,4]
Output
[[],[1],[2],[2,2],[1,2],[1,2,2],[3],[1,3],[2,3],[2,2,3],[1,2,3],[1,2,2,3],[4],[1,4],[2,4],[2,2,4],[1,2,4],[1,2,2,4],[3,4],[1,3,4],[2,3,4],[2,2,3,4],[1,2,3,4],[1,2,2,3,4]]
Expected
[[],[1],[1,2],[1,2,2],[1,2,2,3],[1,2,2,3,4],[1,2,2,4],[1,2,3],[1,2,3,4],[1,2,4],[1,3],[1,3,4],[1,4],[2],[2,2],[2,2,3],[2,2,3,4],[2,2,4],[2,3],[2,3,4],[2,4],[3],[3,4],[4]]



// 位操作
vector<vector<int> > subsetsWithDup(vector<int> &nums)
{
	std::sort(nums.begin(), nums.end());
	
	vector<vector<int>> ans;
	
	int subsetNum=1<<nums.size();
	for(int i=0; i<subsetNum; ++i) // 每一种可能子集，
	{
		vector<int> lst;
		bool illegal=false;
		for(int j=0; j<nums.size(); j++) // 判断是否重复
		{
			if((i>>j  &  1)==1) // 当前位是1，第j位
			{
				// 当前是重复数字，并且前一位是0，跳过
				if(j>0  &&  num[j]==num[j-1]  &&  (i>>(j-1)&1)==0)
				{
					illegal=true;
					break;
				}
				else
					lst.push_back(nums[j]);
			}
		}
		if(!illegal)
			ans.push_back(lst);
	}
	return ans;
}


	