class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        min=INT_MAX;
        nextMin=INT_MAX;
        minRight=true;
    }
    
    void push(int x) {
        vec.push_back(x);
        if(x<min)
        	nextMin=min, min=x;
        else if(x<nextMin)
        	nextMin=x;
    }
    
    void pop() {
        if(!vec.empty())
        {
        	int val=top();
        	vec.pop_back();
        	if(val==min  ||  val==nextMin)
        		minRight=false;
		}
    }
    
    int top() {
        return vec.back();
    }
    
    int getMin() {
    	if(!minRight)
    		computeMin();
		return min;
    }
    
private:
	std::vector<int> vec; 
	int min;
	int nextMin;
	bool minRight;
	
	void computeMin(){
		int min1=INT_MAX, nextMin1=INT_MAX;
        for(std::vector<int>::iterator itr=vec.begin(); itr!=vec.end(); itr++)
        {
			if(*itr<min1) 
				nextMin1=min1, min1=*itr;
			else if(*itr<nextMin1)
				nextMin1=*itr;
		}
		min=min1;
		nextMin=nextMin1;
		minRight=true;
	}
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
