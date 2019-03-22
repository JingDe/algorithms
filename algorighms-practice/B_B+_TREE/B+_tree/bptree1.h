#ifndef BPLUS_TREE_TWO_NODE_H_
#define BPLUS_TREE_TWO_NODE_H_

// B+树实现
static int M=5;//M叉树
static int L=5;//规定叶节点的数据项的个数

typedef keytype int;
typedef valuetype int;

// 根结点：或者是叶节点，或者是儿子数在2和M之间
// 除根以外的非叶节点：M/2~M个子结点，和少于1个的键; 键i代表子树i+1中的最小的键

class BTNode{
public:
	//bool isLeaf_; // 是否是叶节点，叶节点没有儿子，只有键
	int sz_; // 键的个数
	std::set<keytype> keys_; // sz_个键，有序
			
	union{
		std::vector<BTNode*> children_; // 有序
		std::vector<LeafNode*> leafs_;//最后一层非叶结点
	};
	
		
	BTNode* parent_;// 父节点
};


// 叶节点：L/2~L个数据项
class LeafNode{
public:
	int sz_; // 数据项的个数
	std::set<valuetype> values_; // sz_个数据项
	
};


// B+树结构
class BPlusTree{
private:
	BTNode* root_;
	
};

#endif