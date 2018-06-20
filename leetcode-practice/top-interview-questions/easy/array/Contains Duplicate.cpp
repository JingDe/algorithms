class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
		// ºÚµ•—°‘Ò≈≈–Ú£¨≥¨ ± 
		int len=nums.size();
		for(int i=0; i<len-1; i++) 
		{
			int min=nums[i];
			int idx=i;
			for(int j=i+1; j<len; j++)
			{
				if(nums[j]<min)
				{
					min=nums[j];
					idx=j;
				}
				else if(nums[j]==min)
					return true;
			}
			if(i>=1  &&  min==nums[i-1])
				return true;
			else
				std::swap(nums[i], nums[idx]);
		}
		return false;
    }
    bool containsDuplicate(vector<int>& nums) {
        // ≤Â»Î≈≈–Ú
        int len=nums.size();
		for(int i=1; i<len; i++)
		{
			int tmp=nums[i];
            int j;
			for(j=i-1; j>=0  &&  nums[j]>tmp; j--)
			{
				nums[j+1]=nums[j];
			}
			if(j>=0  &&  nums[j]==tmp)
				return true;
			else
				nums[j+1]=tmp;
		}
		return false;
    }
};
