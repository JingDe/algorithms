
void setZeroes(vector<vector<int>>& matrix) {
	bool colFirst=false;
	int m=matrix.size();
	int n=matrix[0].size();
	for(int r=0; r<m; ++r)
		for(int c=0; c<n; ++c)
		{
			if(matrix[r][c]==0)
			{
				matrix[r][0]=0;				
				if(c==0)
					colFirst=true;
				else
					matrix[0][c]=0;
			}
		}
		
	for(int i=1; i<m; ++i)
		for(int j=1; j<n; ++j)
		{
			if(matrix[i][0]==0  ||  matrix[0][j]==0)
				matrix[i][j]=0;
		}
	if(matrix[0][0]==0)
		for(int c=0; c<n; ++c)
			matrix[0][c]=0;
	if(colFirst==true)
		for(int r=0; r<m; ++r)
			matrix[r][0]=0;
}