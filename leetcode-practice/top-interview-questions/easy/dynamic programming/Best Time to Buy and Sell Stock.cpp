class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minprice=INT_MAX;
        int maxprofit=0;
        int len=prices.size();
        for(int i=0; i<len; i++)
        {
        	if(prices[i]<minprice)
        		minprice=prices[i];
        	else if(prices[i]-minprice>maxprofit)
        		maxprofit=prices[i]-minprice;
		}
		return maxprofit;
    }
};
