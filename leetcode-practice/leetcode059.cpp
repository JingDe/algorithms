
// LeetCode 54
vector<int> spiralOrder(vector<vector<int>>& matrix) {
	if(matrix.empty())
		return vector<int>();
	int top=0;
	int bottom=matrix.size()-1;
	int left=0;
	int right=matrix[0].size()-1;

	vector<int> ans;
	while(top<=bottom  &&  left<=right)
	{
		printf("left %d, right %d, top %d, bottom %d\n", left, right, top, bottom);
		for(int i=left; i<=right; ++i)
			ans.push_back(matrix[top][i]);
		
		if(top==bottom)
			break;

		for(int i=top+1; i<=bottom; ++i)
			ans.push_back(matrix[i][right]);
		
		if(left==right)
			break;
		
		for(int i=right-1; i>=left; --i)
			ans.push_back(matrix[bottom][i]);
		
		for(int i=bottom-1; i>left; --i)
			ans.push_back(matrix[i][left]);

		left++;
		right--;
		top++;
		bottom--;
	}
	return ans;
}

// 
vector<vector<int>> generateMatrix(int n) {
	vector<vector<int>> ans(n, vector<int>(n));
	
	int top=0;
	int bottom=n-1;
	int left=0;
	int right=n-1;

	int counter=1;
	while(top<=bottom  &&  left<=right)
	{
		printf("left %d, right %d, top %d, bottom %d\n", left, right, top, bottom);
		for(int i=left; i<=right; ++i)
			ans[top][i]=counter++;
			
		
		if(top==bottom)
			break;

		for(int i=top+1; i<=bottom; ++i)
			ans[i][right]=counter++;
		
		if(left==right)
			break;
		
		for(int i=right-1; i>=left; --i)
			ans[bottom][i]=counter++;
		
		for(int i=bottom-1; i>left; --i)
			ans[i][left]=counter++;

		left++;
		right--;
		top++;
		bottom--;
	}
	return ans;
}
	
	