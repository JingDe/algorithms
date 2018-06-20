class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // 每一行0-9，每一列0-9，每一个小正方形0-9
        vector<char> line;
		for(int i=0; i<9; i++)
			if(validate(board[i]))
				return false;
		for(int i=0; i<9; i++)
		{
			line.clear();
			for(int j=0; j<9; j++)
			{
				line.push_back(board[j][i]);
			}
			if(validate(line)==false)
				return false;
		}
		for(int i=0; i<9; i+=3)
		{
			for(int j=0; j<9; j+=3)
			{
				line.clear();
				for(int m=0; m<3; m++)
					for(int n=0; n<3; n++)
						line.push_back(board[i+m][j+n]);
				if(validate(line)==false)
				return false;
			}
		}
		return true;
    }
    bool validate(vector<int>& nums) {
        int len=nums.size();
		for(int i=1; i<len; i++)
		{
			int tmp=nums[i];
            int j;
			for(j=i-1; j>=0  &&  nums[j]>tmp; j--)
			{
				nums[j+1]=nums[j];
			}
			if(j>=0  &&  nums[j]==tmp)
				return false;
			else
				nums[j+1]=tmp;
		}
		return true;
    }
};
