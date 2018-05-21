// @author: norah

// B+树实现
// 根结点：或者是叶节点，或者是儿子数在2和M之间
// 除根以外的非叶节点：⌈M/2⌉~M个子结点，和少于1个的键。键i代表子树i+1中的最小的键
// 叶节点有⌈L/2⌉~L个数据项

typedef keytype int;
typedef valuetype int;	
		
template<typename T>
class BTNode{
public:
	bool isLeaf_; // 是否是叶节点，叶节点没有儿子，只有键
	int sz_; // key的个数，或者value的个数
	std::set<T> keys_; // key数组，或者value数组，有序
		
	std::vector<void*> children_; // 子节点数组，对叶节点为空
				
	BTNode<keytype>* parent_;// 父节点
};




template<typename T>
class BPlusTree{
public:
	BTNode();
	~BTNode();
	
	bool insert(const keytype& key, const valuetype& value);
	bool search(const keytype& key, valuetype *value);
	
private:
	BTNode<T>* root_;
		
	static const int M=5;
	static const int L=5;
};


BTNode::BTNode()
{
	
}

