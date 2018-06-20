class Solution {
public:
    int reverse(int x) {
        bool positive=x > 0;
        if(x<0)
        	x=(-1)*x;
        int t;
        int res=0;
        while(x!=0)
        {
        	t=x%10;
        	x=x/10;
        	int temp=res;
        	res=res*10+t;
        	
        	if((res-t)/10 != temp)
        		return 0;
		}
		if(!positive)
			res=(-1)*res;
		return res;
    }
};
