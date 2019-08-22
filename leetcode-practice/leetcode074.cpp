
bool searchMatrix(vector<vector<int>>& matrix, int target) {
	if(matrix.empty())
		return false;
	int m=matrix.size();
	int n=matrix[0].size();
	
	// 二维下标i,j 对应 一维下标i*n+j
	// 一维下标p ————》 二维下标？？
			// x= p/n
			// y= p-x*n 
	int left=0;
	int right=m*n-1;
	int mid=0;
	int x=0, y=0;
	while(left<=right)
	{
		mid=left+(right-left)/2;
		two2one(mid, x, y);
		if(matrix[x][y]==target)
			return true;
		if(matrix[x][y]<target)
			left=mid+1;
		else
			right=mid-1;
	}
	return false;
}

void two2one(int p, int& x, int& y, int n)
{
	x=p/n;
	y=p-x*n;
}