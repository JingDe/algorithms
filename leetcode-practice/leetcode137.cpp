

int singleNumber(vector<int>& nums) {
	int ones=0, twos=0, threes=0;
	for(int num : nums)
	{
		twos |= ones & num;
		ones ^= num;
		threes = ones & twos;
		ones &= ~threes;
		twos &= ~threes;
	}
	return ones;
}


int singleNumber(vector<int>& nums) {
	int ones=0, twos=0;
	for(int num : nums)
	{
		ones = ones ^ num & ~twos;
        twos = twos ^ num & ~ones;
	}
	return ones;
}

public int singleNumber(int[] nums) {
    int ones = 0, twos = 0, threes = 0;
    for (int num : nums) {
        twos |= ones & num;//用Int32位任意一位出现了一次1的结果ones 和当期num与 则同一个位置出现两次的会是1合并到twos 出现一次的保持twos原先的位
        ones ^= num;//一直异或num 则Int中的某一位出现一次1 ones为1 两次则异或成0 三次还是1 但是会被后续操作清零
        threes = ones & twos;//ones和twos同时为1时 threes为1
        ones &= ~threes;//threes对应的位置为1 取反为0 和ones与则将对应位清零
        twos &= ~threes;
    }
    return ones;
}