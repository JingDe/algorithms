

// 输入: 00000010100101000001111010011100
// 输出: 00111001011110000010100101000000
uint32_t reverseBits(uint32_t n) {
	uint32_t ans=0;
	for(int i=0; i<32; i++)
	{
		ans = (ans<<1) | ((n & (1<<i))>>i);
		
	}
	return ans;
}

class Solution {
private:
	map<uint32_t, uint32_t> memo;
public:
    uint32_t reverseBits(uint32_t n) {
		if(memo.find(n)!=memo.end())
			return memo[n];
        uint32_t ans=0;
        for(int i=0; i<32; i++)
        {
            ans = (ans<<1) | ((n & (1<<i))>>i);

        }
		memo[n]=ans;
        return ans;
    }
};