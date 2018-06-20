class Solution {
public:
	void print(const std::vector<vector<int> >& points)
	{
		for(std::vector<vector<int> >::const_iterator it=points.begin(); it!=points.end(); it++)
			std::cout<<"("<<(*it)[0]<<","<<(*it)[1]<<")  ";
		std::cout<<std::endl;
	}

	struct{
    	bool operator()(vector<int> a, vector<int> b) const
    	{
    		return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
		}
	}comp;
		
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) 
	{ 
        
         vector<vector<int> > points{p1, p2, p3, p4};
         std::sort(points.begin(), points.end(), [](vector<int> a, vector<int> b){
			return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
		});
		
		
		std::vector<std::vector<std::vector<int> > > results;
		std::vector<std::vector<int> > current;
		permutation3(4, current, points, 0, results);
		for(std::vector<std::vector<std::vector<int> > >::const_iterator it=results.begin(); it!=results.end(); it++)
		{
			std::vector<std::vector<int> > one=*it;
			if(validThisSquare(one[0], one[1], one[2], one[3]))
				return true;
		}
		
		return false;
    }
    bool validThisSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
		 return distance2(p1,p2)!=0  &&  distance2(p1,p2)==distance2(p2,p3) &&  distance2(p2,p3)==distance2(p3,p4) && distance2(p3,p4)==distance2(p4,p1)  &&  distance2(p1,p3)==distance2(p2,p4);
	}
	double distance2(vector<int>& p1, vector<int>& p2)
	{
		return (p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]); 
	}
	
	
	

	bool equal(const std::vector<int> &v1, const std::vector<int> &v2)
	{
		if(v1[0]==v2[0]  &&  v1[1]==v2[1])
			return true;
		return false;
	}
	
	void permutation3(int n, std::vector<std::vector<int> >& current, const std::vector<std::vector<int> >& points, int cur, std::vector<std::vector<std::vector<int> > >& results)
	{
		if(cur==n)
		{
			//print(current);
			results.push_back(current);
		} 
		else
		{
			for(std::vector<std::vector<int> >::const_iterator it=points.begin(); it!=points.end(); ++it) // 依次考察points中所有元素 
			{
				int c1=0; 
				int c2=0;
				
				for(std::vector<std::vector<int> >::const_iterator it3=points.begin(); it3!=points.end(); ++it3) 
					if(equal(*it, *it3))
						c1++;
							
				for(std::vector<std::vector<int> >::iterator it2=current.begin(); it2!=current.end(); ++it2) // 对照current中的元素 
				{
					if(equal(*it, *it2))
						c2++;
				}
				if(c1>c2)
				{
					current.push_back(*it);
					permutation3(n, current, points, cur+1, results);
					current.pop_back();
				}
			}
		}
	}
};
