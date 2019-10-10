

// 方法一：线性搜索
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
	for(int i=0; i<nums.size(); ++i)
	{
		for(int j=i-1; j>=i-k; j--)
		{
			if(j>=0  &&  std::abs(nums[j]-nums[i])<=t)
				return true;
		}
	}
	return false;
}

// 方法二：二叉搜索树
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
	std::set<long> tree;
	for(int i=0; i<nums.size(); i++)
	{
		long x=nums[i];
		//std::set<int>::iterator it=std::lower_bound(tree.begin(), tree.end(), x);
		std::set<long>::iterator it=tree.lower_bound(x);
		if(it!=tree.end())
		{
			long s=*it;
			if((long)s-x<=t)
				return true;
		}

		// 查找小于x的最大的数g，检查是否x-g<=t, g>=x-t
		// 改为查找不小于x-t的数
		it=tree.lower_bound((long)x-t);
		if(it!=tree.end())
		{
			long g=*it;
			if(std::abs((long)g-x)<=t)
				return true;
		}

		tree.insert(x);
		if(tree.size()>k)
			tree.erase((long)nums[i-k]);
	}
	return false;
}

// 方法三：散列表/哈希表、桶
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
	if(k<1  ||  t<0)
		return false;
	std::map<long, int> barrel;
	for(int i=0; i<nums.size(); i++)
	{
		int x=nums[i];
		long k1=getBarrelNo(x, t);

		if(barrel.count(k1))
			return true;
		if(barrel.count(k1-1)  &&  (long)x-barrel[k1-1]<=t)		
			return true;
		if(barrel.count(k1+1)  &&  (long)barrel[k1+1]-x<=t)
			return true;
		
		if(barrel.size()>=k)
		{
			int barrelNo=getBarrelNo(nums[i-k], t);
			barrel.erase(barrelNo);
		}    
		barrel[k1]=x;
	}
	return false;
}
int getBarrelNo(int x, int t)
{
	long tmp1=(long)x-(long)t;
	long tmp2=(long)t+1;
	long k1=std::ceil(tmp1/tmp2);
	//long k1=std::ceil(((long)(x-t))/((long)(t+1)));
	//long k2=std::floor(x/(t+1));
	long k2=std::floor((long)x/tmp2);

	//printf("t=%d, %d : %lld, %lld\n", t, x, k1, k2);
	//assert(k1==k2);
	if(x>=0)
		k1=k2;
	//printf("t=%d, %d hit barrel %d\n", t, x, k1);
	return k1;
}

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{
	if(k<1  ||  t<0)
		return false;
	map<long, long> barrel;
	for(int i=0; i<nums.size(); i++)
	{
		long remappedNum =(long) nums[i]-INT_MIN;
		long bucket=remappedNum/((long)t+1);
		
		if(map.count(bucket))
			return true;
		if(map[bucket-1]  &&  remappedNum-map[bucket-1]<=t)
			return true;
		if(map[bucket+1]  &&  remappedNum-map[bucket+1]<=t)
			return true;
		
		if(map.size()>=k)
		{
			long lastBucket=((long)nums[i-k]-INT_MIN) / ((long)t+1);
			map.remove(lastBucket);
		}
		map[bucket]=remappedNum;
	}
	return false;
}

int getBarrelNo2(int x)
{
	long remappedNum=(long)x-INT_MIN;
	long bucket=remappedNum/((long)t+1);
	return bucket;
}