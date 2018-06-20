
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len=nums.size();
        int sp=0; // 已排好序的下一位置 
        int dp=0; // 当前遍历到的位置
        int elem=INT_MIN;
		for(dp=0; dp<len; dp++)
		{
			if(nums[dp]!=elem)
			{
				nums[sp++]=nums[dp];
				elem=nums[dp];
			}
		}
		return sp;
    }
};
