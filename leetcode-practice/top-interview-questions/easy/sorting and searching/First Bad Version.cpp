// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        // 从[1, 2,...n]找出第一个错误版本，调用isBadVersion(i)，调用次数最少
		// 解法：二分法:若中间的符合条件，返回 
		int middle;
		int left=1, right=n;
		while(left<=right) 
		{
			middle=left+(right-left)/2;
			if(isBadVersion(middle)) 
			{
				if(isFirst(middle, left))
					return middle;
				else
					right=middle-1;
			}
			else
				left=middle+1;
		}
		return -1;
    }
    
    // 满足条件的返回值有以下情况：
	// 位于第一个，并且是bad
	// 不位于第一个，且bad，前一个不是bad 
    bool isFirst(int middle, int left)
    {
    	if(middle-1<left  ||  ( middle-1>0  &&  !isBadVersion(middle-1) ))
    		return true;
    	return false;
	}
	
	int firstBadVersion(int n) {
        int left=1, right=n;
		int mid;
		while(left<=right)
		{
			mid=left+(right-left)/2;
			int isBad=isBadVersion(mid);
			if(isBad  &&  (mid-1<left  ||  mid-1>0  &&  !isBadVersion(mid-1)))
				return mid;
			else if(isBad)
				right=mid-1;
			else
				left=mid+1;
		}
		return -1;
    }
    
    // 优化版！！ 
    int firstBadVersion(int n) {
        int left=1, right=n;
		int mid;
		while(left<=right)
		{
			mid=left+(right-left)/2;
			int isBad=isBadVersion(mid);
			if(isBad  &&  (mid-1<left  ||  !isBadVersion(mid-1)))
				return mid;
			else if(isBad)
				right=mid-1;
			else
				left=mid+1;
		}
		return -1;
    }
};
