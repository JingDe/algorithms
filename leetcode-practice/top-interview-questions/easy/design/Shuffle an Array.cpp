class Solution {
public:
    Solution(vector<int> nums) {
        save_=nums;
        //cur_=nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return save_;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> result;
        
        int sz=save_.size();
        int used[sz]={0};
        for(int i=0;i<sz; )
        {
        	int idx=std::rand() % sz;
        	if(!used[idx])
        	{
        		result.push_back(save_[idx]);
        		used[idx]=1;
        		i++;
			}
		}
		return result;
    }
    
private:
	//vector<int> cur_;    	
	vector<int> save_;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */
