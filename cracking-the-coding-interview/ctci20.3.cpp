


std::vector<int> randomMofN(int arr[], int n, int m)
{
	std::vector<int> res;
	if(arr==NULL  ||   n<m  ||  m<0)
		return res;
	res.reserve(m);
	for(int i=0; i<m; ++i)
	{
		int idx=std::rand()%(n-i)+i; // 
		std::swap(arr[i], arr[idx]);
		
		res.push_back(arr[i]);
	}
	return res;
}