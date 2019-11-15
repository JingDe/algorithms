
// 方法二： 二分法搜索
bool searchMatrix(vector<vector<int>>& matrix, int target) {
	int row=matrix.size();
	if(row==0)
		return false;
	int col=matrix[0].size();
	
	int min=std::min(row, col);
	for(int i=0; i<min; ++i)
	{
		// 从对角线(i, i)开始往下和往右搜索
		// 往右 从(i, i)到(i, col-1)
		if(binary_search(matrix[i].begin()+i, matrix[i].end(), target))
			return true;
		// 往下 从(i, i)到(row-1, i)
		if(binarySearch(matrix, target, i, i, row-1))
			return true;
	}
	return false;
}

bool binarySearch(const vector<vector<int>>& matrix, int target, int col, int startRow, int endRow)
{
	while(startRow<=endRow)
	{
		int mid=(endRow-startRow)/2+startRow;
		if(matrix[mid][col]==target)
			return true;
		else if(matrix[mid][col]>target)
			endRow=mid-1;
		else
			startRow=mid+1;
	}
	return false;
}

// 方法三： 缩小搜素矩阵
bool searchMatrix(vector<vector<int>>& matrix, int target)
{
	vector<vector<int> > mat=matrix;
	int targ=target;
	
	if(mat.empty()  ||  mat[0].empty())
		return false;
	
	// 左上角的列、行， 右下角列、行的索引
	return searchRec(0, 0, matrix[0].size()-1, matrix.size()-1);
}

bool searchRec(int left, int up, int right, int down)
{
	if(left>right  ||  up>down)
		return false;
	else if(target<matrix[up][left]  ||  target>matrix[down][right])
		return false;
	
	int mid=left+(right-left)/2; // 中间列
	int row=up;
	// 
	while(row<=down  &&  matrix[row][mid]<=target)
	{
		// 
		if(matrix[row][mid]==target)
			return true;
		row++;
	}
	
	return (searchRec(left, row, mid-1, down)  ||  searchRec(mid+1, up, right, row-1));
}

// 
bool searchMatrix(vector<vector<int>>& matrix, int target)
{
	if(matrix.empty()  ||  matrix[0].empty())
		return false;
	
	int cur_row=matrix.size()-1;
	int cur_col=0;
	
	while(cur_row>=0  &&  cur_col<matrix[0].size())
	{
		if(matrix[cur_row][cur_col]==target)
			return true;
		else if(matrix[cur_row][cur_col]>target)
			cur_row--;
		else
			cur_col++;
	}
	return false;
}
