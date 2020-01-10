
int findDuplicate(vector<int>& nums) {        
	int fast = 0, slow = 0;
	while(true){
		fast = nums[nums[fast]];
		slow = nums[slow];
		if(fast == slow)
			break;
	}
	int finder = 0;
	while(true){
		finder = nums[finder];
		slow = nums[slow];
		if(slow == finder)
			break;        
	}
	return slow;
}

int findDuplicate(vector<int> &nums) {
	int len = nums.size();
	int left = 0;
	int right = len - 1;

	while (left < right) {
		int mid = (left + right) >> 1;
		int counter = 0;
		for (int num:nums) {
			if (num <= mid) {
				counter++;
			}
		}

		if (counter > mid) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}
	return left;
}

int findDuplicate(vector<int> &nums) {
	int len = nums.size();
	int left = 0;
	int right = len - 1;

	while (left < right) {
		int mid = (left + right + 1) >> 1;
		int counter = 0;
		for (int num:nums) {
			if (num < mid) {
				counter++;
			}
		}

		if (counter >= mid) {
			right = mid - 1;
		} else {
			left = mid;
		}
	}
	return left;
}
