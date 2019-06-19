
#include

const int kWordSize = 26 + 5;
const int kNodeSize = 1200 + 5;
const int kHashSize = 10001; //大质数

struct Node{
	char word[kWordSize];
	Node* next;
};

Node node[kNodeSize+1];
Node* head[kHashSize+1];