#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>
#include<functional>

using std::stringstream;
using std::string;
using std::vector; 
using std::cin;
using std::cout;

class Solution{
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
		bool flag=false;
        
         vector<vector<int> > points{p1, p2, p3, p4};
         std::sort(points.begin(), points.end(), [&flag](vector<int> a, vector<int> b){
         	if(a[0]==b[0]  &&  a[1]==b[1])
         		flag=true;
			return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
		});
		
		if(flag)
			return false;
		
		std::vector<std::vector<std::vector<int> > > results;
		std::vector<std::vector<int> > current;
		permutation2(4, current, points, 0, results);
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
		 return distance2(p1,p2)==distance2(p2,p3) &&  distance2(p2,p3)==distance2(p3,p4) && distance2(p3,p4)==distance2(p4,p1)  &&  distance2(p1,p3)==distance2(p2,p4);
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
	
	void permutation2(int n, std::vector<std::vector<int> >& current, const std::vector<std::vector<int> >& points, int cur, std::vector<std::vector<std::vector<int> > >& results)
	{
		if(cur==n)
		{
			//print(current);
			results.push_back(current);
		} 
		else
		{
			for(std::vector<std::vector<int> >::const_iterator it=points.begin(); it!=points.end(); ++it)
			{
				int ok=1;
				for(std::vector<std::vector<int> >::iterator it2=current.begin(); it2!=current.end(); ++it2)
				{
					if(equal(*it, *it2))
						ok=0;
				}
				if(ok)
				{
					current.push_back(*it);
					permutation2(n, current, points, cur+1, results);
					current.pop_back();
				}
			}
		}
	}
};



void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

string boolToString(bool input) {
    return input ? "True" : "False";
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> p1 = stringToIntegerVector(line);
        getline(cin, line);
        vector<int> p2 = stringToIntegerVector(line);
        getline(cin, line);
        vector<int> p3 = stringToIntegerVector(line);
        getline(cin, line);
        vector<int> p4 = stringToIntegerVector(line);
        
        bool ret = Solution().validSquare(p1, p2, p3, p4);

        string out = boolToString(ret);
        cout << out << std::endl;
    }
    return 0;
}

