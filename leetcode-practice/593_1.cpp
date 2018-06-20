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
	
	bool comp2(vector<int> a, vector<int> b) 
	{
		return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
	}
		
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) 
	{
		bool flag=false;
        // 求4！种排列 
         vector<vector<int> > points{p1, p2, p3, p4};
         std::sort(points.begin(), points.end(), [&flag](vector<int> a, vector<int> b){
         	if(a[0]==b[0]  &&  a[1]==b[1])
         		flag=true;
			return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
		});
		
		if(flag)
			return false;
		
		int i=0;
		do{
			if(validThisSquare(points[0], points[1], points[2], points[3]))
				return true;
			print(points);
		}
		while(next_permutation(points.begin(), points.end(), comp));//有重复 
		//while(next_permutation(points.begin(), points.end(), std::bind1st(comp2, this)));
		return false;
    }
    bool validThisSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
    	// 四边形4顶点顺序p1、p2、p3、p4
		// 判断4条边、对角线是否相等
		 return distance2(p1,p2)==distance2(p2,p3) &&  distance2(p2,p3)==distance2(p3,p4) && distance2(p3,p4)==distance2(p4,p1)  &&  distance2(p1,p3)==distance2(p2,p4);
	}
	double distance2(vector<int>& p1, vector<int>& p2)
	{
		return (p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]); 
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

