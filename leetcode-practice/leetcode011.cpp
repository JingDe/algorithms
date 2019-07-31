


int maxArea(vector<int>& height) {
	int sz=height.size();
	int res=0;
	for(int s=0; s<sz; ++s)
		for(int e=s+1; e<sz; ++e)
		{
			// int area=std::min(height[s], height[e])*(e-s);
			// res=std::max(res, area);
			res=std::max(res, std::min(height[s], height[e])*(e-s));
		}
	return res;
}

int maxArea_2pointers(vector<int>& height) 
{
	int sz=height.size();
	int res=0;
	int sp=0; 
	int ep=sz-1;
	while(sp<ep)
	{
		int area=std::min(height[sp], height[ep])*(ep-sp);
		res=std::max(area, res);
		
		if(height[sp]<=height[ep])
			++sp;
		else
			--ep;
	}
	return res;
}
