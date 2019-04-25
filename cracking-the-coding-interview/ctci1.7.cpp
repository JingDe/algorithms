

void setZero(int **a, int m, int n)
{
	int rrow[m], ccol[n];
	for(int row=0; row<m; ++row)
		for(int col=0; col<n; ++col)
		{
			if(a[row][col]==0)
			{
				rrow[row]=true;
				ccol[col]=true;
			}
			
		}
		
	for(int row=0; row<m; ++row)
		for(int col=0; col<n; ++col)
		{
			if(rrow[row]==true  ||  ccol[col]==true)
				a[m][n]=0;
		}
}