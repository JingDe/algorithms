
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int> > triangle;
		triangle.resize(numRows);
		
		for(int line=0; line<numRows; ++line)
		{
			triangle[line].resize(line+1);
			triangle[line][0]=triangle[line][line]=1;
			
			for(int c=1; c<line; ++c)
			{
				triangle[line][c]=triangle[line-1][c-1]+triangle[line-1][c];
			}
		}
		return triangle;
    }
};

