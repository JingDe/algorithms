
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len=nums.size();
        int sp=0; // ���ź������һλ�� 
        int dp=0; // ��ǰ��������λ��
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
