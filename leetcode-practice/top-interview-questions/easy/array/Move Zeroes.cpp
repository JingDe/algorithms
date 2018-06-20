class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int len=0;
        int i;
        for(i=len-1; i>=0; i--)
        {
        	if(nums[i]==0)
        		nums.erase(nums.begi()+i);
        	nums.push_back(0);
		}
    }
};
