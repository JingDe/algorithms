
vector<int> spiralOrder(vector<vector<int>>& matrix) {
	int top=0;
	int bottom=matrix.size()-1;
	int left=0;
	int right=matrix[0].size()-1;
	
	vector<int> ans;
	while(top<=bottom  &&  left<=right)
	{
		for(int i=left; i<=right; ++i)
			ans.push_back(matrix[top][i]);
		
		for(int i=top+1; i<=bottom; ++i)
			ans.push_back(matrix[i][right]);
		
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