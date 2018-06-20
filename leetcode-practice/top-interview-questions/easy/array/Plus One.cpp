class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int len=digits.size();
        int i;
        for(i=len-1; i>=0  &&  digits[i]==1; i--)
        {
        	digits[i]=0;
		}
		if(i>=0)
			digits[i]=1;
		else
		{
			digits.insert(digits.begin(), 1);
		}
        return digits;
    }
    vector<int> plusOne(vector<int>& digits) {
    	int len=digits.size();
        int i;
        for(i=len-1; i>=0  &&  digits[i]==9; i--)
        {
        	digits[i]=0;
		}
		if(i>=0)
			digits[i]+=1;
		else
		{
			digits.insert(digits.begin(), 1);
		}
        return digits;
    }
};
