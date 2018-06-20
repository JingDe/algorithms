#include<iostream>
#include<string>
#include<sstream>
#include<algorithm> 
#include<vector>

using std::vector;
using std::string;
using std::stringstream;



struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


void printList(ListNode* head)
{
	ListNode* p=head;
	while(p)
	{
		std::cout<<p->val<<" ";
		p=p->next;
	}
	std::cout<<std::endl;
}


class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* left=new ListNode(0);
        left->next=NULL;
        
		ListNode* right=head;
		ListNode* end=head;
		ListNode* temp;
		while(end!=NULL  &&  end->next!=NULL) 
		{
			temp=right;
			
			right=right->next;
			end=end->next;
			end=end->next;
			
			temp->next=left->next;
			left->next=temp;
		}
		
		if(end!=NULL)
		{
			right=right->next;		
		}
		
		printList(left);
		printList(right);
		
		left=left->next;
		while(right!=NULL)
		{
			if(right->val!=left->val)
				return false;
			left=left->next;
			right=right->next; 
		}
		return true;
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

ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

string boolToString(bool input) {
    return input ? "True" : "False";
}



int main()
{
	std::string s="[1,1]";
	ListNode* head=stringToListNode(s);
	printList(head);
	
	Solution so;
	bool result=so.isPalindrome(head);
	std::cout<<boolToString(result)<<std::endl;
	
	return 0;
}
