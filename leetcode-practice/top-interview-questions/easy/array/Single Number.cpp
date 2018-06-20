
class Solution {
public:
    int singleNumber(vector<int>& nums) {
		//std::sort(nums.begin(), nums.end()); // 超时 
		std::qsort(nums.data(), nums.size(), sizeof(int), [](const void* a, const void* b)
	    {
	        int arg1 = *static_cast<const int*>(a);
	        int arg2 = *static_cast<const int*>(b);
	 
	        if(arg1 < arg2) return -1;
	        if(arg1 > arg2) return 1;
	        return 0;
	 
	    //  return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
	    //  return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
	    });
        
		int len=nums.size();
        for(int i=0; i<len; i++)
            std::cout<<nums[i]<<" ";
        std::cout<<std::endl;
        int left=0, right=len-1, mid;
		while(left<right)
		{
			mid=(left+right)/2;
			if(nums[mid-1]==nums[mid])
			{
				// 左边有 mid-1-left 个元素
				if((mid-1-left) % 2 ==0) 
					left=mid+1;
				else
					right=mid-2;
			}	
			else if(nums[mid+1]==nums[mid])
			{
				// 左边有 mid-left 个元素 
				if((mid-left) % 2 ==0)
					left=mid+2;
				else
					right=mid-1;
			}
            else
                return nums[mid];
            std::cout<<left<<"\t"<<right<<std::endl;
		}
        //assert(left==right);
        std::cout<<left<<"\t"<<right<<std::endl;
		return nums[left];
    }
};
