// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        // ��[1, 2,...n]�ҳ���һ������汾������isBadVersion(i)�����ô�������
		// �ⷨ�����ַ�:���м�ķ������������� 
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
    
    // ���������ķ���ֵ�����������
	// λ�ڵ�һ����������bad
	// ��λ�ڵ�һ������bad��ǰһ������bad 
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
    
    // �Ż��棡�� 
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
