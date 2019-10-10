

int lastStoneWeight(vector<int>& stones) {
	std::priority_queue<int> pq;
	for(int i=0; i<stones.size(); ++i)
	{
		pq.push(stones[i]);
	}
	while(pq.size()>1)
	{
		int st1=pq.top();
		pq.pop();
		int st2=pq.top();
		pq.pop();
		
		if(st1!=st2)
			pq.push(st1-st2);
	}
	if(pq.empty())
		return 0;
	return pq.top();
}