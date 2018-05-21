
// B树实现

template<typename keytype>
class BTNode{
private:
	static const int M=5;
	static const int L=5;
	
	BTNode* parent_;
	int keynum_;
	std::vector<keytype> keys_;//keynum_个键
	std::vector<BTNode*> children_;//keynum_+1个子节点
	bool isLeaf_;
	
public:
	BTNode();
	~BTNode();
	
	bool insert(const keytype& key, const valuetype& value);
	bool search(const keytype& key, valuetype *value);
};

