
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        vector<int>::iterator it=std::lower_bound(nums.begin(), nums.end(), target);
		if(it==nums.end())
			return nums.size();
		return it-nums.begin();
    }
};