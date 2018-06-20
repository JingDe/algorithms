class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        sortVec(nums);
        
        vector<int>::iterator limit=std::lower_bound(nums.begin(), nums.end(), target/2);
        for(vector<int>::iterator it=nums.begin(); it<=limit; it++) 
        {
        	vector<int>::iterator right=std::find(it, nums.end(), target-*it);
        	if(right!=nums.end())
        		return vector<int>{it-nums.begin(), right-nums.begin()}; 
		}
    }
    void sortVec(vector<int>& nums) 
    {
    	std::qsort(nums.data(), nums.size(), sizeof(int), [](const void* a, const void* b){
		        int arg1 = *static_cast<const int*>(a);
		        int arg2 = *static_cast<const int*>(b);
		 
		        if(arg1 < arg2) return -1;
		        if(arg1 > arg2) return 1;
		        return 0;
		    });
	}
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int>::iterator limit=nums.end();
		for(vector<int>::iterator it=nums.begin(); it<=limit; it++) 
        {
        	vector<int>::iterator right=std::find(it, nums.end(), target-*it);
        	if(right!=nums.end())
        		return vector<int>{it-nums.begin(), right-nums.begin()}; 
		}
	}
};
