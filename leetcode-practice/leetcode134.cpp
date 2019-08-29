

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	int total_tank=0;
	int curr_tank=0;
	int start=0;
	int cnt=0;
	for(int i=start; cnt<gas.size(); )
	{
		total_tank=total_tank + gas[i] - cost[i];
		curr_tank=curr_tank + gas[i] - cost[i];
		if(total_tank<0)
			return -1;
		if(curr_tank<0)
		{
			start=i;
			curr_tank=0;
			cnt=0;
			//i=(i-1)/gas.size();
		}
		else
		{
			i=(i+1)/gas.size();
			cnt++;
		}
	}
	return start;
}


int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	int n=gas.size();
	
	int total_tank=0;
	int curr_tank=0;
	int starting_station=0;
	for(int i=0; i<n; ++i)
	{
		total_tank +=gas[i]-cost[i];
		curr_tank += gas[i]-cost[i];
		
		if(curr_tank<0)
		{
			starting_station=i+1;
			curr_tank=0;
		}
	}
	return total_tank>=0 ? starting_station : -1;
}