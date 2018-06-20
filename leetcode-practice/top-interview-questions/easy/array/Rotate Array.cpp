
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // ԭ���±�Ϊi��nums[i]Ԫ�أ�����kλ��֮����±꣺ (i+k)% (nums.size()) 
        // ���㷨��Ҫ gcd(len, k) �� 
        int len=nums.size();
        k=k % len;
        int times=gcd(len, k);
        for(int startpos=0; startpos<times; startpos++)
        	helper(nums, startpos, k);
    }
    void helper(vector<int>& nums, int startpos, int k) 
    {
        int len=nums.size();
        int curpos=startpos;
        int newpos;
        int temp=nums[startpos];
        while(true)
        {
        	newpos=(curpos+k) % len;
        	
        	std::swap(temp, nums[newpos]);
        	curpos=newpos;
        	if(curpos==startpos)
        		break;
		}
	}
	int gcd(int a, int b)
	{
		int tmp;
		if(a<b)
		{
			tmp=a;
			a=b;
			b=tmp;
		}
		while(b)
		{
			tmp=a;
			a=b;
			b=tmp % b;
		}
		return a;
	}
};
