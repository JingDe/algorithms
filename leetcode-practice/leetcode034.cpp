

vector<int> searchRange(vector<int>& nums, int target) {
	vector<int>::iterator it=std::lower_bound(nums.begin(), nums.end(), target);
	if(it==nums.end()  ||  *it!=target)
		return vector<int>({-1, -1});
	vector<int>::iterator it2=std::upper_bound(nums.begin(), nums.end(), target);
	return vector<int>({it-nums.begin(), it2-nums.begin()-1});
}

// 查找到某一个符合的位置，再向前向后遍历，不满足O(logn)
vector<int> searchRange(vector<int>& nums, int target) 
{
	if(nums.empty())
		return vector<int>({-1, -1});
	int left=0, right=nums.size()-1;
	int mid=0;
	while(left<=right)
	{
		mid=left+(right-left)/2;
		if(nums[mid]==target)
			break;
		if(nums[mid]<target)
			left=mid+1;
		else
			right=mid-1;
	}
	if(nums[mid]==target)
	{
		int start=mid, end=mid;
		while(start>=0  &&  nums[start]==target)
			start--;
		while(end<=nums.size()-1  &&  nums[end]==target)
			end++;
		return vector<int>({start+1, end-1});
	}
	return vector<int>({-1, -1});	
}

vector<int> searchRange(vector<int>& nums, int target)
{ 
	vector<int,int> targetRange({-1, -1});
	
	int leftIdx=extremeInsertionIndex(nums, target, true);
	
	if(leftIdx==nums.size()  ||  nums[leftIdx]!=target)
		return targetRange;
	
	targetRange[0]=leftIdx;
	targetRange[1]=extremeInsertionIndex(nums, target, false)-1;
	return targetRange;
}

int extremeInsertionIndex(vector<int>& nums, int targtet, bool left)
{
	int lo=0;
	int hi=nums.size();
	
	while(lo<hi)
	{
		int mid=(lo+hi)/2;
		if(nums[mid]>target  ||  (left  &&  target==nums[mid]))
		{
			hi=mid;
		}
		else // 当left是false，并且mid等于target
			lo=mid+1;
	}
	return lo;
}

