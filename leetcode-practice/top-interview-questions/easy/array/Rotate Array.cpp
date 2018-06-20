
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // 原来下标为i的nums[i]元素，右移k位，之后的下标： (i+k)% (nums.size()) 
        // 此算法需要 gcd(len, k) 趟 
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
