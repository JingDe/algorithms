
class Solution {
public:
    int maxProfit(vector<int>& prices) {
    	int profit=0;
        int valley=0, peak=0;
        int len=prices.size();
        for(int i=0; i<len-1; i++)
        {
        	while(i<len-1  &&  prices[i]>=prices[i+1])
        		i++;
        	valley=i;
        	while(i<len-1  &&  prices[i]<=prices[i+1])
        		i++;
        	peak=i;
        	profit += prices[peak]-prices[valley];
		}
		return profit;
    }
    
    int maxProfit(vector<int>& prices) {
    	int profit=0;
    	int len=prices.size();
    	for(int i=1; i<len; i++)
    	{
    		if(prices[i]>prices[i-1])
    			profit += prices[i]-prices[i-1];
		}
		return profit;
    }
};
