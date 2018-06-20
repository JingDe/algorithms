class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> result;
        result.reserve(m+n);
        int i, j;
        for(i=0, j=0; i<m  &&  j<n;)
        {
        	if(nums1[i]<=nums2[j])
        	{
        		result.push_back(nums1[i]);
        		i++;
			}
			else
			{
				result.push_back(nums2[j]);
				j++;
			}
		}
		while(i<m)
		{
			result.push_back(nums1[i++]);
		}
		while(j<n)
		{
			result.push_back(nums2[j++]);
		}
		return result;
    }
};
