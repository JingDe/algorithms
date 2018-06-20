class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sortVec(nums1);
        sortVec(nums2);
        
        int len1=nums1.size();
        int len2=nums2.size();
        int i=0, j=0;
        vector<int> result; 
        while(i<len1  &&  j<len2)
        {
        	if(nums1[i]==nums2[j])
        	{
				result.push_back(nums1[i]);
				i++;
				j++;
			}
        	else if(nums1[i]<nums2[j])
        		i++;
        	else
        		j++;
		}
		return result;
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
};
