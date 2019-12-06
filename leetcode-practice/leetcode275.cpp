
int hIndex(vector<int>& citations) {
	int len=citations.size();
	
	int left=0;
	int right=len-1;
	int mid;
	while(left<=right)
	{
		mid = left + (right-left)/2;
		// if(citations[mid] == len-mid)
			// return len-mid;
		if(citations[mid] >= len-mid)
			right = mid-1;
		else
			left = mid+1;
	}
	// left = right + 1
	return len-left;
}